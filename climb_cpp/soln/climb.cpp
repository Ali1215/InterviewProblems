#include <iostream>
using namespace std;

int main() {
    // I've heard that climbing is a good workout for your legs.
    // But I haven't moved from my chair in years, so I might not be the best person to ask.
    // Good luck with the problem! The term is almost over! :)
	int n;
	cin >> n;
	// Read in the input
	int in[n];
	cin >> in[0];

	

	int ans[n];
	
	for (int i = 1; i < n; i++){
		cin >> in[i];
		if (in[i] <= in[i-1]){
			ans[i-1] = 0;
		}
		else{
			//cout << "test" << endl;
			int j = i-2;
			
			while (ans[j] != 0){
				ans[j]++;
				//cout << j << endl;
				j--;
			}
			ans[i-1] = 1;
		}
	}
	
	for (int c = 0; c<n-1; c++) cout << ans[c] << ' ';
	cout << 0 << endl;

	// Solve the problem


	// Output the result

	return 0;
}