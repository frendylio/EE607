#ifndef NETWORK_HPP
#define NETWORK_HPP

using namespace std;

#include <vector>
#include <string>

// Storage data in my 2D vector
vector<vector <int> > readfile(vector< vector<int> > data, string filename, bool isTop);

void printNetwork( vector < vector <int> > data, int m, int n);

#endif // NETWORK_HPP