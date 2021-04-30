#include <iostream>
using namespace std;

int main() {
    int n;
    int q;
    // Read in the input
    cin >> n >> q;
    // Solve the problem
    int seconds[n + 1];
    seconds[0] = 0;
    // Output the result
    int sumsofar = 0;
    int temp;
    for (int i = 1; i < (n+1); i++){
        cin >> temp;
        sumsofar += temp;
        seconds[i] = sumsofar;
        //cout << sumsofar << endl;
    }
    int q1, q2;
    //int sum;
    for (int i = 0; i < q; i++){
        cin >> q1 >>q2;
        //sum = 0;
        
        cout << seconds[q2] - seconds[q1-1] << endl;
    }
    return 0;
}