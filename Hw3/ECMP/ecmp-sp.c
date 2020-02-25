/*
 * File: ecmp-sp.c
 * Name: Christopher Manloloyo
 * username: manloloy
 * uhid: 12472841
 * Description: EE607 HW3
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MyCeilf(float num);
int Dijkstra(int numOfNodes, int *topology, int startNode, int endNode);
void CalcCapacities(int numOfNodes, int *prefNeighCount ,int **prefNeigh, float *capSum, int startNode, int endNode, int traffic);

//#define DEBUG
#define INF 2147483647

int main(int argc, char *argv[]){	
	
	//Decalare variables
	int numOfNodes, no;	//Number of Nodes in the Network
	int numOfLines, li;	//Used for for loop for both top and tra files
	int r, c, v, m, count;	//variables reused (i,j,k - for loops), (r,c,v - scans)
	int *dist,**prefNeigh;	//array for all nodes in the network
	int *prefNeighCount;
	int *topology, *traffic;//Topology and Traffic Matrices
	float *capSum, *sumTemp1, *sumTemp2;
	//Name and Location of Topology File
	char topFile[100] = "TestFiles/topology1.txt";
	//Name and Location of Traffic File
	char traFile[100] = "TestFiles/traffic1.txt";
	//Pointers to files for open and close
	FILE *fTop;		
	FILE *fTra;
	//reset Files to use if arguments are given
	if(argc>1){
		strcpy(topFile, argv[1]);
		strcpy(traFile,argv[2]);	
	}

	//Open Topology and Traffic File
	fTop = fopen (topFile, "r");
	fTra = fopen(traFile,"r");

	//scan number of nodes and number of Lines from both files
	fscanf(fTop, "%d %d", &numOfNodes, &numOfLines);
	fscanf(fTra, "%d %d", &no, &li);
	
	//Check,Handle Mismatch error 
	if(numOfNodes!=no){
		fclose(fTra);fclose(fTop);
		printf("ERROR: # of Nodes mismatch - Check your input files");
		return 0;
	}

	//Initialize Topology and Traffic Matrix
	topology = (int *)malloc(numOfNodes * numOfNodes * sizeof(int)); 
	traffic = (int *)malloc(numOfNodes * numOfNodes * sizeof(int)); 
	for (int i = 0; i <  numOfNodes; i++) 
		for (int j = 0; j < numOfNodes; j++){
			*(topology + i*numOfNodes + j) = 0;	
			*(traffic + i*numOfNodes + j) = 0;
		}
	//Insert Data from Topology File
	for(int i = 0; i<numOfLines;i++){
		fscanf(fTop,"%d %d", &r, &c);
		*(topology +r*numOfNodes +c) = *(topology +c*numOfNodes +r) = 1;
	}
	//Insert Data from Traffic File
	for(int i = 0; i<li; i++){
		fscanf(fTra,"%d %d %d", &r, &c, &v);
		*(traffic +r*numOfNodes +c) = *(traffic +c*numOfNodes +r) = v;
	}
	
	//Close Topology/Traffic Files - no longer needed
	fclose(fTop);
	fclose(fTra);

	#ifdef DEBUG
		printf("topology.txt\n");
		for (int i = 0; i <  numOfNodes; i++) {
			for (int j = 0; j < numOfNodes; j++) 
				printf("%d ",*(topology + i*numOfNodes + j));
		printf("\n");
		}
		printf("\ntraffic.txt\n");
		for (int i = 0; i <  numOfNodes; i++) {
			for (int j = 0; j < numOfNodes; j++) 
				printf("%d ",*(traffic + i*numOfNodes + j));	
		printf("\n");
		}
		printf("\n");
	#endif

	//Initialize Distance Matrix
	dist = (int *)malloc(numOfNodes * numOfNodes * sizeof(int)); 
		for(int i=0; i<numOfNodes;i++)
			for(int j=0; j<numOfNodes;j++)
				*(dist + i*numOfNodes + j) = INF;	
	//Use Dijkstra's Algorithm here and store distances for each node
	//dist(row, col)
	for(int i=0; i<numOfNodes; i++)
		for(int j=0; j<numOfNodes;j++){
			if(i==j)
				*(dist+i*numOfNodes+j)=0;
			else
				*(dist+i*numOfNodes+j)=Dijkstra(numOfNodes, topology,i, j);
		}
	//initialize preferred neighbor matrix
	prefNeigh = (int**)malloc(numOfNodes * numOfNodes * sizeof(int*));
	prefNeighCount = (int*) malloc(numOfNodes*numOfNodes*sizeof(int));
	for(int i = 0; i<numOfNodes;i++)
		for(int j=0; j<numOfNodes;j++){
			*(prefNeigh + i*numOfNodes +j) = (int*) malloc(numOfNodes*sizeof(int));
			*(prefNeighCount +i*numOfNodes+j) = 0;
		}
	//ECMPSP preffered neighbor matrix
	for(int i=0; i<numOfNodes;i++)
		for(int j=0; j<numOfNodes; j++){
			if(i==j)
				*(prefNeighCount + i*numOfNodes+j) =0;
			else{
				//loop through all nonzero toplology and pick the lowest distance
				m=INF;
				for(int k=0; k<numOfNodes; k++){
					if(*(topology+i*numOfNodes+k)!=0){
						if(*(dist+k*numOfNodes+j)<m){
							m = *(dist+k*numOfNodes+j);
						}
					}
				}
				//loop through again and pick all nodes with the lowest distance
				count =0;
				for(int k=0; k<numOfNodes; k++){
					if(*(topology+i*numOfNodes+k)!=0){
						if(*(dist+k*numOfNodes+j)==m){
							(*(prefNeigh+i*numOfNodes+j))[count] = k;	
							count++;
							*(prefNeighCount+i*numOfNodes+j)=count;
						}
					}	
				}
			}	
		}
	
	#ifdef DEBUG
		printf("distance (nodex, nodev)\n");
		for(int i = 0; i<numOfNodes;i++){
			for(int j = 0; j<numOfNodes;j++){
				if(*(dist + i*numOfNodes+j) ==INF)
					printf("-1 ");
				else
					printf("%2d ",*(dist + i*numOfNodes + j));
			}	
			printf("\n");
		}
		printf("\npreferredNode(nodex, nodev)\n");
		for(int i = 0; i<numOfNodes;i++){
			for(int j = 0; j<numOfNodes;j++){
				if(*(prefNeighCount+i*numOfNodes+j)!=0){
				printf("node %d to node %d has %d preferred nodes\n", i, j,*(prefNeighCount+i*numOfNodes+j));
				for(int k=0; k<(*(prefNeighCount+i*numOfNodes+j));k++)
					printf("%d ",(*(prefNeigh + i*numOfNodes + j))[k]);
				printf("\n");
				}
			}
			printf("\n");
		}
	#endif


	
	//Allocate space for each linkSum and initilaize to 0
	capSum = (float*) malloc(numOfNodes*numOfNodes*sizeof(float));	
	sumTemp1 = (float*) malloc(numOfNodes*numOfNodes*sizeof(float));	
	sumTemp2 = (float*) malloc(numOfNodes*numOfNodes*sizeof(float));	
	for (int i=0; i<numOfNodes;i++)
		for(int j=0; j<numOfNodes; j++)
			*(capSum+i*numOfNodes +j) = 0.0;
		
	//if traffic data is symmetrical we should loop the upper triangle for traffic
	//if not we need to loop through all traffic data
	for(int i=0; i<numOfNodes; i++){
		for(int j=0; j<numOfNodes; j++){
			if(j>i && (*(traffic+ i*numOfNodes +j)!=0) ){
				//reset temporary capacities
				for (int i=0; i<numOfNodes;i++)
					for(int j=0; j<numOfNodes; j++){
						*(sumTemp1+i*numOfNodes +j) = 0.0;
						*(sumTemp2+i*numOfNodes +j) = 0.0;
					}	
				//caclulate in forward direction and store in sumTemp1
				CalcCapacities(numOfNodes,prefNeighCount,prefNeigh,sumTemp1,i,j, *(traffic+i*numOfNodes+j));
				//caclulate in reverse direction and store in sumTemp2
				CalcCapacities(numOfNodes,prefNeighCount,prefNeigh,sumTemp2,j,i, *(traffic+i*numOfNodes+j));
				//pick max(sumTemp1, sumTemp2) to add to real capsum
				for (int i=0; i<numOfNodes;i++)
					for(int j=0; j<numOfNodes; j++){
					if(*(sumTemp1+i*numOfNodes +j) > *(sumTemp2+i*numOfNodes +j))
						(*(capSum+i*numOfNodes +j))+=(*(sumTemp1+i*numOfNodes +j));
					else
						(*(capSum+i*numOfNodes +j))+=(*(sumTemp2+i*numOfNodes +j));
					}	
			}	
		}
	}

	//Loop through upper triangle of capSum to ceil  sum Capacities
	v=0;
	for(int i=0; i<numOfNodes; i++){
		for(int j=0;j<numOfNodes;j++){
			if(j>i && (*(topology+i*numOfNodes+j)!=0)){
				(*(capSum+i*numOfNodes+j)) = MyCeilf(*(capSum+i*numOfNodes+j));
				v+=(*(capSum+i*numOfNodes+j));	
			}		
		}	
	}

	//printing answer for HW3	
	printf("EE 607 Network Desing\n");
	printf("Toplogy: topology.txt\n");
	printf("Traffic mattrix: traffic.txt\n");
	printf("Shortest path routing: ECMP-SP\n");
	printf("Sum of link capactities = %d\n", v);
	printf("Link Capacities:\n");
	
	for(int i=0; i<numOfNodes; i++){
		for(int j=0;j<numOfNodes;j++){
			if(j>i && (*(topology+i*numOfNodes+j)!=0))
				printf("(%d,%d): %d\n", i,j,(int)(*(capSum+i*numOfNodes+j)));		
		}
		
	}
		

	//Clean up
	//Freeing topology, traffic, and dist memory
	free(topology);
	free(traffic);
	free(dist);
	free(capSum);
	for(int i=0; i<numOfNodes; i++)
		for(int j=0; j<numOfNodes; j++)
			free(*(prefNeigh+i*numOfNodes+j));
	free(prefNeigh);
	return 0;
}

int Dijkstra(int numOfNodes, int *topology, int startNode, int endNode){
	//used to calculate and return values to the dist matrix
	int tempDist;
	int min, index;
	int *dist;   		// node distance matrix for dijkstra
	int *visited;		// visited set for dijkstra's alg
	int currentNode;  	// current node
	visited =(int *) malloc(numOfNodes * sizeof(int)); 
	dist = (int *) malloc(numOfNodes*sizeof(int));
	
	//initialize 
	for(int i=0; i<numOfNodes;i++){
		visited[i] = 0;
		dist[i] = INF;
	}
	//Start Node
	currentNode = startNode;
	dist[currentNode] = 0;	
	visited[currentNode] = 1;
	
	//while the current node is not the end node
	while(currentNode != endNode){

		//check topology and update neighbors
		for(int i=0; i<numOfNodes; i++){
			//find all neighbor nodes
			if(*(topology+currentNode*numOfNodes+i)!=0){
				//if neighbor node was not visited calc distance
				if(!visited[i]){
					tempDist = dist[currentNode] + *(topology+currentNode*numOfNodes+i);
					//if tempDist is less than current dist then update
					if(tempDist<dist[i])
						dist[i] = tempDist;
				}	

		
			}

		}	
		//initialize min by searching for the first unvisited	
		for(int j=0; j<numOfNodes;j++){
			if(!visited[j]){
				min = dist[j];
				index = j;
				break;
			}
		}		
		//search unvisted nodes for lowest dist index
		for(int j=0; j<numOfNodes; j++){
			if(!visited[j])
				if(dist[j] < min){
					min = dist[j];
					index = j;
				}
		}

		//change current node to lowest	dist
       		currentNode = index;
		visited[index] = 1;	
	}
	//I must traverse the
	min = dist[endNode];
	free(visited);
	free(dist);
	return min;
}
		
void CalcCapacities(int numOfNodes, int *prefNeighCount, int **prefNeigh, float *capSum, int startNode, int endNode, int traffic){

	int currentNode;		//current node calculating at
	int *mustVisit;  		//bool of nodes to visit
	float *mustVisitTraffic;	//how much traffic can be sent from a node
	int prefNCount;			//used to store how many pref neighbors are at a node
	float t;			//used to store calculated split traffic at a node
	int n, nodeFound;               //n is a possible node to travel to next
					//nodeFound is a bool to check if the isVisited set is empty.
	
	//initialize space for the must visit arrays and set initial value
	mustVisit = (int *) malloc(numOfNodes*sizeof(int)); 
	mustVisitTraffic = (float *) malloc(numOfNodes*sizeof(float));
	for(int i =0; i<numOfNodes; i++){
		mustVisit[i] = 0;
		mustVisitTraffic[i]=0;
	}
	

	//set start node to current node and make		
	currentNode = startNode;
	mustVisit[startNode] = 1;
	mustVisitTraffic[startNode]=traffic;
	
	//while there are nodes in the must visit set
	//calculate traffic on each link and store in capSum array.
	nodeFound = 1;
	while(nodeFound!=0){
		//find pref count at current node
		prefNCount = *(prefNeighCount+currentNode*numOfNodes+endNode);
		// calculated traffic to be distributed evenly
		t = (float) mustVisitTraffic[currentNode] / (float) prefNCount;
		
		//loop through all neighbors
		//update the capSum
		//and add to mustVisit and mustVisitTraffic
		for(int i=0; i<prefNCount; i++){
			//update capsum for current to n
			n = (*(prefNeigh+currentNode*numOfNodes+endNode))[i];	
			if(currentNode<n)
			 	(*(capSum+currentNode*numOfNodes+n))+=t;
			else
				(*(capSum+n*numOfNodes+currentNode))+=t;
			
			//now add to mustvisit only if n is not equal to endNode
			if(n!=endNode){
				//if node is not in must visit, add it
				if(mustVisit[n]!=1){
					mustVisit[n] = 1;
					mustVisitTraffic[n] = t;
				}else{ // if it is, just add the traffic
					mustVisitTraffic[n]+=t;
				}
			}
		}
		//remove current node from the mustvisit set and clear mustvisittraffic
		mustVisit[currentNode] =0;
		mustVisitTraffic[currentNode]=0;
		//check if there are still nodes in mustvisit
		nodeFound =0;
		for(int j=0; j<numOfNodes;j++){
			if(mustVisit[j] == 1&& !nodeFound){
				currentNode = j;
				nodeFound=1;
			}
		}
	}

	//Free dynamic mem
	free(mustVisit);
	free(mustVisitTraffic);
	return;
}

int MyCeilf(float num) {
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}
