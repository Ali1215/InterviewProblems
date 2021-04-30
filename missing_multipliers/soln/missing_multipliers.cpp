#include <iostream>
using namespace std;
#include <vector>
#include <unordered_set>

int n,m;
//bool flag = true;
int index = 0;


void adjust(long* nums, int j, bool* visited){
	//if (j==0) flag = false;
	for (int i = 0; i<n; i++){
		if (abs(index - i) <= m)
			continue;
		if (nums[i] == 0 && visited[i]==false){
			nums[i] += j;
			visited[i] =true;
			//cout <<nums[i] << ' ';
		}
		else{
			nums[i] *= j;
			//cout <<nums[i] << ' ';
		}
	}
	//cout << endl;
	return;
}


int main(){
	// Declare your variables
	
	// Read the input
	cin >> n >> m;
	// Solve the problem. I believe in you!
	//vector< unordered_set<int> > nums(n);
	long nums[n] = {0};

	long LS[n] = {1};
	long RS[n] = {1};
	bool visited[n] = {false};
	// Output the answer
	
	
	/*
	while (index<n){
		int j;
		cin >>j;
		LS[index]
		index++;
	}*/
	int j;
	cin >> j;
	LS[0] = j;
	nums[0] = j;

	for (int i = 1; i< n; i++){
		cin >> j;
		nums[i] = j;
		LS[i] = j * LS[i-1];
	}

	RS[n-1] = j;
	for(int i = n-2; i>=0; i--){
		RS[i] = nums[i]*RS[i+1];
	}

	for (int i = 0; i<n; i++){
		bool leftend = i-m <= 0;
		bool rightend = i+m >= (n-1);
		if(rightend && leftend){
			cout << 0 << ' ';
			continue;
		}
		else if(rightend){
			cout << LS[i-m-1] << ' ';
			continue;
		}
		else if(leftend){
			cout << RS[i+m+1] << ' ';
			continue;
		}
		else{
			cout << LS[i-m-1] * RS[i+m+1] << ' ';
		}
	}

	//cout << endl;
	//for (int i = 0; i < n; i++){
	//	cout << LS[i] << ' ' << RS[i] << endl;
	//}
	//cout << nums[n-1] << endl;
	return 0;
}