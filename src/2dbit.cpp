/*
/* C++ program to implement 2D Binary Indexed Tree 
  
2D BIT is basically a BIT where each element is another BIT. 
Updating by adding v on (x, y) means it's effect will be found 
throughout the rectangle [(x, y), (max_x, max_y)], 
and query for (x, y) gives you the result of the rectangle 
[(0, 0), (x, y)], assuming the total rectangle is 
[(0, 0), (max_x, max_y)]. So when you query and update on 
this BIT,you have to be careful about how many times you are 
subtracting a rectangle and adding it. Simple set union formula 
works here. 
  
So if you want to get the result of a specific rectangle 
[(x1, y1), (x2, y2)], the following steps are necessary: 
  
Query(x1,y1,x2,y2) = getSum(x2, y2)-getSum(x2, y1-1) - 
                     getSum(x1-1, y2)+getSum(x1-1, y1-1) 
  
Here 'Query(x1,y1,x2,y2)' means the sum of elements enclosed 
in the rectangle with bottom-left corner's co-ordinates 
(x1, y1) and top-right corner's co-ordinates - (x2, y2) 
  
Constraints -> x1<=x2 and y1<=y2 
  
    /\ 
 y  | 
    |           --------(x2,y2) 
    |          |       | 
    |          |       | 
    |          |       | 
    |          --------- 
    |       (x1,y1) 
    | 
    |___________________________ 
   (0, 0)                   x--> 


_____________________________________________________________________________________-
Time Complexity:

    Both updateBIT(x, y, val) function and getSum(x, y) function takes O(log(NM)) time.
    Building the 2D BIT takes O(NM log(NM)).
    Since in each of the queries we are calling getSum(x, y) function so answering all the Q queries takes O(Q.log(NM)) time.

Hence the overall time complexity of the program is O((NM+Q).log(NM)) where,
N = maximum X co-ordinate of the whole matrix.
M = maximum Y co-ordinate of the whole matrix.
Q = Number of queries.

Auxiliary Space: O(NM) to store the BIT and the auxiliary array
*/
#include<bits/stdc++.h> 
using namespace std; 

#define N 4 // N-->max_x and max_y 

// A structure to hold the queries 
struct Query 
{ 
	int x1, y1; // x and y co-ordinates of bottom left 
	int x2, y2; // x and y co-ordinates of top right 
}; 

// A function to update the 2D BIT 
void updateBIT(int BIT[][N+1], int x, int y, int val) 
{ 
	for (; x <= N; x += (x & -x)) 
	{ 
		// This loop update all the 1D BIT inside the 
		// array of 1D BIT = BIT[x] 
		for (; y <= N; y += (y & -y)) 
			BIT[x][y] += val; 
	} 
	return; 
} 
int getSum(int BIT[][N+1], int x, int y) 
{ 
	int sum = 0; 

	for(; x > 0; x -= x&-x) 
	{ 
		for(; y > 0; y -= y&-y) 
		{ 
			sum += BIT[x][y]; 
		} 
	} 
	return sum; 
} 
void constructAux(int mat[][N], int aux[][N+1]) 
{ 
	for (int i=0; i<=N; i++) 
		for (int j=0; j<=N; j++) 
			aux[i][j] = 0; 
	for (int j=1; j<=N; j++) 
		for (int i=1; i<=N; i++) 
			aux[i][j] = mat[N-j][i-1]; 

	return; 
} 
void construct2DBIT(int mat[][N], int BIT[][N+1]) 
{ 
	int aux[N+1][N+1]; 
	constructAux(mat, aux); 
	for (int i=1; i<=N; i++) 
		for (int j=1; j<=N; j++) 
			BIT[i][j] = 0; 

	for (int j=1; j<=N; j++) 
	{ 
		for (int i=1; i<=N; i++) 
		{ 
			int v1 = getSum(BIT, i, j); 
			int v2 = getSum(BIT, i, j-1); 
			int v3 = getSum(BIT, i-1, j-1); 
			int v4 = getSum(BIT, i-1, j); 
			updateBIT(BIT, i, j, aux[i][j]-(v1-v2-v4+v3)); 
		} 
	} 

	return; 
} 
void answerQueries(Query q[], int m, int BIT[][N+1]) 
{ 
	for (int i=0; i<m; i++) 
	{ 
		int x1 = q[i].x1 + 1; 
		int y1 = q[i].y1 + 1; 
		int x2 = q[i].x2 + 1; 
		int y2 = q[i].y2 + 1; 

		int ans = getSum(BIT, x2, y2)-getSum(BIT, x2, y1-1)- 
				getSum(BIT, x1-1, y2)+getSum(BIT, x1-1, y1-1); 

		printf ("Query(%d, %d, %d, %d) = %d\n", 
				q[i].x1, q[i].y1, q[i].x2, q[i].y2, ans); 
	} 
	return; 
} 
int main() 
{ 
	int mat[N][N] = {{1, 2, 3, 4}, 
					{5, 3, 8, 1}, 
					{4, 6, 7, 5}, 
					{2, 4, 8, 9}}; 

	int BIT[N+1][N+1]; 
	construct2DBIT(mat, BIT); 
	Query q[] = {{1, 1, 3, 2}, {2, 3, 3, 3}, {1, 1, 1, 1}}; 
	int m = sizeof(q)/sizeof(q[0]); 

	answerQueries(q, m, BIT); 

	return(0); 
} 

