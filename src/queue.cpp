#include <iostream> 
#include <queue> 
using namespace std; 
  
void showq(queue <int> q) 
{ 
    
    while (!q.empty()) 
    { 
        cout << '\t' << q.front(); 
        q.pop(); 
    } 
    cout << '\n'; 
} 
  
int main() 
{ 
    queue <int> myq; 
    myq.push(10); 
    myq.push(20); 
    myq.push(30); 
  
    cout << "The queue gquiz is : "; 
    showq(myq); 
  
    cout << "\ngquiz.size() : " << myq.size(); 
    cout << "\ngquiz.front() : " << myq.front(); 
    cout << "\ngquiz.back() : " << myq.back(); 
  
    cout << "\ngquiz.pop() : "; 
    myq.pop(); 
    showq(myq); 
  
    return 0; 
} 