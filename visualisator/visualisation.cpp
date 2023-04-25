#include "GRIPAlgorithm.h"

void random_layout(){

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


int main(){

}