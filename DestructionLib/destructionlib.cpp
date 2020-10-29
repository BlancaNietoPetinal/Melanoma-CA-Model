#include <iostream>
#include <fstream> //getMat
#include "destructionlib.h"
#include "../GeneratorLib/generatorlib.h" // get n_neigh, quitar dependencia en cuanto se pueda
#include <random>
#include <chrono>
#include <array>

int * getMat(std::string filename, int matlen){
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
void get_tumor_limits(int * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf){
    left = leftBorder(mat, xsize*ysize);
    right = rightBorder(mat, xsize*ysize);
    sup = superiorBorder(mat, xsize, ysize);
    inf = inferiorBorder(mat, xsize, ysize);
}
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

int leftBorder(int * mat, int size){
    int node = 0;
    while(mat[node]==0){
        node++;
    }
    return node;
};
int rightBorder(int * mat, int size){
    int lastNode;
    for(int node = 0; node<size ; node++){
        if(mat[node] != 0){
            lastNode = node;
        }
    }
    return lastNode;
};
int superiorBorder(int * mat, int xsize, int ysize){
    int xcoordinate=0, ycoordinate=ysize, aux, node = 0, y,result;
    for(int x = 0; x<xsize; x++){
        aux = 0;
        y = 0;
        while((y<ysize)){
            if( (mat[node]!=0) && (ycoordinate>y) && (aux==0) ){
                xcoordinate = x;
                ycoordinate = y;
                aux = 1;
                result = node;
            }
            y++;
            node++;
            
        }
    }
    return result;
};
int inferiorBorder(int * mat, int xsize, int ysize){
    int xcoordinate=0, ycoordinate=0, aux, node = 0, y,result;
    for(int x = 0; x<xsize; x++){
        aux = 0;
        y = 0;
        while((y<ysize)){
            if( (mat[node]!=0) && (ycoordinate<y) && (aux==0) ){
                xcoordinate = x;
                ycoordinate = y;
                aux = 1;
                result = node;
            }
            y++;
            node++;
            
        }
    }
    return result;
}
int * effectorCellPlacement(int leftnode, int rightnode, int supnode, int infnode, int xsize, int ysize, int *T){
    int * mat;
    int xleft, xright, ysup, yinf, _;
    mat = new int[xsize*ysize];

    node_to_coordinates(leftnode, xleft, _, xsize, ysize);
    node_to_coordinates(rightnode, xright, _, xsize, ysize);
    node_to_coordinates(supnode, _, ysup, xsize, ysize);
    node_to_coordinates(infnode, _, yinf, xsize, ysize);
    mat = get_squeare(xleft, xright, ysup, yinf, xsize, ysize);

    match_matrices(T, mat, xsize, ysize);
    return mat;
};
int * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize){
    int node = 0;
    int * mat;
    mat = new int[xsize*ysize];
    for(int x = 0; x<xsize; x++){
        for(int y = 0; y<ysize; y++){
            if( ((x>=(xleft-1)) && (y>=(ysup-1))) && ((x<=(xright+1)) && (y<=(yinf+2))) ){
                mat[node] = 1;
            }
            else{
                mat[node] = 0;
            }
            node++;
        }
    }
    return mat;
};
void match_matrices(int *T,int *mat, int xsize, int ysize){
    int totalsize = xsize*ysize;
    for(int node = 0; node<totalsize; node++){
        if(T[node]!=0){
            mat[node] = 0;
        }
    }
};

