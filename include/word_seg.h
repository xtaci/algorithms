/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * CHINESE WORD SEGMENTATION
 *
 * Features:
 * 1. based on Hidden Markov Model
 * 2. definition the states in B,E,M,S 
 * 3. solve the hidden states with viterbi algorithm.
 *
 * http://en.wikipedia.org/wiki/Hidden_Markov_model
 * http://en.wikipedia.org/wiki/Viterbi_algorithm
 *
 ******************************************************************************/

#ifndef __WORD_SEG_H__
#define __WORD_SEG_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "generic.h"
#include "hash_table.h"
#include "queue.h"

/**
 * define a word in four state
 * which means a
 *	-- SINGLE, a single word like '地','水','火','风'
 * 	-- BEGIN, a word is the begin of the word, eg '如' in '如果'
 *	-- MIDDLE, a word is at the middle of the word, eg, '习' in '补习班'
 * 	-- END, a word is at the end of the word, eg, '物' in '有机物'
 */
enum WORDSTATE {
	SINGLE = 0,
	BEGIN = 1,
	MIDDLE = 2,
	END = 3
};

enum WORDTAG {
	N=0,		//		名词
	V,			//		动词
	ADJ	,		//		形容词
	ADV	,		//		副词
	CLAS,		//		量词
	ECHO,		//		拟声词
	STRU,		//		结构助词
	AUX	,		//		助词
	COOR,		//		并列连词
	CONJ,		//		连词
	SUFFIX,		//		前缀
	PREFIX,		//		后缀
	PREP  ,		//  	介词
	PRON  ,		//  	代词
	QUES  ,		//  	疑问词
	NUM	  ,		//  	数词
	IDIOM 		//  	成语	
};

/**
 * the state transition probability matrix. 
 * the 2-d array is in the format of :
 * SINGLE	-> S B M E
 * ... 		-> S B M E
 */
static const float TP[4][4] = {
	{0.5f, 0.5f, 0.0f, 0.0f}, // S
	{0.0f, 0.0f, 0.5f, 0.5f}, // B
	{0.0f, 0.0f, 0.5f, 0.5f}, // M
	{0.5f, 0.5f, 0.0f, 0.0f}  // E
};

/**
 * the start probability of state
 */
static const float SP[4] = {0.5f, 0.5f, 0.0f, 0.0f};

/**
 * word state definition
 * record a single word emission probability in each state
 */
struct WordEP {
	float EP[4];	// the emission probability in each state
	uint64_t	SC[4];	// the count of appearence in each state
};

#define GB18030_NR	70244

/**
 * The word segmentation structure.
 */
struct WordSeg {
	struct HashTable * wordht;	// a WORD-> WordEP hashtable
	uint32_t words[GB18030_NR];	// every char in GB18030
	uint32_t wordcount;
};

/**
 * init a new WordEP struct
 */
static inline struct WordEP * 
__word_seg_new_ep()
{
	struct WordEP *	wep = (struct WordEP *)malloc(sizeof(struct WordEP));	
	wep->EP[0] = wep->EP[1] = wep->EP[2] = wep->EP[3] = 0.0f;
	memset(wep->SC, 0, sizeof(wep->SC));
	return wep;
}

/**
 * add a new word to the hashtable
 */
static void 
__word_seg_add(struct HashTable * wordht, const char * word)
{
	int i=0;
	int len = strlen(word);
	int num_char = 0;

	while(word[i]!='\0') {
		uint32_t CH;
		i+= gb18030_read(word, i, &CH);
		num_char++;

		struct WordEP * wep = (struct WordEP *)hash_table_get(wordht, CH);
		if (wep==NULL) {
			// new WordEP struct
			wep = __word_seg_new_ep();
			hash_table_set(wordht, CH, (uintptr_t)wep);
		}

		if (i==len && (num_char==1)) { // single word
			wep->SC[SINGLE]+=1;
		} else {
			if (num_char==1) {	// begin
				wep->SC[BEGIN]+=1;
			} else {
				if (i==len) { //end 
					wep->SC[END]+=1;	
				} else {	// otherwise we are in middle
					wep->SC[MIDDLE]+=1;
				}
			}
		}
	}
}

/**
 * calc a single word emission probability by its count in each state
 */
static void 
__word_seg_calc_ep(struct WordEP *wep)
{
	double sum = wep->SC[0]+wep->SC[1]+wep->SC[2]+wep->SC[3];
	wep->EP[SINGLE] = wep->SC[SINGLE]/sum;
	wep->EP[BEGIN] = wep->SC[BEGIN]/sum;
	wep->EP[END] = wep->SC[END]/sum;
	wep->EP[MIDDLE] = wep->SC[MIDDLE]/sum;
}

/**
 * calculate the emission probability for each word
 */
