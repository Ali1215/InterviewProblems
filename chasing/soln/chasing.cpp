#include <iostream>

using namespace std;
long int S,A;
int count = -1;
int recur(int arr[], int target){
  count++;
  if (count > A)
    return S;
  
  if ((arr[target - S] < S) || (arr[target - S] > (S+A))){
    
    return arr[target - S];
  }
  return recur(arr, arr[target - S]);

}


int main() {
  // declare variables
  
  cin >> S >> A;

  int array[A];
  for (int i = 0; i<A; i++)
    cin >> array[i];


  int ans = recur(array, S);
  // solve the problem
  if (ans == S){
    cout << "There was a cycle" << endl;
    return 0;
  }
  cout << ans << endl;
  // print the output

  return 0;
}
