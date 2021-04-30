// Remember, style matters!
#include <iostream>
#include <unordered_set>
/*  Ali Muneer - 1615694
    Weekly Interview Question 3
    CMPUT 275, Winter 2021
*/
using namespace std;

int main (){
    unordered_set<int> prices;
    int n, T;
    int temp; //temporary variable to store prices from cin
    cin >> n >> T; //number of items "n" and total price "T"
    for (int i = 0; i<n; i++){
        cin >> temp;
        prices.insert(temp);
    }
    //iterate through all the prices
    for (auto it = prices.begin(); it != prices.end(); it++){
        // if a price is found that would make it add up to T
        // and that value is not itself, print YES and exit
        if (prices.find(T-*it) != prices.end() && prices.find(T-*it) != it){
            cout << "YES" << endl;
            return 0;
        }
    }
    // none is found
    cout << "NO" << endl;
    return 0;
}