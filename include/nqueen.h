/*******************************************************************************
 * DANIEL'1'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 8-Queue 
 *
 * http://en.wikipedia.org/wiki/Eight_queens_puzzle
 ******************************************************************************/

#ifndef ALGO_NQUEEN_H__
#define ALGO_NQUEEN_H__

#include <stdio.h>
#include <string.h>

namespace alg {
	class QueenN {
		private:
			char **board;
			int cnt,N;
		public:
			void solve() {
//				memset(board, '0', sizeof(board));
				cnt = 0;
				_solve(0);
			}

            void setN(int n) {
				N = n;
				board=new char*[N];
				for (int i=0; i<N; i++) {
					board[i] = new char[N];
					for(int j=0; j<N; j++){
						board[i][j] = '0';
					}
				}
            }
		private:
			void _solve(int row) {	// start from 0
				int i;
				for (i=0;i<N;i++) {
					board[row][i] = '1';
					if (check(row, i)) {
						if (row == N-1) print();
						else _solve(row+1);
					}
					board[row][i] = '0';	// rollback
				}
			}

			void print() {
				printf("chessboard: %d\n",++cnt);
				int i,j;
				for (i=0;i<N;i++) {
					for (j=0;j<N;j++) {
						printf("%c ", board[i][j]);
					}
					printf("\n");
				}
			}

			bool check(int row, int col) {
				int i,j;

				// cannot be same column
				for (i=0;i<row;i++) {
					if (board[i][col] == '1') {
						return false;
					}
				}

				// cannot be diagnal
				i = row-1, j = col-1;
				while (i>=0 && j >=0) {
					if (board[i][j] == '1') {
						return false;
					}
					i--;
					j--;
				}

				i = row-1, j = col+1;
				while (i>=0 && j <N) {
					if (board[i][j] == '1') {
						return false;
					}
					i--;
					j++;
				}

				return true;
			}
	};
}

#endif //ALGO_8QUEEN_H__
