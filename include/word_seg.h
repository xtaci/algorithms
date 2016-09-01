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

#ifndef ALGO_WORD_SEG_H__
#define ALGO_WORD_SEG_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "generic.h"
#include "hash_table.h"
#include "queue.h"

#ifdef ALG_VLA_NOT_SUPPORTED
#include "2darray.h"
#endif//ALG_VLA_NOT_SUPPORTED

namespace alg {
	/**
	 * define a word in four state
	 * which means a
	 *	-- SINGLE, a single word like '地','水','火','风'
	 * 	-- BEGIN, a word is the begin of the word, eg '如' in '如果'
	 *	-- MIDDLE, a word is at the middle of the word, eg, '习' in '补习班'
	 * 	-- END, a word is at the end of the word, eg, '物' in '有机物'
	 */
	class WordSeg {
		public:
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
			inline const float (&TP()const)[4][4] {
				/**
				 * the state transition probability matrix. 
				 * the 2-d array is in the format of :
				 * SINGLE	-> S B M E
				 * ... 		-> S B M E
				 * A MORE SOPHISTICATED CALCULATION IS REQUIRED IN PRACTICE
				 */
				static const float _TP[4][4] = {
					{0.5138298266610544, 0.48617017333894563, 0.000001, 0.000001},
					{0.000001, 0.000001, 0.14817814348183422, 0.8518218565181658},
					{0.000001, 0.000001, 0.2835512540013088, 0.7164487459986911},
					{0.44551469488355755, 0.554485305116442, 0.000001, 0.000001}
				};

				return _TP;
			}
			/**
			 * the start probability of state
			 */
			inline const float (&SP()const)[4] {
				/**
				 * the start probability of state
				 */
				static const float _SP[4] = {0.5f, 0.5f, 0.0f, 0.0f};
				return _SP;
			}
			/**
			 * word state definition
			 * record a single word emission probability in each state
			 */
			struct WordEP {
				float 		EP[4];	// the emission probability in each state
				uint64_t	SC[4];	// the count of appearence in each state
				WordEP() {
					EP[0]  = EP[1] = EP[2] = EP[3] = 0.0f;
					SC[0]  = SC[1] = SC[2] = SC[3] = 0;
				}
			};

			static const int GB18030_NR	= 70244;

			/**
			 * The word segmentation structure.
			 */
		private:
			HashTable<uint32_t, WordEP> wordht;	// a WORD-> WordEP hashtable
		public:
			WordSeg() : wordht(GB18030_NR){ }

			/**
			 * init a WordSeg struct by a given file
			 * format:
			 * WORD1 .....
			 * WORD2
			 * ....
			 * WORDN
			 */
			WordSeg(const char * path):wordht(GB18030_NR) {
				FILE * fp;	
				char word[64];	// the longest word should be less than 64 char

				fp = fopen(path, "r");
				if (fp==NULL) {
					perror(__func__);
				} else {
					while(!feof(fp)) {
						fscanf(fp, "%s%*[^\n]", word);
						//			printf("read %s count %d\n", word, count);
						add_word(word);
					}
				}
				fclose(fp);

				calc_all();
			}

			/**
			 * add a new word to the hashtable
			 */
			void add_word(const char * word) {
				int i=0;
				int len = strlen(word);
				int num_char = 0;

				while(word[i]!='\0') {
					uint32_t CH;
					i+= gb18030_read(word, i, &CH);
					num_char++;

					WordEP & wep = wordht[CH];

					if (i==len && (num_char==1)) { // single word
						wep.SC[SINGLE]+=1;
					} else {
						if (num_char==1) {	// begin
							wep.SC[BEGIN]+=1;
						} else {
							if (i==len) { //end 
								wep.SC[END]+=1;	
							} else {	// otherwise we are in middle
								wep.SC[MIDDLE]+=1;
							}
						}
					}
				}
			};

			/**
			 * return the most possible B,E,M,S sequence(FIFO) for a sentence
			 * using The Viterbi algorithm
			 *
			 * you should strip the , . white-spaces first before entering this 
			 * function
			 */
			Queue<uint32_t> * run(const char * str) {
				// the position of string cursor
				int pos = 0;
				int len = strlen(str);

#ifdef ALG_VLA_NOT_SUPPORTED
				alg::Array2D<double> V(len, 4);
				uint32_t CH;

				// record the path
				alg::Array2D<> path(4, len+1);
				alg::Array2D<> newpath(4, len+1);

				path.clear(0);
				newpath.clear(0);
#else
				double V[len][4];
				uint32_t CH;

				// record the path
				char path[4][len+1];
				char newpath[4][len+1];

				memset(path,0, sizeof(path));
				memset(newpath,0, sizeof(newpath));
#endif

				// Initialize base case. the first observation.
				int i;
				pos = gb18030_read(str, pos, &CH);

				for(i=0; i<4;i++) {	
					V[0][i] = SP()[i] * wordht[CH].EP[i];
					path[i][0] = i+'0';
				}

				// Run Viterbi for observation > 1
				int wc=1; // word count;
				while(pos<len) {
					pos += gb18030_read(str, pos, &CH);

					int j;
					for(j=0;j<4;j++) {
						double prob_max = 0.0f;
						int state_max = 0;
						int k;
						for(k=0;k<4;k++) { // like relaxation step in Dijkstra.
							double prob = V[wc-1][k] * TP()[k][j] * wordht[CH].EP[j];
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

				Queue<uint32_t> * q = new Queue<uint32_t>(wc);

				i=0;
				while(path[state_max][i]!='\0') {
					q->enqueue(path[state_max][i]);
					i++;
				}

				return q;
			}

		private:
			/**
			 * calc a single word emission probability by its count in each state
			 */
			void calc_ep(WordEP & wep) {
				double sum = wep.SC[0]+wep.SC[1]+wep.SC[2]+wep.SC[3];
				wep.EP[SINGLE] = wep.SC[SINGLE]/sum;
				wep.EP[BEGIN] = wep.SC[BEGIN]/sum;
				wep.EP[END] = wep.SC[END]/sum;
				wep.EP[MIDDLE] = wep.SC[MIDDLE]/sum;
			};

			/**
			 * calculate the emission probability for each word
			 */
			void calc_all() {
				unsigned char i, j, m, n;

				// for each char in gb18030
				for (i=0;i<=0x7f;i++) { calc_ep(wordht[i]); }

				for (i=0x81;i<=0xFE;i++) {
					for(j=0x40;j<=0xFE;j++) {
						uint32_t CH = (i << 8)|j;
						calc_ep(wordht[CH]); 
					}

					for(j=0x30;j<=0x39;j++) {
						for(m=0x81;m<=0xFE;m++) {
							for(n=0x30;n<=0x39;n++) {
								uint32_t CH = (i<<24)|(j<<16)|(m<<8)|n;
								calc_ep(wordht[CH]); 
							}
						}
					}
				}
			};
	};

}
#endif //
