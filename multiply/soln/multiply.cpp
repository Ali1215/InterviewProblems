#include <iostream>
#include <map>
using namespace std;

int main() {
  //int a[100], b[100], product[200];
  int n, m;

  // Read the input
  cin >> m >> n;
  int a[m];
  int b[n];
  //char ans[m+n];
  for (int i = 0; i < m; i++){
    cin >> a[i];
  }
  for (int j = 0; j < n; j++){
    cin >> b[j];
  }

  int prod[m+n] = {0};
  int *mul_temp;
  mul_temp = new int[m+n];
  int t = 0;
  int carry = 0;

  for (int i = m-1; i>=0; i--){
    mul_temp = new int[m+n]{0};
    /*for(int k = 0; k<(m+n); k++){
      cout << mul_temp[k];
    }*/
    //cout << endl;
    for (int j = n-1; j>=0; j--){
        t = a[i]*b[j] + carry;
        carry = 0;
        while (t>=10){
          t -= 10;
          carry++;
        }
        //cout << carry << ' '<< t << ' '<< i+j+1 << endl;
        mul_temp[i+j+1] += t;
        
    }
    mul_temp[i] += carry;
    carry = 0;
    for(int k = 0; k<(m+n); k++){
      
      
      prod[k] += mul_temp[k];
      //cout << mul_temp[k];
    }
    //cout << endl;
    delete[] mul_temp;
    
  }
  for (int l = (n+m-1); l >=0; l--){
    while (prod[l]>9){
      prod[l] -= 10;
      prod[l-1]++;
    }
  }
  for (int h = 0; h< (m+n-1); h++){
    cout << prod[h] << ' ';
  }
  cout << prod[m+n-1] << endl;
  return 0;
}
