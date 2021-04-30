#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	// declare your variables
	int n;
	
	// read the input
	cin >> n;
	char p[n];
	cin >> p;
	// solve, good luck!
	sort(p, p+(n));
	int ans = 0;
	int i = 1;
	//cout << p << endl;
	while (i<(n)){
		if (p[i-1] == p[i]){
			ans = ans + 2;
			i++;
		}
		i++;
	}
	if ((ans%2 == 0) && (n != ans)){
		cout<< ans+1 << endl;
	}
	else{
		cout << ans << endl;
	}
	return 0;
}
