#include <iostream>
#include <fstream>
#include "../../DestructionLib/destructionlib.h"
#include "../../GeneratorLib/generatorlib.h"

//std::vector<int> get_neighbours(int *mat, int node, int d, int value, int xsize, int ysize);
//void limits(int *mat, int node, int d, int &xmin, int &ymin, int &xmax, int &ymax, int xsize, int ysize);
//std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value, int xsize, int ysize);

int main(){
    int * T, xsize = 11, ysize = 11, node = 120, d = 5;
    std::vector<int> neighbours;
    T = new int[NODE_NUM];
    T = getMat("Tests/Sample/Ttest_6x6_15.txt", NODE_NUM);
    neighbours = get_specific_neighbours(T, node, d, 2, xsize, ysize);

    T[node] = -1;
    for(int i = 0; i<neighbours.size(); i++) {
        T[neighbours[i]] = 10;
    }

    save_mat(121, T, "Tests/neighbours/T.txt");
}
/*
std::vector<int> get_neighbours(int *mat, int node, int d, int xsize, int ysize){ //devolver puntero??
    // devuelve los vecinos a distancia d
    std::vector<int> neighbour_nodes;
    int x, y, xmin, ymin, xmax, ymax, node2;
    limits(mat, node, d, xmin, ymin, xmax, ymax, xsize, ysize);
    for(int xcoor = xmin; xcoor<=xmax; xcoor++){
        for(int ycoor = ymin; ycoor<=ymax; ycoor++){
            coordinates_to_node(node2, xcoor, ycoor, xsize, ysize);
            if(node2!=node){
                neighbour_nodes.push_back(node2);
            }
            
        }
    }
    return neighbour_nodes;

}

void limits(int *mat, int node, int d, int &xmin, int &ymin, int &xmax, int &ymax, int xsize, int ysize){
    int x, y;
    node_to_coordinates(node, x, y, xsize, ysize);
    xmin = x-d; ymin = y-d; xmax = x+d; ymax = y+d;
    while(xmin<0){
        xmin++;
    }
    while(ymin<0){
        ymin++;
    }
    while(xmax>(xsize-1)){
        xmax--;
    }
    while(ymax>(ysize-1)){
        ymax--;
    }

};



std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value, int xsize, int ysize){
    std::vector<int> neighbour_nodes, specific_neighbour_nodes;
    neighbour_nodes = get_neighbours(mat, node, d, xsize, ysize);

    for(int i = 0; i<neighbour_nodes.size(); i++){
        if(mat[neighbour_nodes[i]] == value){
            specific_neighbour_nodes.push_back(neighbour_nodes[i]);
        }
    }
    return specific_neighbour_nodes;
};
*/