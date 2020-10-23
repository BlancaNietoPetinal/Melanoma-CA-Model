#include <iostream>
#include <fstream>
#include "../../DestructionLib/destructionlib.h"
#include "../../GeneratorLib/generatorlib.h"

void test();
void print(std::vector <int> mat);

int main(){
    test();
    return 0;
}

void print(std::vector <int> mat) {
   std::cout << "The vector elements are : ";

   for (std::vector<int>::const_iterator i = mat.begin(); i != mat.end(); ++i)
    std::cout << *i << ' ';
}

void test(){
    bool result = true;
    int x, y, * E, node, *NE;
    E = new int[NODE_NUM];
    NE = new int[NODE_NUM];
    E = getMat("Tests/Sample/Etest_6x6_15.txt", NODE_NUM);
    std::vector <int> neighbours;
    coordinates_to_node(node, 5, 3, 2*NX-1, 2*NY-1);
    neighbours = n_neighbours(2, E, node, 2*NX-1, 2*NY-1);
    std::cout<<"Nodo: "<<node<<" en las coordenadas 7, 3"<<std::endl;
    create_vec(NODE_NUM, NE, 0);
    for (std::vector<int>::const_iterator i = neighbours.begin(); i != neighbours.end(); ++i){
            std::cout<<"Vecino: "<<*i<<std::endl;
            NE[*i] = 1;
    }
    //NE[node] = 10;
    save_mat(NODE_NUM, NE, "Tests/n_neighbours/neighbours.txt");
}