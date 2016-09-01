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

#ifndef ALGO_ASTAR_H__
#define ALGO_ASTAR_H__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "heap.h"
#include "hash_table.h"
#include "2darray.h"

namespace alg {
	class AStar {
		public:
			/**
			 * A-Star algorithm result;
			 */
			struct AStarResult {
				int * path; // the path format:
				// [X1Y1X2Y2X3Y3.....XnYnX1Y1] 
				// interleaving X,Y coordinate
				int num_nodes;
				~AStarResult() 
				{
					delete [] path;
					path = NULL;
				}
			};

			static const unsigned char WALL = 0xFF;

		private:
			const Array2D<unsigned char> & m_grid;	
			// the openset
			Heap<uint32_t> m_openset;
			// The set of nodes open -- for fast testing of a point in openset. heap contains test is quite slow -- O(n)
			Array2D<bool> m_openset_grid;
			// The set of nodes already evaluated.
			Array2D<bool> m_closedset;
			// Cost from start along best known path.	
			Array2D<float> g_score;
			// Estimated total cost from start to goal through y.
			Array2D<float> f_score;
		public:
			AStar(const Array2D<unsigned char> & grid) :
				m_grid(grid), 
				m_openset(grid.row()*grid.col()),
				m_openset_grid(grid.row(),grid.col()),
				m_closedset(grid.row(),grid.col()),
				g_score(grid.row(),grid.col()),
				f_score(grid.row(),grid.col()) { 
					m_openset_grid.clear(false);
					m_closedset.clear(false);
				}

			/**
			 * the A* algorithm
			 * search a path from (x1,y1) to (x2,y2)
			 * a integer representing path is returned, you should delete it after. 
			 */
			AStarResult * run(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
				static float SQRT2 = 1.414213562373095;
				uint32_t nrow = m_grid.row();
				uint32_t ncol = m_grid.col();

				// test wheather the (x1, y1) is the wall, we don't do stupid searching.
				if (m_grid(x1, y1) == WALL) {
					return NULL;
				}

				// the set of tentavie nodes to be evaluated,
				// initialy containing the start node	
				// encoding [x,y] to [x*ncol + y]
				// using binary heap ...
				m_openset.push(0, x1*ncol+y1);
				// record the starting point in openset_grid
				m_openset_grid(x1,y1) = true;

				// The map of navigated nodes.	
				HashTable<uint32_t, uint32_t> came_from(nrow*ncol);

				g_score(x1,y1) = 0.0f;
				f_score(x1,y1) = g_score(x1,y1) + estimate(x1,y1,x2,y2);

				AStarResult * as = new AStarResult;
				as->path = NULL;
				as->num_nodes = 0;

				// the main A*algorithm
				while(!m_openset.is_empty()) {
					Heap<uint32_t>::elem e = m_openset.pop();
					uint32_t value = e.data;
					int	cx = value/ncol;
					int	cy = value%ncol;

					if(cx == (int)x2 && cy==(int)y2) {	// great! we've reached the target position (x2,y2)
						// reconstruct path
						as->num_nodes = 2;
						uint32_t tmp = x2*ncol+y2;
						while((tmp=came_from[tmp]) != x1*ncol+y1) {
							as->num_nodes++;
						}

						as->path = new int[2*as->num_nodes];

						tmp = x2*ncol+y2;
						int idx=0;
						as->path[idx++] = x2;
						as->path[idx++] = y2;
						while((tmp=came_from[tmp]) != x1*ncol+y1) {
							as->path[idx++] = tmp/ncol;
							as->path[idx++] = tmp%ncol;
						}
						as->path[idx++] = x1;
						as->path[idx++] = y1;
						return as;
					}

					// move it into closed set.
					m_closedset(cx, cy) = true;
					m_openset_grid(cx, cy) = false;

					// for each valid neighbor of current position
					int nx, ny;
					for(nx=cx-1;nx<=cx+1;nx++) {
						for(ny=cy-1;ny<=cy+1;ny++) {
							// exclude invalid position
							if (nx<0 || nx>=(int)ncol || ny<0 || ny>=(int)nrow) continue;
							// except the cur itself
							if(nx == cx && ny==cy) continue;
							// except the wall;
							if(m_grid(nx,ny) == WALL) continue;
							// exclude the neighbour in the closed set	
							if(m_closedset(nx,ny)) continue;

							// ok, we got a valid neighbour
							float tentative = g_score(cx,cy);
							if (nx == cx || ny == cy) {	// horizontal/vertical neighbour is near
								tentative += 1;
							} else { // diagonal neighbour is farther.
								tentative += SQRT2;
							}

							// if neighbour not in the openset or dist < g_score[neighbour]	
							if (!m_openset_grid(nx,ny) || tentative < g_score(nx,ny)) {
								came_from[nx*ncol+ny] = cx*ncol+cy; // record the path
								g_score(nx,ny) = tentative;			// update path cost for current position
								f_score(nx,ny) = tentative + estimate(nx,ny,x2,y2);	// record path cost to this neighbour
								if (!m_openset_grid(nx,ny)) {	// only insert the neighbour if it hasn't been add to the openset.
									m_openset.push(f_score(nx,ny), nx*ncol+ny);
									m_openset_grid(nx,ny) = true;
								}
							}
						}
					}
				}

				// haven't reached target
				return as;
			}
		private:
			/**
			 * Estimate the cost for going this way, such as:
			 * acrossing the swamp will be much slower than walking on the road.
			 * design for you game.
			 */
			inline float estimate(int x1, int y1, int x2, int y2) const {
				return sqrtf((x2-x1) * (x2-x1) + (y2-y1)*(y2-y1));
			}
	};

}

#endif //
