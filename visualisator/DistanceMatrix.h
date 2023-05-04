#ifndef VERTEX
#define VERTEX
typedef int Vertex; 
typedef  std::vector<int> VertexSet; 
#endif


typedef  struct{
    int nbVertices; 
    int diameter; 
    int* m;

} DistanceMatrix, *pDistanceMatrix ;

int getGraphDistance(Vertex i, Vertex j, DistanceMatrix* mdist); 

DistanceMatrix * initDistanceMatrix(std::vector<std::vector<int>> adjacencyLists, int nbVertices); 
int distanceVertexSet(Vertex v, VertexSet vset, DistanceMatrix* mdist);
Vertex getFarthestVertex(VertexSet v, DistanceMatrix* m); 


void freeDistanceMatrix(DistanceMatrix * d); 