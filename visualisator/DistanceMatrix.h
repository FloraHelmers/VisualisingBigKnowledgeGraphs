typedef  struct{
    int nbVertices; 
    int diameter; 
    int* m;

} DistanceMatrix, *pDistanceMatrix ;

int getGraphDistance(Vertex i, Vertex j, DistanceMatrix* mdist); 

DistanceMatrix * initDistanceMatrix(std::vector<std::vector<int>> adjacencyLists, int nbVertices); 

void freeDistanceMatrix(DistanceMatrix * d); 