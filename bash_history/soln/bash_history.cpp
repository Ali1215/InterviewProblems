// Remember style matters!

#include <map>
#include <set>
#include <string>
#include <iostream>
using namespace std;


void back_up(string &directory){
    /*
    Description:  Changes the directory to go up one folder

    args: directory = current directory
    
    returns: none (changes directory by reference)
  */

    int last_index = directory.find_last_of('/');
    //resize to remove last folder
    directory.resize(last_index);
    //add slash for root directory
    if (directory.size() == 0)
        directory = "/";
    return;
}


void print_set(set<string> set_to_print){
    /*
    Description:  prints out a set with elements space separated

    args: set_to_print = set to print to terminal
    
    returns: none
  */
    for (auto file = set_to_print.begin(); file != set_to_print.end(); file++)
        cout << ' ' << *file;
    cout << endl;
    return;
}

int main() {
    int num_commands;
    cin >> num_commands;
    

    map<string,set<string>> files_map;
    //start in root directory
    string current_directory = "/";
    
    //initialize root directory to empty set of files
    files_map[current_directory];
    
    string command, arg;
    for (int i = 0; i < num_commands ; i++){
        cin >> command >> arg;
        
        if (command == "ls")
            //insert file argument to directory's files
            files_map[current_directory].insert(arg);
        else if (command == "cd"){
            if(arg == ".."){
                //go up one directory
                back_up(current_directory);
                
            }
            else{
                if (current_directory != "/"){
                    //add slash and then new folder to directory
                    current_directory += '/' + arg;
                }
                else{
                    //if in root directory, slash is unnecessary
                    current_directory += arg;
                }
                //initialize directory to empty set, if it has not been visited previously
                files_map[current_directory];
            }
        }
    }
    for (auto it = files_map.begin(); it != files_map.end(); it++){
        //print directory name first
        cout << it->first;

        //print files within directory
        print_set(it->second);
    }
    
    return 0;
}