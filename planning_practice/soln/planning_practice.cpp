#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	// Declare your variables
	int n;
	int t;
	cin >> n >>t;
	
	int leave[n];
	int ret[n];

	for (int i=0; i<n; i++)
	    cin >> leave[i] >> ret[i];

    int *l = max_element(leave, leave + n);
	int *r = min_element(ret, ret + n);

	if (*r <= *l){
		cout << "IMPOSSIBLE" << endl;
	}
	else{
		
		int h = *r - *l;
		int i = h;
		int days = 1;

		while (i<t){
			i = i+h;
			days++;

		}
		cout << days << endl;
	}
	
	// Read the input

	// Solve the problem. Good luck! :)

	// Output the answer

	
	return 0;
}