// Remember, style matters!
// While you may rely upon additional functions 
// ensure isprime and twinprime follow the specifications.

#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n){
    double limit = sqrt(n); 
    // one of two factors will always be less than square root of num
    // only up until this limit needs to be tested

    int factor = 2; 
    if (n == 2){
        return true; // check the only case where even n is prime
    }
    // now if even, it is not prime
    if (n % factor == 0){
        return false;
    }
    //otherwise check all odd factors up until limit
    factor++;
    while(factor <= limit){
        if (n % factor == 0){
            return false; //remainder of 0 for any factor means it is not prime
        }
        factor = factor + 2; //advance to next odd factor
    }
    // function is prime if no factor gave remainder of 0
    return true;
}

void twinPrimes(int k){
    int twinOne = 3; //lowest odd number
    int twinTwo;
    int pairCount = 0;
    while (pairCount < k){
        while (!isPrime(twinOne)){
            twinOne = twinOne + 2; //add odd numbers until prime
        }
        // test if next odd number is a prime
        twinTwo = twinOne + 2;
        if (isPrime(twinTwo)){
            cout << twinOne << ' ' << twinTwo << endl;
            // print twinPrimes if next odd number is prime
            pairCount++;
        }
        // advance twinOne to look for next prime number
        twinOne = twinTwo;

    }

}

bool prime;

int main(){
    int n; char c;
    cin >> c >> n; // input variables
    if (c=='p'){
        prime = isPrime(n);
        if (prime){
            cout << "prime" << endl;
        }
        else{
            cout << "not prime" << endl;
        }
    }
    if (c=='t'){
        twinPrimes(n);
    }
    
    return 0;
}