void tumor_lysis(int * T, int * E, int *Ecount, int *D, int *H, int xsize, int ysize){
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> dice_distribution(1,2);
    std::vector<int> Tneighbours;
    int dice, node = 0;
    for(int x = 0; x < xsize; x++)
    {
        for(int y = 0; y < ysize; y++)
        {

            if(E[node]==1){
                
                Tneighbours = get_specific_neighbours(T, node, 1, 1, xsize, ysize);
                if(Tneighbours.size()!=0){
                    lysis(T, E, Ecount, D, node, xsize, ysize);
                }
                else{
                    dice = dice_distribution(generator);
                    switch (dice)
                    {
                    case 1:
                        inactivation(T, E, H, node, xsize, ysize);
                        break;
                    
                    case 2:
                        Emigration(E, H, node, xsize, ysize);
                        break;
                    }
                }
            }
            else if(T[node]!=1){
                recruitment(T, E, D, H, node, xsize, ysize);
            }
            
            node++;
        }
    }
};

void lysis(int * T, int *E, int *Ecount, int *D, int node, int xsize, int ysize){
    std::vector<int> Eneighbours, Tneighbours;
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::normal_distribution<double> distribution(0,LYS);
    std::uniform_int_distribution<> u_distrib(1,50);
    int NNEIG = 1, neignode, index;
    double rnd_n = distribution(generator), P;

    Eneighbours = get_specific_neighbours(E, node, NNEIG, 1, xsize, ysize);
    Tneighbours = get_specific_neighbours(T, node, 1, 1, xsize, ysize);
    P = 1-exp(-pow(Eneighbours.size()/LYS,2));
    P = 30; //DELETE
    if( (P>abs(rnd_n)) && (Tneighbours.size()!=0) ){
        std::cout<<"E = 1"<<std::endl;
        index = u_distrib(generator) % Tneighbours.size();
        neignode = Tneighbours[index];
        T[neignode]--; D[neignode]++; Ecount[node]++;
        // ADD RECRUITMENT HERE
        if(Ecount[node]==3){
            E[node] = 0; //celula sana
        }
    }

};

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

std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value,  int xsize, int ysize){
    std::vector<int> neighbour_nodes, specific_neighbour_nodes;
    neighbour_nodes = get_neighbours(mat, node, d, xsize, ysize);

    for(int i = 0; i<neighbour_nodes.size(); i++){
        if(mat[neighbour_nodes[i]] == value){
            specific_neighbour_nodes.push_back(neighbour_nodes[i]);
        }
    }
    return specific_neighbour_nodes;
};


void recruitment(int *T, int *E, int *D, int *H, int node, int xsize, int ysize){
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::normal_distribution<double> distribution(0,REC);
    std::uniform_int_distribution<> u_distrib(1,50);
    std::vector<int> Tneighbours, neighbours;
    int index, neignode;

    Tneighbours = get_specific_neighbours(T, node, NEIGBOUR_NUMBER, 1, xsize, ysize);
    double rnd_n = distribution(generator);
    double P = exp(-pow(1/(Tneighbours.size()*LYS),2));

    if(P>abs(rnd_n) && ((H[node] == 1) || (D[node] >= 1))){
        neighbours = get_specific_neighbours(E, node, 1, 0, xsize, ysize);
        index = u_distrib(generator) % neighbours.size();
        neignode = neighbours[index];
        D[neignode] = 0; H[neignode] = 0; E[neignode] = 1;
    }
};
void inactivation(int *T, int *E, int *H, int node, int xsize, int ysize){
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::normal_distribution<double> distribution(0,INC);
    std::vector<int> Tneighbours;
    double rnd_n = distribution(generator), P;
    Tneighbours = get_specific_neighbours(T, node, 1, 1, xsize, ysize);
    P = 1 - exp(- pow(1/(Tneighbours.size()*INC),2));
    if(P>abs(rnd_n)){
        E[node] = 0;
        H[node] = 1;
    }
};
void Emigration(int *E, int *H, int node, int xsize, int ysize){
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> u_distrib(0,100);
    std::vector<int> Hneighbours;
    int index, neignode;
    Hneighbours = get_specific_neighbours(H, node, 1, 0, xsize, ysize);
    index = u_distrib(generator) % Hneighbours.size();
    neignode = Hneighbours[index];
    E[node] = 0; E[neignode] = 1;
};