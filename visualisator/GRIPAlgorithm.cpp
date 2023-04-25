#include <vector>
#include "polyscope/curve_network.h" 

void createFiltration(){}

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

