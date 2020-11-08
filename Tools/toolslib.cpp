//#include <iostream>
//#include <fstream> //getMat
#include "toolslib.h"
#include <random>
#include <chrono>
#include <array>
#include <algorithm>

int * get_mat(std::string filename, int matlen){
    int * mat;
    mat = new int[matlen];
    std::ifstream file;
    int loop = 0;
    file.open(filename);
    if(file.is_open()){
        while(file >> mat[loop]){
            loop++;
        }
        file.close();
    }
    else{
        std::cout<<"No se pudo abrir el fichero.";
    }
    return mat;
};

void node_to_coordinates(int node, int &x, int &y, int xsize, int ysize){
    int n = 0;
    bool esc = 0;
    if(node>=(xsize*ysize)){
        std::cout<<"La matriw es demasiado pequena para albergar ese nodo.";
    }
    for(int xcoor = 0; xcoor<xsize; xcoor++){
        for(int ycoor = 0; ycoor<ysize; ycoor++){
            if(n == node){
                x = xcoor;
                y = ycoor;
                esc = true;
                break;
            }
            n++;
        }
        if(esc){
            break;
        }
    }
};
void coordinates_to_node(int &node, int x, int y, int xsize, int ysize){
    int n=0;
    bool esc = 0;
    for(int xcoord = 0; xcoord<xsize; xcoord++){
        for(int ycoord = 0; ycoord<ysize; ycoord++){
            if( (xcoord==x) && (ycoord==y) ){
                node = n;
                esc = 1;
                break;
            }
            n++;
        }
        if(esc){
            break;
        }
    }
}

std::vector<int> get_neighbours(int *mat, int node, int d, int xsize, int ysize){ //devolver puntero??
    // devuelve los n vecinos
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
    // devuelve los limites a una distancia d de un nodo dado
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
std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value, char mode,  int xsize, int ysize){
    // gets the n neighbours with a specific value and a operator specified
    std::vector<int> neighbour_nodes, specific_neighbour_nodes;
    neighbour_nodes = get_neighbours(mat, node, d, xsize, ysize);

    for(int i = 0; i<neighbour_nodes.size(); i++){
        switch (mode)
        {
        case '=':
            if((mat[neighbour_nodes[i]] == value)){
                specific_neighbour_nodes.push_back(neighbour_nodes[i]);
            }
            break;
        
        case '>':
            if(mat[neighbour_nodes[i]] > value){
                specific_neighbour_nodes.push_back(neighbour_nodes[i]);
            }
            break;
        case '<':
            if(mat[neighbour_nodes[i]] < value){
                specific_neighbour_nodes.push_back(neighbour_nodes[i]);
            }
        }
    }

    return specific_neighbour_nodes;
};

void create_vec(int node_num, int mat[], int value){ //poner un mensaje si node_num no es correcto
    for (int i = 0; i<node_num; i++) 
    {
        mat[i] = value;
    }
}

void save_mat(int node_num, int mat[], std::string filename){
    std::ofstream File(filename); 
    for(int node = 0; node<node_num; node++){
        File << mat[node] << std::endl;
    }
    File.close();
}

int* get_random_nodes(int xsize, int ysize){
    int* random_nodes;
    random_nodes = new int[xsize*ysize];

    for(int node = 0; node < (xsize*ysize); node++){
        random_nodes[node] = node;
    }
    std::random_shuffle(&random_nodes[0], &random_nodes[xsize*ysize]);
    return random_nodes;
}

bool is_tumor_in_border(int *mat, int xsize, int ysize){ //cambiar nombre
    bool result=false;
    int node = 0;
    for(int x = 0; x<xsize; x++){
        for(int y = 0; y<ysize; y++){
            if( (x==0) || (y==0) || (x==(xsize-1)) || (y==(ysize-1))){
                if(mat[node] != 0){
                    result = true;
                }
            }
            node++;
        }
    }
    return result;
};