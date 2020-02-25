#include "linkedlist.hpp"
#include "network.hpp"
#include "path.hpp"
#include "print.hpp"

#define row 20
#define col 2
#define toprow 10
#define topcol 3

using namespace std;

int main(){  

    vector < vector < int > > data(row, vector< int>(col, -1));
    
    string topology = "topolgy.txt";

    data = readfile(data, topology, true);
     cout << "--Opening Topology\n"; 
    //////////////
    // Make data into a graph
    //////////////
    int nodes; // number of nodes
    int links; // number of links

    nodes = data[0][0];
    links = data[1][0];
    int i = 2;
    int k = 0;
    vector<int> adj[nodes]; 

    while (k < links){
        if(data[i][0] == -1) break;
        addEdge(adj, data[i][0], data[i][1]); 
        i++;    
        k++;    
    }
    //  printGraph(adj, nodes); 
    ////////////////////////
    // Put weights.
    ////////////////////////
    vector < vector < int > > DataTraf(toprow, vector< int>(topcol, -1));
    
    string traffic = "matrix.txt";

    DataTraf = readfile(DataTraf, traffic, false);
    cout << "--Opening Traffic\n";
    int loop = DataTraf[1][0];

    vector< vector<shortestpath> >path(loop, vector <shortestpath>(nodes, {-1,0}));

    k = 0;
    i = 2;
    while(k < loop){
        path[k] = printShortestDistance(adj, DataTraf[i][0], DataTraf[i][1], nodes, DataTraf[i][2]); 
        // cout << "------\n"<<path[k][1].path <<  path[k][1].weight;
        i++;
        k++;
    }
        cout << "--Short Distance\n";
     // printing path from source to destination 
    // for(int j = path.size() - 1; j >=0; j --){
    //         cout << "\nPath is::"; 
    //         for (int i = path[j].size() - 1; i >= 0; i--) 
    //             cout << path[j][i].path << " "; 
    //         cout << "\nCapacity is::"; 
    //         for (int i = path[j].size() - 1; i >= 0; i--)
    //             cout << path[j][i].weight << " \n";    
    // }

    ///////////// 
    // ECMP
    ////////////
    vector< ECMP_PATH> MultipleShortestPath;
    k = 0;
    i = 2;
    while (k < links){
        if(DataTraf[i][0] == -1) break;
        MultipleShortestPath.push_back(findpaths(adj, DataTraf[i][0], DataTraf[i][1], nodes, DataTraf[i][2]));  
        i++;    
        k++;    
    } 

// print
    // i = 0;
    // int j = 0;
    // Capacity real_capacity;
    // while(j < MultipleShortestPath.size()){
    //         // cout << "path from src " << DataTraf[i][0] << " to dst " << DataTraf[i][1] << " are \n"; 
    //         // if (index == MultipleShortestPath.size()) break;
    //         real_capacity = ECMPLinkCapacities(5,MultipleShortestPath[j],true);
    //     j++;
    // }
    ///////////////////
    // Output
    ///////////////////
    cout << "\n -------------- Pure - SP --------------" << " \n";    
    
    cout << "EE 607 Network Design" << " \n";
    cout << "Topology: " << topology <<" \n";
    cout << "Traffic matrix: " << traffic <<" \n";
    cout << "Shortest path routing: Pure-SP" <<" \n"; 
    cout << "Sum of link capacities = "; 
    LinkCapacities(nodes, path, adj, true);
    cout << "Link Capacities:" << " \n";    
    LinkCapacities(nodes, path, adj, false);
    return 0; 

}

// For network
   
//   printGraph(adj, nodes);


// FOr Linked list texting
/*
    int V = 5; 
    vector<int> adj[V]; 
    addEdge(adj, 0, 1); 
    addEdge(adj, 0, 4); 
    addEdge(adj, 1, 2); 
    addEdge(adj, 1, 3); 
    addEdge(adj, 1, 4); 
    addEdge(adj, 2, 3); 
    addEdge(adj, 3, 4); 
    printGraph(adj, V); 
*/