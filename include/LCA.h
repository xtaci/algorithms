/*******************************************************************************
 *
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _
 * /--\ | (_| (_) |  |  |_ | | | | | _>
 *         _|
 *
 * LCA Finding using Binary Lifting and Dynamic Programming
 *
 * Features:
 * 1. Answers Query about LCA of two nodes in O(log N)
 *          where N is the total number of nodes in a tree.
 *
 * https://en.wikipedia.org/wiki/Lowest_common_ancestor
 * http://www.csegeek.com/csegeek/view/tutorials/algorithms/trees/tree_part12.php
 ******************************************************************************/

#ifndef LCA_H
#define LCA_H
#include <vector>

class LCA
{
    public:
        LCA(std::vector< std::pair<int,int> > edges);
        int lcaQuery(int a, int b);

    private:
        int getMaxLog();
        void initDP();
        void dfs(int currentNode, int currentParent);
        std::vector< std::vector<int> > adjList, binaryLiftDp;
        std::vector<int> parent, nodeHeight;
        std::vector<bool> visited;
        int _numberOfNodes, _maxLog;
};

#endif // LCA_H
