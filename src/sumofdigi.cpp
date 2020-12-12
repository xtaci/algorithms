#include<iostream>
using namespace std;
//SUM OF DIGITS (RECURS)

sum2(int n){
	
	if(n<10) return n;
	return sum2(n/10) + n%10;
}

int main(){
	int num;
	cin>> num;
	//s=sum(num, a);
	cout<< "The sum is : "<<sum2(num);
}






// sum(int n, int a){
// 	int s;
// 	if(n==0) return a;

// 	a = a + n%10;
// 	cout<<" n= "<<n<<"\n";
// 	cout<<" a= "<<a<<"\n";

// 	s =sum(n/10,a);

// 	return s;
// }