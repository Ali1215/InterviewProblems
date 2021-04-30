// Ali Muneer - 1615694
#include <iostream> // this is the only header you may use (for cin, cout, and endl)
using namespace std;

void reverse(int* begin, int* end){
    // find difference between back and front
    int diff = end - begin;
    int temp;

    // switch elements using temp, only until halfway, exclusive
    for (int i = 0; i < (diff / 2); i++){
        temp = *(end - i - 1);
        *(end - i - 1) = *(begin + i);
        *(begin + i) = temp;

    }
    return;
}
int main(){
    int len;
    cin >> len;
    int seq[len];

    int Leaders[len]; // there will be max "len" leaders
    int leadersFound = 0;


    for (int i = 0; i < len; i++){
        cin >> seq[i];
    }
    
   
    // the last element of the array is always a leader
    // initialize variables to last element
    int lastLead = len - 1;
    int maxLead = seq[len - 1];
    Leaders[0] = maxLead;

    // go backwards from end of list, new maximum is a leader
    for (int j = len - 1; j >= 0; j--){
        // element is a leader if a new maximum is found
        if (seq[j] > maxLead){
            maxLead = seq[j];
            leadersFound++;
            Leaders[leadersFound] = maxLead; // add found leader to array of leaders
            
            reverse(seq + j + 1, seq + lastLead); //reverse from new leader to old leader
            lastLead = j; // update index of most recent leader
        }
    }
    reverse(seq, seq + lastLead); // reverse to first leader from beginning of list

    // print out all Leaders found, in reverse
    // since they were found in reverse
    for (int i = leadersFound; i > 0; i--){
        cout << Leaders[i] << ' ';
    }
    // print last one without whitespace at end
    cout << Leaders[0] << endl;

    for (int i = 0; i<len - 1; i++)
        cout << seq[i] << ' ';
    
    // print last one without whitespace at end
    cout << seq[len - 1] << endl;
}
