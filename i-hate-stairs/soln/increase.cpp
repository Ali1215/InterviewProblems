#include <iostream>

using namespace std;

int main() {
  // Good luck! The term is almost over!
  int n;
  cin >> n;
  int cur = 0;
  int prev = 0;
  cin >> prev;
  int diff = 0;
  int ans  = 0;
  for(int i = 1; i<n; i++){
    cin >> cur;
    diff = cur - prev;
    if (diff > 0){
      ans += diff;
    }
    prev = cur;
  }
  cout << ans << endl;;
  return 0;
}
