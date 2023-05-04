#include <bits/stdc++.h>
using namespace std;
#include <vector>
#include "DistanceMatrix.h"

#ifndef VERTEX
#define VERTEX
typedef int Vertex; 
typedef  std::vector<int> VertexSet; 

#endif
typedef struct{float x; float y;  float z;} myPoint, *pmyPoint; 

/**** The filtration process ****/
VertexSet createFiltrationVk(int c, DistanceMatrix* distm){
    VertexSet v; 
    srand((unsigned) time(NULL)); 
    int firstVertex = rand() % distm->nbVertices; 
    v.push_back(firstVertex); 
    for(int i = 1; i < c; i++){
        Vertex f = getFarthestVertex(v, distm); 
        v.push_back(f);
    }
    return v; 
}

VertexSet createFiltrationVi(vector<int> V, DistanceMatrix* distm, int nbToAdd){
    VertexSet Vi; 
    Vi.insert(V.begin(), V.begin(), V.end());
    for(int i = 1; i < nbToAdd; i++){
        Vertex f = getFarthestVertex(Vi, distm); 
        Vi.push_back(i);
    }
    return Vi; 
}

vector<vector<int>> createFiltration(int sizeFiltration, DistanceMatrix * distm, int c){
    vector<vector<int>> filtration; 
    filtration.push_back(createFiltrationVk(c, distm));
    int nbNotAssigned = distm->nbVertices - c;  
    int x = (int) exp((log(distm->nbVertices/c)/(sizeFiltration+1))); //to check
    for (int i = 1; i < sizeFiltration -1; i++){
        int nbToAdd = pow(x, i-1) * c; 
        filtration.push_back(createFiltrationVi(filtration[i-1], distm, nbToAdd));
        nbNotAssigned -= nbToAdd; 
    }
    filtration.push_back(createFiltrationVi(filtration[sizeFiltration -1], distm, nbNotAssigned));
}


/**** Find the initial position ****/

myPoint getBarycenter(myPoint a, myPoint b, myPoint c){
    //TODO check 
    float x = (a.x + b.x + c.x)/3; 
    float y = (a.y + b.y + c.y)/3; 
    float z = (a.z + b.z + c.z)/3;
    return myPoint {x, y, z}; 
}

myPoint getPointLinearCombination(myPoint a, myPoint b, float la, float lb){
    float x = (la * a.x + lb * b.x); 
    float y = la* a.y + b.y *lb; 
    float z = la* a.z + b.z * lb;
    return myPoint {x, y, z}; 
}

float getPointScalarProduct(myPoint a, myPoint b){
    float x = a.x * b.x + a.y * b.y + a.z * b.z;
    return x; 
}





void insertionClosestVertices(Vertex vinsert, Vertex v,  vector<int> vect, int sizeVect, DistanceMatrix* dist){
    //TODO check
    //en mode insertion à bulle
    //we consider that the first one is the closest
    if (getGraphDistance(vinsert, v, dist) < getGraphDistance(v, vect[sizeVect -1], dist)){
        vect[sizeVect-1] = vinsert; 
        int i = sizeVect -1; 
        while (i > 0 && (getGraphDistance(vect[i], v, dist) < getGraphDistance(vect[i-1], v, dist))){
            Vertex temp = vect[i]; 
            vect[i] = vect[i-1]; 
            vect[i-1] = temp; 
            i --; 
        }
    }
}

vector<Vertex> getThreeClosestVertex(Vertex v, vector<Vertex> vertexSet, DistanceMatrix* dist){
    vector<Vertex> result = {-1, -1, -1};
    for (auto u: vertexSet){
        insertionClosestVertices(u, v, result, 3, dist); 
    }
    return result; 
}


void initialiseFirstPositions(Vertex a, Vertex b, Vertex c, myPoint* pos, DistanceMatrix* distm){
    pos[a] = (myPoint) {0, 0, 0}; 
    pos[b] = (myPoint) {0, 0, getGraphDistance(a, b, distm)}; 
    pos[c] = (myPoint) {getGraphDistance(a, c, distm), getGraphDistance(b, c, distm),  0}; 
}

void findInitialPosition(Vertex v, vector<Vertex> vertexSet, DistanceMatrix* dist, myPoint* pos){
    //on ne l'applique qu'à partir de la filtration V_k
    vector<int> closestVertex = getThreeClosestVertex(v, vertexSet, dist); 
    pos[v] = getBarycenter(pos[closestVertex[0]], pos[closestVertex[1]], pos[closestVertex[2]]);    
}






