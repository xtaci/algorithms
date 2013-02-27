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
#include "2darray.h"

namespace alg
{
	/**
	 * A-Star algorithm result;
	 */
	struct AStarResult {
		int * path; // the path format:
					// [X1Y1X2Y2X3Y3.....XnYnX1Y1] 
					// interleaving X,Y coordinate, the last one is soure coordinate
		int num_nodes;
	};

	struct Coord {
		uint32_t x;
		uint32_t y;
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
	astar(const Array2D<int> & grid, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
	{
		uint32_t nrow = grid.row();
		uint32_t ncol = grid.col();
		// The set of nodes already evaluated.
		Array2D<bool> closedset(nrow, ncol);
		closedset.clear(false);

		// the set of tentavie nodes to be evaluated,
		// initialy containing the start node	
		// encoding [x,y] to [x*ncol + y]
		// using binary heap ...
		Heap<uint32_t> openset(nrow*ncol);
		openset.insert(0, x1*ncol+y1);

		// The map of navigated nodes.	
		HashTable<uint32_t> came_from(nrow*ncol);

		// Cost from start along best known path.	
		Array2D<float> g_score(nrow, ncol);
		g_score(x1,y1) = 0.0f;

		// Estimated total cost from start to goal through y.
		Array2D<float> f_score(nrow,ncol);
		f_score(x1,y1) = g_score(x1,y1) + __astar_estimate(x1,y1,x2,y2);

		struct AStarResult * as = (struct AStarResult*)malloc(sizeof(struct AStarResult));
		as->path = NULL;
		as->num_nodes = 0;

		while(!openset.is_empty()) {
			uint32_t value = openset.min_value();
			int	cx = value/ncol;
			int	cy = value%ncol;

			if(cx == (int)x2 && cy==(int)y2) {	// we reached (x2,y2)
				// reconstruct path & return
				uint32_t tmp = x2*ncol+y2;
				while((tmp=came_from[tmp]) != x1*ncol+y1) {
					as->num_nodes++;
				}

				as->path = (int*)malloc(sizeof(int)*2*as->num_nodes);

				tmp = x2*ncol+y2;
				int idx=0;
				while((tmp=came_from[tmp]) != x1*ncol+y1) {
					as->path[idx++] = tmp/ncol;
					as->path[idx++] = tmp%ncol;
				}
				return as;
			}

			openset.delete_min();
			closedset(cx, cy) = true;

			// for each neighbor
			int nx, ny;
			for(nx=cx-1;nx<=cx+1;nx++) {
				if (nx<0 || nx>=(int)ncol) continue;
				for(ny=cy-1;ny<=cy+1;ny++) {
					if (ny<0 || ny>=(int)nrow) continue;

					// except the wall;
					if(grid(nx,ny) == WALL) continue;
					// except the cur itself
					if(nx == cx && ny==cy) continue;
					// if neighbour in the closed set	
					if(closedset(nx,ny)) continue;	
			
					float tentative = g_score(cx,cy) + 1.41421f; //sqrt(2)
				
					// if neighbour not in the openset or dist < g_score[neighbour]	
					if (openset.find_value(nx*ncol+ny) < 0 || tentative < g_score(nx,ny)) {
						came_from[nx*ncol+ny] = cx*ncol+cy; // record path
						g_score(nx,ny) = tentative;
						f_score(nx,ny) = tentative + __astar_estimate(nx,ny,x2,y2);
						if (openset.find_value(nx*ncol+ny) < 0) {
							openset.insert(f_score(nx,ny), nx*ncol+ny);
						}
					}
				}
			}
		}
		return as;
	}

	static void astar_free(struct AStarResult * as)
	{
		if (as->path) free(as->path);
		free(as);
	}

	static inline float
	__astar_estimate(int x1, int y1, int x2, int y2)
	{
		return sqrtf((x2-x1) * (x2-x1) + (y2-y1)*(y2-y1));
	}
}

#endif //