static void 
__word_seg_calc_all(struct HashTable * wordht)
{
	unsigned char i, j, m, n;
	struct WordEP * wep; 

	// for each char in gb18030
	for (i=0;i<=0x7f;i++) {
		wep = (struct WordEP*)hash_table_get(wordht, i);
		if (wep!=NULL) { __word_seg_calc_ep(wep); }
	}
	
	for (i=0x81;i<=0xFE;i++) {
		for(j=0x40;j<=0xFE;j++) {
			uint32_t CH = (i << 8)|j;
			wep = (struct WordEP *)hash_table_get(wordht, CH);
			if (wep!=NULL) { __word_seg_calc_ep(wep); }
		}
		
		for(j=0x30;j<=0x39;j++) {
			for(m=0x81;m<=0xFE;m++) {
				for(n=0x30;n<=0x39;n++) {
					uint32_t CH = (i<<24)|(j<<16)|(m<<8)|n;
					wep = (struct WordEP *)hash_table_get(wordht, CH);
					if (wep!=NULL) { __word_seg_calc_ep(wep); }
				}
			}
		}
	}
}

/**
 * init a WordSeg struct by a given file
 * format:
 * WORD1 .....
 * WORD2
 * ....
 * WORDN
 */
static struct WordSeg * 
word_seg_init(const char * path)
{
	struct WordSeg * ws = (struct WordSeg*)malloc(sizeof(struct WordSeg));
	ws->wordht = hash_table_create(GB18030_NR);
	
	FILE * fp;	
	char word[64];	// the longest word should be less than 64 char
	
	fp = fopen(path, "r");
	if (fp==NULL) {
		perror(__func__);
	} else {
		while(!feof(fp)) {
			fscanf(fp, "%s%*[^\n]", word);
			//			printf("read %s count %d\n", word, count);
			__word_seg_add(ws->wordht, word);
		}
	}
	fclose(fp);

	__word_seg_calc_all(ws->wordht);

	return ws;
}

/**
 * return the most possible B,E,M,S sequence(FIFO) for a sentence
 * using The Viterbi algorithm
 *
 * you should strip the , . white-spaces first before entering this 
 * function
 */
static Queue * 
word_seg_run(struct WordSeg * ws, const char * str)
{
	// the position of string cursor
	int pos = 0;
	int len = strlen(str);
	
	double V[len][4];
	struct WordEP * wep;
	uint32_t CH;
	
	// record the path
	char path[4][len+1];
	char newpath[4][len+1];
	memset(path,0, sizeof(path));
	memset(newpath,0, sizeof(newpath));

	// Initialize base case. the first observation.
	int i;
	pos = gb18030_read(str, pos, &CH);
	wep = (struct WordEP *)hash_table_get(ws->wordht, CH); 
		
	for(i=0; i<4;i++) {	
		V[0][i] = SP[i] * wep->EP[i];
		path[i][0] = i+'0';
	}

	// Run Viterbi for observation > 1
	int wc=1; // word count;
	while(pos<len) {
		pos += gb18030_read(str, pos, &CH);
		wep = (struct WordEP *)hash_table_get(ws->wordht, CH);
		
		int j;
		for(j=0;j<4;j++) {
			double prob_max = 0.0f;
			int state_max = 0;
			int k;
			for(k=0;k<4;k++) { // like relaxation step in Dijkstra.
				double prob = V[wc-1][k] * TP[k][j] * wep->EP[j];
				if (prob > prob_max) {
					prob_max = prob;
					state_max = k;
				}
			} 
			// update the maximum values
			V[wc][j] = prob_max;
			strcpy(newpath[j], path[state_max]);
			newpath[j][wc] = j+'0';
		}
			
		// path update	
		for (j=0;j<4;j++) {
			strcpy(path[j], newpath[j]);
		}
			
		wc++;
	}

	double prob_max = 0;	
	int state_max = 0;

	for(i=0;i<4;i++) {
		if (V[wc-1][i] > prob_max) {
			prob_max = V[wc-1][i];
			state_max = i;
		}
	}
	
	Queue * q = create_queue(wc);
	
	i=0;
	while(path[state_max][i]!='\0') {
		enqueue(q, (uintptr_t)path[state_max][i]);
		i++;
	}

	return q;
}

/**
 * replace the unknown chars with white-space.
 */
static void 
word_seg_strip(struct WordSeg * ws, char * str)
{
	int pos = 0;
	int len = strlen(str);
	uint32_t CH;
	
	while(pos<len) {
		int wordlen = gb18030_read(str, pos, &CH);
		struct WordEP * wep = (struct WordEP *)hash_table_get(ws->wordht, CH);
		if (wep == NULL) {
			int k;
			for (k=0;k<wordlen;k++){
				str[pos+k] = ' ';
			}
		}
		pos+=wordlen;
	}
}

#endif //
