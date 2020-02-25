

#include <iostream>
#include <iomanip>

// Headers needed to read file
#include <fstream>
using namespace std;

#include <vector>
#include "network.hpp"

// Storage data in my 2D vector
vector<vector <int> > readfile(vector< vector<int> > data, string filename, bool isTop){

    int i=0, j=0, x;

    // Input file stream
    ifstream inFile;
    
    // open file
    inFile.open(filename);
    // check if we opened the file
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    // Read from the file and do something
    while (inFile >> x) {

        data[i][j] = x;

        // If topology
        if (isTop){
            // next column
            if (i > 1){
                j = j + 1;
            } 

            // next line
            if (j == 2 || i < 2){
                j = 0;
                i = i + 1;
            }
        }

        // If traffic
        else{
            // next column
            if (i > 1){
                j = j + 1;
            } 

            // next line
            if (j == 3 || i < 2){
                j = 0;
                i = i + 1;
            }
        }    

    }
    
    // close file
    inFile.close();

    return data;

}

void printNetwork( vector < vector <int> > data, int m, int n){
  int i, j;
   for (int i = 0; i < m; i++) 
       for (int j = 0; j < n; j++) 
  
          // Prints ' ' if j != n-1 else prints '\n'           
          cout << data[i][j] << " \n"[j == n-1]; 

}
