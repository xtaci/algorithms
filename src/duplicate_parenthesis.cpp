#include<iostream>
#include<stack>
using namespace std;

bool balancedParanthesis(char *a){

	stack<char> s;

	for(int i=0;a[i]!='\0';i++){
		char ch = a[i];
		switch(ch){
			case '[':
			case '(':
			case '{': s.push(ch);break;

			case ']':if(!s.empty()&&s.top()=='['){
							s.pop();
							break;
					 }
					 else{
					 	return false;
					 }
			case '}':if(!s.empty()&&s.top()=='{'){
							s.pop();
							break;
					 }
					 else{
					 	return false;
					 }
			case ')':if(!s.empty()&&s.top()=='('){
							s.pop();
							break;
					 }
					 else{
					 	return false;
					 }

		}
	}
	if(!s.empty()){
		return false;
	}
	else{
		return true;
	}

}

int main(){

	char a[100];
	cin.getline(a,100);
	if(balancedParanthesis(a)){
		cout<<"Balanced !";
	}
	else{
		cout<<"Not balanced expression!";
	}
	return 0;
}