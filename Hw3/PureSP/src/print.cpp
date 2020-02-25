#include "print.hpp"
using namespace std;

void LinkCapacities(int nodes, vector< vector<shortestpath> >path, vector<int> adj[], bool is_Sum){
    // Populate parantesis
    int capacity = 0;
    int exitloop = 0;
    int pathi = path.size() - 1;
    int pathj;  
    int test = 0;
    int total_capacity = 0;
    bool salir;


    // Logic go through path, and go to each node.
    for(int i = 0; i < nodes; i++){
          for(auto j: adj[i]){
            if (i > j) {
                continue;
            }// reset count
            capacity = 0;
            // Add counts

            for(int row  = path.size() - 1; row >=0; row --){
                 for(int col = path[row].size() - 1; col >= 0; col--){
                    if(path[row][col].path == i){
                        // check if next one is j
                        if(path[row][col-1].path == j){
                            capacity = path[row][col].weight + capacity;
                        }
                        
                    }
                    //case 1 <- 0
                    else if(path[row][col].path == j){
                        // check if before one is j
                        if(path[row][col-1].path == i){
                            capacity = path[row][col-1].weight + capacity;
                        }                    
                    }
                }
            }
            if(!is_Sum) cout << "(" << i << "," << j << "): " << capacity << "\n";
            else total_capacity = total_capacity + capacity;
        }  
    } 

    if(is_Sum) cout << total_capacity << "\n";
};


Capacity ECMPLinkCapacities(int nodes, ECMP_PATH path, bool is_Sum){

    /////////////////////////
    // Variables
    ////////////////////////
                                // size ,  value
    vector< float > return_weight(path.path.size(), path.weight);
    vector < float > current_path;
    vector < int > index; // tells us which index to update.
    int rows_same = 0;
    vector <int> is_same_path;
    vector < vector < int > > splits_2d;
    vector < int > splits_1d;
    int split_number = 0;
    ///////////////////////////
    // Logic
    ///////////////////////////
    // go each row
    for(int i = 0; i < path.path.size(); i++){

        ////////////////////////
        // Current Path
        ////////////////////////
        // empty path
        current_path.clear();
        // populate current path.
        for(int a = 0; a < path.path[i].size(); a++){
            current_path.push_back(path.path[i][a]);
        }

        ////////////////////
        // Go each col
        ////////////////////
        for(int j = 0; j < current_path.size(); j++){

            ///////////////////////////
            // check against other row
            ///////////////////////////
            for(int k = 0; k < path.path.size(); k++){

                ///////////////////
                // if checking same path(itself) skip
                // i = current
                // k = check against other row
                ///////////////////
                if (i == k) continue;

                else{
                    /////////////////
                    // Check previous row and see if we need to split
                    // j = current col
                    // l = check against col
                    // storage with index is the same path.
                    /////////////////
                    index.clear();

                    // Check if same.
                    for(int l = 0; l < j; l++){
                        if(current_path[l] == path.path[k][l]){
                            is_same_path.push_back(k);
                        } 
                    }

                    // if is_same_path is not empty; means it splits
                    if (!is_same_path.empty()){

                        // check if current is different.
                        for(int r = 0; r < path.path.size(); r++){
                            if(is_same_path[r] != k) continue;

                            if(current_path[j] != path.path[k][j]){
                                split_number ++;
                            }
                        }
                    }

                }

                is_same_path.clear();
            }

            /////////////////////
            // Now after checking how many ways it splits
            ///////////////////////
            splits_1d.push_back(split_number);
            split_number = 0;

        }    
        splits_2d.push_back(splits_1d);
        splits_1d.clear();
    }

    ///////////////////////////////////////////
    // Print statement
    ///////////////////////////////////////

    // weight
    cout << "weight\n";

    for(int i = 0; i < splits_2d.size(); i++){
        for(int j = 0; j < splits_2d[i].size();j++){
            cout << splits_2d[i][j] << " ";
        }
            cout << "\n";
    }
    //For weight
    cout << "vector\n";
    for (int i = 0; i < return_weight.size(); i++){
        cout << return_weight[i] << " ";
    }
cout << "\n";
    // For array
    cout << "path\n";
    for(int i = 0; i < path.path.size(); i++){
        for(int j = 0; j < path.path[i].size(); j++)
            cout << path.path[i][j] << " ";

            cout << "\n";
    }
              cout << "\n";

};