
int getGraphDistance(Vertex i, Vertex j, DistanceMatrix* mdist){
        int nbVertices = mdist->nbVertices;
        if (j < i){
            return getGraphDistance(j, i, mdist); 
        }
        if (i <= -1 || j >= mdist->nbVertices){
            return mdist->diameter ; 
        }
        return mdist->m[i*nbVertices + j]; 
}

DistanceMatrix * initDistanceMatrix(std::vector<std::vector<int>> adjacencyLists, int nbVertices){
    int* m = (int*) malloc(nbVertices * nbVertices * sizeof(int)); 
    for (int i = 0; i < nbVertices * nbVertices; i++){
        m[i] = INT_MAX; 
        cout << m[i] << endl; 
    }
    //read the graph
    for (int i = 0; i < nbVertices; i++){
        for (auto l : adjacencyLists[i]){
            m[i * nbVertices +l] = 1;
            m[i + nbVertices * l] = 1; 
        }
    }
    int diameter = INT_MAX; 

    // Floyd-Warshall
    for (int k = 0; k < nbVertices; k++) {
        for (int i = 0; i < nbVertices; i++) {
            for (int j = 0; j < nbVertices; j++) {
                if ((m[i* nbVertices +k] < INT_MAX) && (m[k* nbVertices +j] < INT_MAX) && (m[i* nbVertices +k] + m[k* nbVertices +j] < m[i* nbVertices +j])){
                    m[i* nbVertices +j] = m[i* nbVertices +k] + m[k* nbVertices +j];
                }
            }
        }
    }
    
    DistanceMatrix* d = (DistanceMatrix*) malloc(sizeof(DistanceMatrix)); 
    d->diameter = diameter; 
    d->m = m; 
    d->nbVertices = nbVertices; 
    return d;
}

int distanceVertexSet(Vertex v, VertexSet vset, DistanceMatrix* mdist){
    int distance = getGraphDistance(v, -1, mdist);
    for (auto u: vset){
        int currentDistance = getGraphDistance(u, v, mdist); 
        if (currentDistance < distance){
            distance = currentDistance;
        }
    }
    return distance; 
}



bool vectorContains(VertexSet v, Vertex i){
    for (auto u : v){
        if( u == i){
            return true; 
        }
    }
    return false ;
}

Vertex getFarthestVertex(VertexSet v, DistanceMatrix* m){
    Vertex farthest = -1;
    for (int i = 0; i < m->nbVertices; i++ ){
        //a modifier 
        if ((!vectorContains(v, i)) &&  (distanceVertexSet(i, v, m) < distanceVertexSet(farthest, v, m))){
            farthest = i; 
        }
    }
    return farthest; 
}





void freeDistanceMatrix(DistanceMatrix * d){
    free(d->m); 
    free(d); 
}