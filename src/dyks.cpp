#include <iostream>
#include<time.h>
using namespace std;

int max(int a, int b) { return (a > b)? a : b; }
// Returns the maximum value that can be put in a knapsack of capacity W
int knapsack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n+1][W+1];
    
    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i==0 || w==0)
                K[i][w] = 0;
            else if (wt[i-1] <= w)
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
            else
                K[i][w] = K[i-1][w];

            cout<<K[i][w]<<"\t";
        }
        cout<<"\n";
    }


    
    return K[n][W];
}

int main()
{
    int val[] = {1, 6, 18, 22, 28, 31};
    int wt[] = {1,2,5,6,7,8};
    int  W = 15;
    int n = sizeof(val)/sizeof(val[0]);
    time_t start,end;
    
    chrono::time_point<chrono::system_clock>t1,t2;
    t1=chrono::system_clock::now();

    int v =knapsack(W, wt, val, n);
    cout<< "\nValue ="<< v;
    t2=chrono::system_clock::now();
    
    chrono::duration<double, micro> t3 = t2-t1;
    cout<<"\nTime Taken "<<t3.count()<< " microseconds"<<endl;
    return 0;
}