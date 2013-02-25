/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * A* ALGORITHM
 * 
 * Features:
 *    In computer science, A* (pronounced "A star" ,is a computer algorithm
 * that is widely used in pathfinding and graph traversal, the process of
 * plotting an efficiently traversable path between points, called nodes. Noted 
 * for its performance and accuracy, it enjoys widespread use. (However, in 
 * practical travel-routing systems, it is generally outperformed by algorithms 
 * which can pre-process the graph to attain better performance.[1])
 *
 * http://en.wikipedia.org/wiki/A*_search_algorithm
 *
 ******************************************************************************/

#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "heap.h"
#include "hash_table.h"

/**
 * A-Star algorithm result;
 */
struct AStarResult {
	int * path; // the path format:
 				// [X1Y1X2Y2X3Y3.....XnYnX1Y1] 
 				// interleaving X,Y coordinate, the last one is soure coordinate
	int num_nodes;
};

#define WALL 0xFFFF

static inline float __astar_estimate(int x1, int y1, int x2, int y2);
/**
 * the A* algorithm
 * search a path from (x1,y1) to (x2,y2)
 * a integer representing path is returned, you should free it after. 
 * 
 * 
 */
static struct AStarResult *
astar(int nrow, int ncol, const int grid[nrow][ncol], int x1, int y1, int x2, int y2)
{
	// The set of nodes already evaluated.
	bool * closedset= (bool*)malloc(sizeof(bool)*nrow*ncol);
	memset(closedset, false, sizeof(closedset));

	// the set of tentavie nodes to be evaluated,
	// initialy containing the start node	
	// [x,y] encoded in x*ncol+y	
	struct Heap * openset = heap_init(nrow*ncol);
	heap_insert(openset, 0, (uintptr_t)(x1*ncol + y1));

	// The map of navigated nodes.	
	struct HashTable * came_from = hash_table_create(nrow*ncol);

	// Cost from start along best known path.	
	float * g_score = (float *)malloc(sizeof(float)*nrow*ncol);
	g_score[x1*ncol+y1] = 0.0f;

	// Estimated total cost from start to goal through y.
	float * f_score = (float *)malloc(sizeof(float)*nrow*ncol);
	f_score[x1*ncol+y1] = g_score[x1*ncol+y1] + __astar_estimate(x1,y1,x2,y2);

	struct AStarResult * as = (struct AStarResult*)malloc(sizeof(struct AStarResult));
	as->path = NULL;
	as->num_nodes = 0;

	while(!heap_is_empty(openset)) {
		int value = (int)HEAP_MIN_VALUE(openset);
		int cx = value/ncol;
		int cy = value%ncol;

		if(cx == x2 && cy==y2) {	// we reached (x2,y2)
			// reconstruct path & return
			int tmp = x2*ncol+y2;
			while((tmp=(int)hash_table_get(came_from, tmp)) != x1*ncol+y1) {
				as->num_nodes++;
			}

			as->path = (int*)malloc(sizeof(int)*2*as->num_nodes);

			tmp = x2*ncol+y2;
			int idx=0;
			while((tmp=(int)hash_table_get(came_from, tmp)) != x1*ncol+y1) {
				as->path[idx++] = tmp/ncol;
				as->path[idx++] = tmp%ncol;
			}

			return as;
		}

		heap_delete_min(openset);
		closedset[cx*ncol + cy] = true;

		// for each neighbor
		int nx, ny;
		for(nx=cx-1;nx<=cx+1;nx++) {
			if (nx<0 || nx>=ncol) continue;
			for(ny=cy-1;ny<=cy+1;ny++) {
				if (ny<0 || ny>=nrow) continue;

				// except the wall;
				if(grid[nx][ny] == WALL) continue;
				// except the cur itself
				if(nx == cx && ny==cy) continue;
				// if neighbour in the closed set	
				if(closedset[nx*ncol+ny]) continue;	
		
				float tentative = g_score[cx*ncol+cy] + 1.41421f; //sqrt(2)
			
				// if neighbour not in the openset or dist < g_score[neighbour]	
				if (heap_find_value(openset, nx*ncol+ny) < 0 ||
					tentative < g_score[nx*ncol+ny]) {
					hash_table_set(came_from, nx*ncol+ny, cx*ncol+cy); // record path
					g_score[nx*ncol+ny] = tentative;
					f_score[nx*ncol+ny] = tentative + __astar_estimate(nx,ny,x2,y2);
					if (heap_find_value(openset, nx*ncol+ny) < 0) {
						heap_insert(openset, f_score[nx*ncol+ny], nx*ncol+ny);
					}
				}
			}
		}
	}

	return as;
}

static inline float
__astar_estimate(int x1, int y1, int x2, int y2)
{
	return sqrtf((x2-x1) * (x2-x1) + (y2-y1)*(y2-y1));
}

#endif //
