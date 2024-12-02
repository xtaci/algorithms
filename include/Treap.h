// Harun GUNAYDIN
// 01/29/2016

/*
	This is a simple implementation of Treap ( Treap with Implicit Key )
	All operations are performed in O(logN) in average
	It is a min heap in this implementation.
	The key values that helps us construct this min heap treap are chosen randomly and this makes the tree have logN levels in average.
	Indices start from 1.

	http://habrahabr.ru/post/102364/
*/

#ifndef _TREAP_WITH_IMPLICIT_KEY_
#define _TREAP_WITH_IMPLICIT_KEY_
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
namespace alg
{
	template <typename ValueT>
		class Treap
		{
			private:

				class Node
				{
					public:
						ValueT val;
						int r;
						int size;
						Node *left,*right;
						Node() { left = right = NULL; }
						Node( ValueT newValue )
						{
							val = newValue;
							r = rand() * rand();
							size = 1;
							left = right = NULL;
						}
				};

				class TreapException: public std::exception {
					public:
						virtual const char * what() const throw() {
							return "key does not exist";
						}
				} excp_key;

				typedef Node* pNode;				
				pNode root;

				Treap( pNode p )
				{
					delete root;
					root = new Node();
					copy(root,p);
				}

				int sizeOf( pNode p ) { return p == NULL ? 0 : p->size; }
				void update( pNode p )
				{
					if(p) p->size = sizeOf(p->left) + sizeOf( p->right ) + 1;
				}

				void copy(pNode to,pNode from)
				{
					*to = *from;
					if( from->left )
					{
						to->left = new Node();
						copy(to->left,from->left);	
					}
					if( from->right )
					{
						to->right = new Node();
						copy(to->right,from->right);
					}
				}

				/*
					Gets the corresponding node of the x_th index.
				*/	
				pNode get( pNode p , int x )
				{
					int s = sizeOf(p->left);
					if( s + 1 == x ) return p;
					return x <= s ? get( p->left , x ) : get( p->right , x-s-1 );
				}

				void Split( pNode t , pNode &L , pNode &R , int x )
				{
					if( t == NULL ) return void( L = R = NULL );
					int s = sizeOf(t->left) + 1;
					if(s <= x) Split( t->right , t->right , R , x - s ) , L = t;
					else Split( t->left , L , t->left , x ) , R = t;
					update(t);
				}

				void Merge( pNode &t , pNode L , pNode R )
				{
					if( L == NULL ) return void( t = R );
					if( R == NULL ) return void( t = L );
					if( L->r < R->r ) Merge(L->right,L->right,R) , t = L;
					else Merge(R->left,L,R->left) , t = R;
					update(t);
				}

				void print( pNode p , std::ostream& out )
				{
					if( p == NULL ) return;
					print(p->left,out);
					out << p->val << " ";
					print(p->right,out);
				}

				void destruct( pNode p )
				{
					if( p == NULL ) return;
					destruct(p->left);
					destruct(p->right);
					delete p;
				}

			public:

				Treap()
				{
					static bool flag = true;
					root = NULL;
					if(flag)
					{
						srand( time(NULL) );
						flag = false;
					}
				}

				Treap( const Treap <ValueT> &x )
				{
					*this = x;
				}

				~Treap()
				{
					destruct(root);
				}

				friend std::ostream& operator <<( std::ostream &out , Treap <ValueT>& x )
				{
					x.print(out);
					return out;
				}

				Treap <ValueT> & operator = (const Treap <ValueT> &x)
				{
					delete root;
					root = new Node();
					copy(root , x.root);
					return *this;
				}

				void print()
				{
					print(root,std::cout);
				}

				void print(std::ostream& out)
				{
					print(root,out);
				}

				int size()
				{
					return sizeOf(root);
				}

				void push_back( const ValueT data )
				{
					Merge( root , root , new Node(data) );
				}

				void push_back( const Treap <ValueT> data )
				{
					Merge( root , root , data.root );
				}

				void push_front( const ValueT data )
				{
					Merge( root , new Node(data) , root );
				}

				void push_front( const Treap <ValueT> data )
				{
					Merge( root , data.root , root );
				}

				void pop_back()
				{
					pNode t;
					Split( root , root , t , size() - 1 );
				}

				void pop_front()
				{
					pNode t;
					Split( root , t , root , 1 );
				}
				
				/*
					Add just before x_th index
					Means the new element will be at index x.
					x must be in between 1 and the size of the Treap.
				*/
				
				void insert( int x , const ValueT data )
				{
					if( x == size() + 1 ) return push_back(data);
					if( x == 1 ) return push_front(data);
					assert( 2 <= x && x <= size() );
					pNode t1,t2;
					Split( root, t1 , t2, x-1 );
					Merge( root , t1 , new Node(data) );
					Merge( root , root , t2 );
				}

				/*
					Removes the x_th index
				*/
				void remove(int x)
				{
					assert( 1 <= x && x <= size() );
					pNode t1,t2,t3,t4;
					Split( root , t1 , t2 , x-1 );
					Split( t2 , t3 , t4 , 1 );
					Merge( root , t1 , t4 );
				}

				/*
					Removes the interval [a,b]
				*/
				void remove(int a,int b)
				{
					assert( 1 <= a && a <= b && b <= size() );
					pNode t1,t2,t3,t4;
					Split( root , t1 , t2 , b );
					Split( t1 , t3 , t4 , a-1 );
					Merge( root , t3 , t2 );
				}

				void clear()
				{
					destruct(root);
				}

				ValueT get( int x )
				{
					assert( 1 <= x && x <= size() );
					return get(root,x)->data;
				}

				/*
					Returns the interval [a,b]
				*/

				Treap <ValueT> get( int a , int b )
				{
					assert( 1 <= a && a <= b && b <= size() );
					pNode t1,t2,t3,t4;
					Split( root , t1 , t2 , b );
					Split( t1 , t3 , t4 , a-1 );
					Treap <ValueT> res(t4);
					Merge( t1 , t3 , t4 );
					Merge( root , t1 , t2 );
					return res;
				}

				void set( int x , const ValueT data )
				{
					assert( 1 <= x && x <= size() );
					get(root,x)->val = data;
				}

		};
}
#endif