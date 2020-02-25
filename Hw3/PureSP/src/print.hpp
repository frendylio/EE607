#ifndef PRINT_HPP
#define PRINT_HPP

using namespace std;
#include <vector>
#include "path.hpp"
#include<bits/stdc++.h> 



void LinkCapacities(int nodes, vector< vector<shortestpath> >path, vector<int> adj[], bool is_Sum);
Capacity ECMPLinkCapacities(int nodes, ECMP_PATH path, bool is_Sum);

#endif // PRINT_HPP