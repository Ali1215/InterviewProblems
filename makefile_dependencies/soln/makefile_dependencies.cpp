// Remember, style matters!
//Ali Muneer
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;
unordered_map<string,vector<string>>  make; //map holding all of the dependencies per target
unordered_set<string> prev_made; //to hold made targets


vector<string> recurse(string target){
    /*
    Description:  recursively searches through dependencies a target
                    and "makes" each dependencies (and their dependencies etc)

    args: target = target whos dependencies to make
    
    returns: vector<string> vector of strings where the "made" dependencies will be stored
    */
    
    vector<string> ans;
    
    for (auto x: make[target]){
        //loop over dependencies
        if (prev_made.find(x) != prev_made.end() || make.find(x) == make.end()){  
            continue; //skip if previously made or not a target
        }
        else{
            vector<string> temp;
            temp = recurse(x); //check dependencies for each dependency
            ans.insert(ans.end(), temp.begin(), temp.end()); //append dependency's dependencies
            ans.insert(ans.end(), x);//dependency is now made
            prev_made.insert(x);
            

        }
    }
    prev_made.insert(target); //target is now made once all dependencies are made
    return ans;
}

int main() {
    int n,m;
    cin >> n >> m;//number of targets and number of make commands
    
    //construct makefile structure
    for (int i = 0; i<n; i++){
        int numd;//number of dependencies
        string target;
        cin >> numd >> target;
        target.pop_back(); //remove colon
        make[target]; //initialize empty vector
        for (int j = 0; j< numd;j++){
            string depend;
            cin >> depend;
            make[target].push_back(depend);//add each dependency
        }
        
    }
    for (int j = 0; j<m; j++){
        string command;
        string foo;//ignore "make"
        cin >> foo >> command;
        if (prev_made.find(command) != prev_made.end()){
            //skip if already made
            cout << "make: " << "`" << command << "'" << " is up to date." << endl;
            continue;
        }

        vector<string> ans = recurse(command);
        
        for (auto it = ans.begin(); it != ans.end(); it++){
            cout << *it << ' ';
        }
        //target command is now made
        cout << command << endl;
        prev_made.insert(command);
            
    }
    
    return 0;

}