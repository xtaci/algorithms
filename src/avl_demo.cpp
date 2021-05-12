#include <iostream>
#include "avl.h"

using namespace std;
using namespace alg;

const unsigned N = 4096*32;
const unsigned N_ELEMS_TO_REMOVE = N-128; // Must be between 0 and N-1

template <typename T> 
void printTreeStatus(const AVL<T> &t) {
    cout << "----------------------------------------" << endl;
    if (t.isEmpty()) cout << "The tree is empty" << endl;
    else {
        cout << "Tree root is: " << t.root() << endl;
        cout << "Tree height is: " << t.height() << endl;
        cout << "Tree contains " << t.size() << " elements" << endl;
    }
    cout << "----------------------------------------" << endl;
}

int main()
{
    int values[N];

    AVL<int> avl;

    cout << "Populating the tree with " << N << " random values... ";
    for (unsigned i = 0; i < N; ++i) {
        values[i] = rand();
        avl.insert(values[i]);
    }
    cout << "Done" << endl;

    printTreeStatus(avl);

    for (unsigned i = 0; i < N; ++i) {
        unsigned idx = rand() % N;
        if (!avl.contains(values[idx])) 
	        cout << "ERROR: Value " << values[idx] << " was inserted and not found!" << endl;
    }

    cout << "Now removing a random element from the tree... ";
    unsigned idx = rand() % N;
    avl.erase(values[idx]);
    cout << "Done" << endl;

    printTreeStatus(avl);
    
    cout << "Now removing the root of the tree " << N_ELEMS_TO_REMOVE << " times... ";
    for (unsigned i = 0; i < N_ELEMS_TO_REMOVE; ++i) {
        avl.erase(avl.root());
    }
    cout << "Done" << endl;

    printTreeStatus(avl);

    // Outputting to cerr so the output can be redirected with ./avl_demo 2> <name>.gvz
    cout << "Do you want to output the GraphViz representation of the tree to the cerr stream (Y/n)? ";
    char usrInput;
    cin >> usrInput;
    if (usrInput == 'Y' || usrInput == 'y') avl.toGraphViz(cerr, "AVL");
    
    return 0;
}

