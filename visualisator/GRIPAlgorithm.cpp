#include <vector>



typedef int Vertex; 
typedef  struct{
    int nbVertices; 
    int diameter; 
    std::vector<std::vector<int>> m;

} DistanceMatrix, *pDistanceMatrix ;

DistanceMatrix * initDistanceMatrix(){
    //TODO
    //read the graph
    //create the bellman ford matrix 
    return NULL;
}

int getGraphDistance(Vertex i, Vertex j, DistanceMatrix* mdist){
        if (i <= -1 || j <= -1){
            return mdist->diameter + 1; 
        }
        return mdist->m[i][j]; 
}

typedef struct{float x, float y, float z} myPoint, *pmyPoint; // TODO check 

typedef  std::vector<Vertex> VertexSet; //has the method contains

/**** The filtration process ****/
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



Vertex getFarthestVertex(VertexSet v, DistanceMatrix* m){
    Vertex farthest = -1;
    for (int i = 0; i < m.nbVertices; i++ ){
        if ((!v.contains(i)) &&  (getGraphDistance(i, v, m) < getGraphDistance(v, farthest, m))){
            farthest = i; 
        }
    }
    return i; 
}


void createFiltration(){
    //TODO
}


/**** Find the initial position ****/

myPoint getBarycenter(myPoint a, myPoint b, myPoint c){
    //TODO check 
    float x = (a.x + b.x + c.x)/3; 
    float y = (a.y + b.y + c.y)/3; 
    float z = (a.z + b.z + c.z)/3;
    return myPoint {x, y, z}; 
}

void insertionClosestVertices(Vertex vinsert, Vertex v,  vector<Vertex>* vect, int sizeVect, DistanceMatrix* dist, int sizevect){
    //TODO
    //en mode insertion à bulle
    //we consider that the first one is the closest
    if (getGraphDistance(vinsert, v, dist) < getGraphDistance(v, vect[sizevect -1], dist)){
        vect[sizevect-1] = vinsert; 
        int i = sizevect -1; 
        while (i > 0 && getGraphDistance(vect[i] < vect[i-1], dist)){
            Vertex temp = vect[i]; 
            vect[i] = vect[i-1]; 
            vect[i-1] = temp; 
            i --; 
        }

    }
}

vector<Vertex> getThreeClosestVertex(Vertex v, vector<Vertex> vertexSet, DistanceMatrix dist){
    vector<Vertex> result = {-1, -1, -1};
    float diameter = dist.diameter(); //TODO
    vector<float> distances = {}
    for (auto u: vertexSet){
        insertionClosestVertices(u, result, 3, dist); 
    }
    return result; 
}

vector<myPoint> computeTwoSpheresIntersection3D(myPoint u, float radiusU, myPoint v, float radiusV){
    //TODO maths 
}



myPoint findInitialPosition(Vertex v, vector<Vertex> vertexSet, DistanceMatrix dist){
    vector<Vertex> closestVertex = getThreeClosestVertex(v, vertexSet, dist); 
    if (closestVertex.size() == 3 && closestVertex[2] != -1){
        // then there are 3 closest Vertex
        //TODO
        
    }
    //case 2

    //case 1 
    

}




/**** Rest of it ****/
void startNbrs(){}

std::vector<int> getSetDifference(){
    return {};
}

void findNeighbourhood(){}





double computeLocalTemperature(int v){
    return 0.; 
}
void GRIPAlgorithm(int sizeFiltration){
    createFiltration();
    startNbrs(); //? 
    for (int i = sizeFiltration; i >= 0; i--){

        for (auto v : getSetDifference()){
            findNeighbourhood(); 
            findInitialPosition(); 
        }
    }
    for (int i = 0; i < rounds; i++){
        for (auto v : V[i]){
            heat[v] = computeLocalTemperature(v); 
            disp[v] = scalar(heat[v].Fn(v, neighbours[v]));

        }
        for (auto v : V[i]){
            pos[v] += disp[v]; 
        }
    }
    //add the edges 

}

