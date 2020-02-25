#ifndef PATH_HPP
#define PATH_HPP

using namespace std;
#include <vector>

struct shortestpath{
    int path;
    int weight;
};   


struct ECMP_PATH{
    vector< vector<float> >path;
    float weight;
};   

struct Capacity{
    float weight;
    int index;
};

vector<shortestpath> printShortestDistance(vector<int> adj[], int s, int dest, int v, int capacity); 
bool BFS(vector<int> adj[], int src, int dest, int v, shortestpath pred[], int dist[], int capacity);

// ECMP
void printpath(vector<float>& path);
int isNotVisited(int x, vector<float>& path);
ECMP_PATH findpaths(vector<int> adj[], int s, int dst, int v, int capacity);
#endif // PATH.HPP