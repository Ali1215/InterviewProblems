#include <iostream>
using namespace std;

int main(){
	// declare your variables
	int n, m;
	// read the input
	cin >> n >> m;
	// solve, good luck!
	int i = 1;
	
	if (n==1){
		cout << "BAD" << endl;
		return 0;
	}
	while(i <= m){
		i = i*n;
	}
	//cout << i;
	if ((i/n)==m){
		cout << "GOOD" << endl;
	}
	else{
		cout << "BAD" << endl;
	}
	return 0;
}