/**** Rest of it ****/


float distancePoint(myPoint a, myPoint b){
    myPoint diff = getPointLinearCombination(a, b, 1, -1); 
    return sqrt(getPointScalarProduct(diff, diff)); 
}

myPoint Fkk(Vertex v, VertexSet vertexSet, DistanceMatrix dist){
    vector<int> closestVertex = getThreeClosestVertex(v, vertexSet, dist); 
    myPoint res = (myPoint) {0, 0, 0}; 
    for (int i = 0; i < 3; i++){
        myPoint diff = getPointLinearCombination(pos[u], pos[v], 1, -1); 
        res = getPointScalarProduct(res, diff, 1, distancePoint(pos[u], pos[v])/getGraphDistance(u, v, dist) - 1); 
    } 
    return res; 
}


myPoint Ffr(Vertex v, VertexSet adjacencylist, VertexSet vertexSet, DistanceMatrix dist){
    vector<int> closestVertex = getThreeClosestVertex(v, vertexSet, dist); 
    myPoint res = (myPoint) {0, 0, 0}; 
    for (int i = 0; i < 3; i++){
        Vertex u = closestVertex[i]; 
        myPoint diff = getPointLinearCombination(pos[u], pos[v], 1, -1); 
        res = getPointScalarProduct(res, diff, 1, pow(distancePoint(pos[u], pos[v]), 2)/getGraphDistance(u, v, dist) - 1); 
    } 
    for (auto u: adjacencylist){
        myPoint diff = getPointLinearCombination(pos[u], pos[v], 1, -1); 
        res = getPointScalarProduct(res, diff, 1, pow(distancePoint(pos[u], pos[v]), -2));

    }
    return res; 
}

double computeLocalTemperature(int v){
    return 1; 
}







myPoint* GRIPAlgorithm(int sizeFiltration, std::vector<std::vector<int>> adjacencyLists, int nbVertices, int rounds){
    DistanceMatrix* dm = initDistanceMatrix(adjacencyLists, nbVertices);
    int c = 3; //ca facilite la vie
    myPoint* pos = (myPoint*) malloc(sizeof(myPoint)*nbVertices); 
    myPoint* disp = (myPoint*) malloc(sizeof(myPoint)*nbVertices);  
    vector<vector<int>> filtration = createFiltration(sizeFiltration, dm, c);
    

    initialiseFirstPositions(filtration[0][0], filtration[0][1], filtration[0][2], pos, dm); 
    for (int i = 1; i < sizeFiltration; i++){

        for (auto v : filtration[i]){
            VertexSet neighbours = getThreeClosestVertex(v, filtration[i], dm); 
            findInitialPosition(v, neighbours, dm, pos); 
        }
    }
    for (int i = 0; i < rounds; i++){
        for (auto v : filtration[i]){
            VertexSet neighbours = getThreeClosestVertex(v, filtration[i], dm);
            heat[v] = computeLocalTemperature(v); 
            disp[v] = getPointScalarProduct(heat[v], Fn(v, neighbours[v]));
        }
        for (auto v : filtration[i]){
            pos[v] = getPointLinearCombination(pos[v], disp[v], 1, 1); 
        }
    }
    freeDistanceMatrix(dm);
    //add the edges 
    return pos; 

}


int roundingue(float f, int rounding){
    return round(f*rounding);
}

void savePositionToFile(myPoint * pos, int nbVertices, string filename, int rounding){
    // Create and open a text file
    ofstream MyFile(filename);
    for (int i = 0; i < nbVertices; i++){
        MyFile << "P" << i << ", " << roundingue(pos[i].x, rounding) << ", " << roundingue(pos[i].y, rounding) << ", " << roundingue(pos[i].z, rounding) << endl; 
    } 
    MyFile.close(); 
}

void savePositionToObjFile(myPoint * pos, int nbVertices, string filename, int rounding){
    // Create and open a text file
    ofstream MyFile(filename);
    for (int i = 0; i < nbVertices; i++){
        MyFile << "v" << " " << roundingue(pos[i].x, rounding) << " " << roundingue(pos[i].y, rounding) << " " << roundingue(pos[i].z, rounding) << endl; 
    } 
    MyFile.close(); 
}
