#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
    vector<char> v(str.begin(), str.end());
    vector<char> v1;
    
    char ch[] = { ',','\0'}; 
    cout<<ch[0]<<endl;
           
    return ;

}

int main() {

    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}
