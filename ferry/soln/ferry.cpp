#include <iostream>
using namespace std;

#include <map>

int main() {
	// Read in the input
	int w, e;
	cin >> w >> e;

	map<int, bool> cars;
	
	bool current = true;

	for (int i = 0; i<w; i++){
		int temp;
		cin >> temp;
		cars[temp] = true;
	}
	for (int i = 0; i<e; i++){
		int temp;
		cin >> temp;
		cars[temp] = false;
	}
	int time = 0;
	for (auto i = cars.begin(); i != cars.end(); i++){
		if ((*i).second == current){
			if (time < (*i).first){
				time = (*i).first;
			}
			
			time += 100;
			current = !current;
			continue;
		}
		else{
			 //cross river
			if (time < (*i).first){
				time = (*i).first;
			}
			time += 200; //cross river
		}
	}
	cout << time << endl;
	
	// Solve the problem


	// Output the result

	return 0;
}