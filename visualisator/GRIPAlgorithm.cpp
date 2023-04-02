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

void createVisualisation(){
    std::vector<glm::vec3> nodes = {} /* some nodes */;
    std::vector<std::array<size_t, 2>> edges = {} /* edges between nodes */;
    std::vectpr<std::string> names_nodes; 
    std::vectpr<std::string> names_edges; 

    polyscope::registerCurveNetwork("graphs", nodes, edges); 
    polyscope::getCurveNetwork("graphs")->addNodeScalarQuantity("name_nodes", names_nodes);
    polyscope::getCurveNetwork("graphs")->addEdgeScalarQuantity("names", names_edges);
    polyscope::show(); 
}