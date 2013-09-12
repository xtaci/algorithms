



#ifndef _CBASE64_H_
#define _CBASE64_H_


#include <iostream>
#include <string>
#include <string.h>

using namespace std;


class CBase64
{

public:
	CBase64();
	~CBase64();



	static string encodeBase64(unsigned char *input , int input_len)
		{
			string code="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			unsigned char input_char[3];
			char output_char[5];
			int output_num;
			string output_str="";
			int near=input_len%3;

			for(int i=0;i<input_len;i+=3)
				{
					memset(input_char ,0,3);
					memset(output_char ,61,4);
					if(i+3 <= input_len)
						{
							memcpy(input_char,input+i,3);
						}else
							{
								memcpy(input_char,input+i,input_len-i);
								output_num=((int)input_char[0]<<16)+((int)input_char[1]<<8)+(int)input_char[2];
								if(near==1)
									{
									output_char[0]=code[((output_num>>18) & 0xff)];
									output_char[1]=code[((output_num>>12) & 0x3f)];
									output_char[2]='=';
									output_char[3]='=';
									output_char[4]='\0';
									}

								if(near==2)
									{
									output_char[0]=code[((output_num>>18) & 0xff)];
									output_char[1]=code[((output_num>>12) & 0x3f)];
									output_char[2]=code[((output_num>>6) & 0x3f)];;
									output_char[3]='=';
									output_char[4]='\0';
									}
								
								output_str.append(output_char);
								break;
							}

					output_num=((int)input_char[0]<<16)+((int)input_char[1]<<8)+(int)input_char[2];
					output_char[0]=code[((output_num>>18) & 0xff)];
					output_char[1]=code[((output_num>>12) & 0x3f)];
					output_char[2]=code[((output_num>>6) & 0x3f)];
					output_char[3]=code[((output_num) & 0x3f)];
					output_char[4]='\0';
					output_str.append(output_char);

					
				}

			//cout <<"encodeBase64 Res::: " << output_str <<  endl;


			return output_str;
		}

	static string decodeBase64(string input)
		{
			unsigned char input_char[4];
			unsigned char output_char[4];
			int output_num=0;
			int k=0;
			string output_str="";

			for(unsigned int i=0;i<input.size();i++)
				{
					input_char[k]=indexOfCode(input[i]);
					k++;
					if(k==4)
						{
							output_num= ((int)input_char[0]<<18)+((int)input_char[1]<<12)+((int)input_char[2]<<6)+((int)input_char[3]);
							output_char[0]=(unsigned char)((output_num & 0x00FF0000 )>> 16) ;
							output_char[1]=(unsigned char)((output_num & 0x0000FF00 ) >> 8) ;
							output_char[2]=(unsigned char)(output_num & 0x000000FF) ;
							output_char[3]='\0';
							output_str.append((char *)output_char);
							k=0;
						}
				}

			//cout << "decodeBase64 ::: " <<output_str << endl;
			return output_str;

		}


	static int indexOfCode(const char c)
		{
			string code="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

			for(unsigned int i=0;i<code.size();i++)
				{
					if(code[i]==c)
						return i;
				}
			return 0;
		}



};






#endif









