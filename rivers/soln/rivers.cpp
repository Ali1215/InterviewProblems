// Ali Muneer 1615694
#include <iostream>

using namespace std;

int toOcean(int* rivers, int r1, int* rivtoOcean){
    /*
    Description:  This function recieves a list of rivers and returns an array
                    that indicated how it branches to the ocean

    args: rivers    = integer array that indicates how the rivers branch
          r1        = starting river
          rivtoOcean = integer array that will be modified to show the path taken
                        to the ocean
    
    returns: nodes = the amount of rivers passed before it reaches the ocean
  */
    
    //first river visited is the river itself
    rivtoOcean[0] = r1;
    int nodes = 1;
    
    //keep on traversing rivers, adding each river to the array
    //and incrementing the amount of nodes
    while (rivers[r1 - 1] != 0){
        rivtoOcean[nodes] = rivers[r1-1];
        r1 = rivers[r1 - 1];
        nodes++;
    }
    rivtoOcean[nodes+1] = 0;
    return nodes;
    
}

int query(int* rivers, int numRivers, int r1, int r2){
        /*
    Description:  This function recieves a list of rivers and returns one
                    that two specific rivers meet at.

    args: rivers    = integer array that indicates how the rivers branch
          numRivers = number of rivers in total
          r1        = one river to compare
          r2        = second river to compare

    returns: int = the river where r1 and r2 connect
    */
    
    
    //handle edge cases where the rivers are the same
    if (r1 == r2){
        return r1;
    }
    //if either 'river' is the ocean then return the ocean
    if (r1 == 0 || r2 == 0){
        return 0;
    }

    //initialize array that will hold the rivers visited
    //use numRivers as size since that will be the max length
    int r1toOcean[numRivers] = {0};
    int r2toOcean[numRivers] = {0};
    
    int r1branches = toOcean(rivers, r1, r1toOcean);
    int r2branches = toOcean(rivers, r2, r2toOcean);
    

    //start at end of array where ocean is found and increment backwards
    //unti; difference is found
    bool start1reached = false;
    while (r1toOcean[r1branches] == r2toOcean[r2branches]){
        if (r1branches>0){
            //only increment if branches remain above 0
            r1branches--;
        }
        else{
            start1reached = true;
        }
        if (r2branches>0){
            //only increment if branches remain above 0
            r2branches--;
        }
        
    }
    if (start1reached){
        return r2toOcean[r2branches + 1];
    }
    return r1toOcean[r1branches + 1];
    
    


}

int main(){

    //store the number of rivers and amount of queries to be made
    int numRivers,queries;
    cin >> numRivers >> queries;
    int rivers[numRivers];
    int r1, r2;
    
    //populate array of rivers showing how they branch
    for (int i = 0; i < numRivers; i++)
        cin >> rivers[i];
    
    //execute each query
    for (int j = 0; j < queries; j++){
        cin >> r1 >> r2;
        
        cout << query(rivers, numRivers, r1, r2) << endl;
    }
    return 0;

}