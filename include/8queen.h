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

#ifndef ALGO_8QUEEN_H__
#define ALGO_8QUEEN_H__

#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
namespace alg {
	class Queen8 {
		private:
			std::vector<std::vector<char> > board;
			int cnt;
			std::set<int> column,main_diagonal,opposite_diagonal;
		public:
			void solve(int size=8) {
				board = std::vector<std::vector<char> >(size,std::vector<char>(size,'0'));
				cnt = 0;
				_solve(0);
			}
		private:
			void _solve(int row) {	// start from 0
				int i;
				for (i=0;i<board.size();i++) {
					board[row][i] = '1';
					if (addParameters(row, i)) {
						if (row == board.size()-1) print();
						else _solve(row+1);
						removeParameters(row,i); // rollback
					}
					board[row][i] = '0';
				}
			}

			void print() {
				printf("chessboard: %d\n",++cnt);
				int i,j;
				for (i=0;i<board.size();i++) {
					for (j=0;j<board.size();j++) {
						printf("%c ", board[i][j]);
					}
					printf("\n");
				}
			}

			bool addParameters(int row,int col){
				if(column.find(col)!=column.end() 
					|| main_diagonal.find(row-col)!=main_diagonal.end() 
					|| opposite_diagonal.find(row+col)!=opposite_diagonal.end())
					return false;
				column.insert(col);
				main_diagonal.insert(row-col);
				opposite_diagonal.insert(row+col);
				return true;
			}

			bool removeParameters(int row,int col){
				column.erase(col);
				main_diagonal.erase(row-col);
				opposite_diagonal.erase(row+col);
			}
	};
}

#endif //ALGO_8QUEEN_H__
