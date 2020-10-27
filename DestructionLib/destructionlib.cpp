#include <iostream>
#include <fstream> //getMat
#include "destructionlib.h"
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
void get_limits(int * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf){
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

void tumor_lysis(int * T, int * E, int *Ecount, int *D, int xsize, int ysize){
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> dice_distribution(1,3);
    int dice, node = 0;
    for(int x = 0; x < xsize; x++)
    {
        for(int y = 0; y < ysize; y++)
        {
            if(E[node]==1){
                dice = dice_distribution(generator);
                dice = 1; //DELETE
                switch (dice)
                {
                case 1:
                    lysis(T, E, Ecount, D, node, xsize, ysize);
                    break;
                
                case 2:
                    std::cout<<"OK"<<std::endl;
                    //recruitment();
                    break;

                case 3:
                    std::cout<<"OK"<<std::endl;
                    //inactivation();
                }
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

    Eneighbours = n_neighbours(NNEIG, E, node, xsize, ysize);
    Tneighbours = n_neighbours(1, T, node, xsize, ysize);
    P = 1-exp(-pow(Eneighbours.size()/LYS,2));
    P = 20; //DELETE
    if( (P>abs(rnd_n)) && (Tneighbours.size()!=0) ){
        index = u_distrib(generator) % Tneighbours.size();
        neignode = Tneighbours[index];
        T[neignode]--; D[neignode]++; Ecount[node]++;

        if(Ecount[node]==3){
            E[node] = 0; //celula sana
        }
    }

};

std::vector<int> n_neighbours(int n, int * mat, int node, int xsize, int ysize){ //intentar cambiarla por la que esta en Generation
    // Fetches the n closest neighbours returns a vector with the nodes
    std::vector<int> neighbours;
    int x, y, node2;

    while(!are_neighbours_interior(node, n, xsize, ysize)){
        n--;
    }
    
    node_to_coordinates(node, x, y, xsize, ysize);

    for(int i = (x-n); i<(x+n+1); i++){
        for(int j = (y-n); j<(y+n+1); j++){
            coordinates_to_node(node2, i, j, xsize, ysize); 
            if( (mat[node2] == 1) && (node2!=node)){
                neighbours.push_back(node2);
            }
        }
    }
    return neighbours;
}; 

bool are_neighbours_interior(int node, int n, int xsize, int ysize){
    bool result = true;
    int x, y;
    node_to_coordinates(node, x, y, xsize, ysize);
    if( ((x-n)<0) || ((y-n)<0) ){
        result = false;
    }
    return result;
}
void recruitment();
void inactivation();
