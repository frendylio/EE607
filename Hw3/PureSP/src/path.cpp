// CPP code for printing shortest path between 
// two vertices of unweighted graph 
#include <bits/stdc++.h> 
#include "path.hpp"
#include <queue>
using namespace std; 

// a modified version of BFS that stores predecessor 
// of each vertex in array p 
// and its distance from source in array d 
bool BFS(vector<int> adj[], int src, int dest, int v, 
                            shortestpath pred[], int dist[], int capacity) 
{ 
    // a queue to maintain queue of vertices whose 
    // adjacency list is to be scanned as per normal 
    // DFS algorithm 
    list<int> queue; 
  
    // boolean array visited[] which stores the 
    // information whether ith vertex is reached 
    // at least once in the Breadth first search 
    bool visited[v]; 
  
    // initially all vertices are unvisited 
    // so v[i] for all i is false 
    // and as no path is yet constructed 
    // dist[i] for all i set to infinity 
    for (int i = 0; i < v; i++) { 
        visited[i] = false; 
        dist[i] = INT_MAX; 
        pred[i].path = -1; 
    } 
  
    // now source is first to be visited and 
    // distance from source to itself should be 0 
    visited[src] = true; 
    dist[src] = 0; 
    queue.push_back(src); 
  
    // standard BFS algorithm 
    while (!queue.empty()) { 
        int u = queue.front(); 
        queue.pop_front(); 
        for (int i = 0; i < adj[u].size(); i++) { 
            if (visited[adj[u][i]] == false) { 
                visited[adj[u][i]] = true; 
                dist[adj[u][i]] = dist[u] + 1; 
                pred[adj[u][i]].path = u; 
                pred[adj[u][i]].weight = capacity; 
                queue.push_back(adj[u][i]); 
  
                // We stop BFS when we find 
                // destination. 
                if (adj[u][i] == dest) 
                   return true; 
            } 
        } 
    } 
  
    return false; 
} 
  
// utility function to print the shortest distance  
// between source vertex and destination vertex 
vector<shortestpath> printShortestDistance(vector<int> adj[], int s,  
                                    int dest, int v, int capacity) 
{ 

    // predecessor[i] array stores predecessor of 
    // i and distance array stores distance of i 
    // from s 
    shortestpath pred[v];
    int dist[v]; 
    vector<shortestpath> path; 
    if (BFS(adj, s, dest, v, pred, dist, capacity) == false) 
    { 
        cout << "Given source and destination"
             << " are not connected"; 
        return path; 
    } 
  
    // vector path stores the shortest path with the weight.

    shortestpath crawl ={ dest, capacity}; 
    path.push_back(crawl); 
    while (pred[crawl.path].path != -1) { 
        path.push_back(pred[crawl.path]); 
        crawl = pred[crawl.path]; 
    } 
  
    return path;
    
    // // distance from source is in distance array 
    // cout << "\nShortest path length is : "
    //     << dist[dest]; 
  
    // // printing path from source to destination 
    // cout << "\nPath is::"; 
    // for (int i = path.size() - 1; i >= 0; i--) 
    //     cout << path[i].path << " "; 
    // cout << "\nCapacity is::"; 
    // for (int i = path.size() - 1; i >= 0; i--)
    //     cout << path[i].weight << " \n"; 
    

} 

///////////////////
// ECMP
/////////////////
  
// utility function for printing 
// the found path in graph 
void printpath(vector<float>& path) 
{ 
    int size = path.size(); 
    for (int i = 0; i < size; i++)  
        cout << path[i] << " ";     
    cout << endl; 
} 
  
// utility function to check if current 
// vertex is already present in path 
int isNotVisited(int x, vector<float>& path) 
{ 
    int size = path.size(); 
    for (int i = 0; i < size; i++)  
        if (path[i] == x)  
            return 0;  
    return 1; 
} 
  
// utility function for finding paths in graph 
// from source to destination 
ECMP_PATH findpaths(vector<int> adj[], int s, int dst, int v, int capacity) { 

    // create a queue which stores 
    // the paths 
    queue<vector<float> > q; 
  
    // path vector to store the current path 
    vector<float> path; 
    vector< vector < float >>sizepath;
    vector< vector < float >>empty;
    path.push_back(s); 
    q.push(path); 

    int size = 0;
    while (!q.empty()) { 
        path = q.front(); 
        q.pop(); 
        int last = path[path.size() - 1]; 
  
        // if last vertex is the desired destination 
        // then print the path 
        if (last == dst){
            if( path.size() > size && size != 0){
                continue;
            }
            else if(path.size() < size && size != 0){
                sizepath = empty;  
            }
            sizepath.push_back(path);
            size = path.size();         
        }
        // traverse to all the nodes connected to  
        // current vertex and push new path to queue 
        for (int i = 0; i < adj[last].size(); i++) { 
            if (isNotVisited(adj[last][i], path)) { 
                vector<float> newpath(path); 
                newpath.push_back(adj[last][i]); 
                q.push(newpath);
            }
        }
    }

    return ECMP_PATH{sizepath, (float)capacity};
} 

// Calculate Capacity

//     // Capcaity
//     // Just added it to the start
//     int j = 0;
//     int i = 1;
//     int k = 0;
//     int divide;
//     float real_capacity;
//     vector <float> CurrentPath;
//     bool is_already;

//     // Move thru rows and check if split
//         while (j < sizepath.size()){
//             is_already = false;
//             /////////////////////////
//             // Check how many path
//             /////////////////////////
//             // if empty
//             if (CurrentPath.empty()){
//                 CurrentPath.push_back(sizepath[j][i]);
//             }
//             // check if split
//             else{
//                 while(k < CurrentPath.size()){
//                     if(sizepath[j][i] == CurrentPath[k]){ 
//                         is_already = true;
//                         break;
//                     }
//                     k++;
//                 }
//                 if(!is_already){  
//                     CurrentPath.push_back(sizepath[j][i]);
//                 }
//             }
//             j++;
//         }
//         divide = CurrentPath.size();
//         real_capacity = (float)capacity/(float)divide;

//     i = 0;
//     while (i < CurrentPath.size()) {
//         sizepath[i].insert(sizepath[i].begin(), real_capacity);
//         i++;
//     }                

// // print
//      i = 0;
//     while (i < sizepath.size()){
//         printpath(sizepath[i]);
//         i++;
//     }

// //current
// cout << " -CurrentPAth-\n";    

//      i = 0;
//   for (i; i < CurrentPath.size(); i++)  {
//         cout << CurrentPath[i] << " --\n";    
//     }
