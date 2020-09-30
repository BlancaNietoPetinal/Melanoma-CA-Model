#include <iostream>
#include <array>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include "MyFun.h"


void save_mat(int node_num, int mat[], std::string filename){
    std::ofstream File(filename); 
    for(int node = 0; node<node_num; node++){
        File << mat[node] << std::endl;
    }
    File.close();
}
void free_neighbours(int T[], std::vector<int> &neighbour_nodes, std::vector<int> &free_nodes){
    int node;
    for(int neighbour = 0; neighbour<neighbour_nodes.size(); neighbour++){
        node = neighbour_nodes[neighbour];
        if (T[node] == 0){
            free_nodes.push_back(node);
        }
    };
};
void neighbours(int node, int T[], std::vector<int> &neighbour_nodes){ // MEJORA: crear una funcion que te devuelva los nodos de al rededor
    int X = 2*NX-1;
    int Y = 2*NY-1;
    //nodos internos
    if( (node%X != 0) && (node%X != (X-1)) && (node > (X-1)) && (node < (X * (Y-1))) )
    {
        //std::cout<<"INTERNOS";
        neighbour_nodes.push_back(node-1);
        neighbour_nodes.push_back(node+1);
        neighbour_nodes.push_back(node-X);
        neighbour_nodes.push_back(node+X);
    }

    // nodos externos (sin vertices)
    else if ( (node > (X * (Y-1))) && (node < (X*Y-1)) )  //arriba
    {
        //std::cout<<"EXTERNOS";
        neighbour_nodes.push_back(node-1);
        neighbour_nodes.push_back(node+1);
        neighbour_nodes.push_back(node-X);
    }

    else if ( (node%X == 0) && (node != (X * (Y-1))) && node != 0) // izqda
    { 
        //std::cout<<"IZQDA";
        neighbour_nodes.push_back(node+1);
        neighbour_nodes.push_back(node-X);
        neighbour_nodes.push_back(node+X);
    }

    else if ( (node%X == X-1) && (node != (X*Y-1)) && (node != (X-1))) //dcha
    { 
        //std::cout<<"DCHA";
        neighbour_nodes.push_back(node-1);
        neighbour_nodes.push_back(node-X);
        neighbour_nodes.push_back(node+X);
    }
    else if ( (node < (X-1)) && (node != 0) ){ //abajo
        //std::cout<<"ABAJO";
        neighbour_nodes.push_back(node-1);
        neighbour_nodes.push_back(node+1);
        neighbour_nodes.push_back(node+X);
    }

    else{  
        //std::cout<<"ESQUINAS";
        if( node == (X*Y - 1) ) // (X,Y)
        {
            neighbour_nodes.push_back(node-1);
            neighbour_nodes.push_back(node-X);
        }

        else if(node == 0) // (1,1)
        { 
            neighbour_nodes.push_back(node+1);
            neighbour_nodes.push_back(node+X);
        }

        else if( node == (X-1) ) // (X,1)
        {
            neighbour_nodes.push_back(node-1);
            neighbour_nodes.push_back(node+X);
        }

        else // (1,Y)
        {
            neighbour_nodes.push_back(node+1);
            neighbour_nodes.push_back(node-X);
        }
    }
    return;
};
void necrosis(double &M, int &T, int &D, double rnd_n){
    float P = exp(- pow((M/T),2)/pow(ThNec,2));
    if( (P>rnd_n) && (D == 0) ){ // hay cel tumoral + no hay cel necrosada
        T = T - 1;
        if(T == 0){
            D = 1;
        }
    }
    return;
}
void migracion(double M[], int T[], int D[], int H[], int node, double rnd_n){
    std::vector<int> neighbour_nodes, free_nodes;
    int neighbour_node, index;
    float P = 1 - exp( - pow((sqrt(T[node]) * M[node]),2) / pow(ThMig,2));
    neighbours(node, T, neighbour_nodes);
    free_neighbours(T, neighbour_nodes, free_nodes);
    if(P>rnd_n){
        if( !free_nodes.empty() ){ // room, pick random
            index = rand() % free_nodes.size();
            neighbour_node = free_nodes[index];
            if(T[node] > 1){
                T[node]--;
                T[neighbour_node] = 1;
                if (H[neighbour_node] == 1){
                    H[neighbour_node] = 0;
                }
                else if (D[neighbour_node] == 1) {
                    D[neighbour_node] = 0;
                }
            }
            else{
                T[node]--;
                T[neighbour_node]++;
                if (H[neighbour_node] == 1){
                    H[neighbour_node] = 0;
                    H[node] = 1;
                }
                else if (D[neighbour_node] == 1) {
                    D[neighbour_node] = 0;
                    D[node] = 1;
                }
            }
        }
        else{
            
            index = rand() % neighbour_nodes.size();
            neighbour_node = neighbour_nodes[index];
            T[node]--;
            T[neighbour_node]++;
            D[node]++; //Esto lo he supuesto, preguntar
        }
    }
};
void division(double N[], int T[], int D[], int H[], int node, double rnd_n){
    std::vector<int> neighbour_nodes, free_nodes;
    int neighbour_node, index;
    float P;
    P = exp( 1 - pow(N[node]/T[node], 2)/ pow(ThDiv,2) );
    if(P>rnd_n){
        neighbours(node, T, neighbour_nodes);
        free_neighbours(T, neighbour_nodes, free_nodes);

        if( free_nodes.empty() ){ //apilamiento
            T[node]++;
        }
        else{
            index = rand() % free_nodes.size(); //pick randomly
            neighbour_node = free_nodes[index];
            T[neighbour_node] = 1;
            if(H[neighbour_node] == 1){
                H[neighbour_node] = 0;
            }
            else{
                D[neighbour_node] = 0;
            }
        }
    }
};
void grow(int node_num, double M[], double N[], int T[], int D[], int H[]){  
    std::default_random_engine generator{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::normal_distribution<double> distribution(0.1,0.3); //DUDA: que valores meto aqui??
    std::uniform_int_distribution<int> dice_distribution(1,3);
    double rnd_n;
    int dice;
    for(int node = 0; node < node_num; node++)
    {
        if(T[node] >= 1){
            rnd_n = distribution(generator);
            dice = dice_distribution(generator);
            switch (dice)
            {
            case 1:
                necrosis(M[node], T[node], D[node], rnd_n);
                break;
            case 2: 
                migracion(M, T, D, H, node, rnd_n);
                break;
            case 3:
                division(N, T, D, H, node, rnd_n);
                break;
            } 
        }

    }    
}
void create_vec(int node_num, int mat[], int value){
    for (int i = 0; i<node_num; i++) 
    {
        mat[i] = value;
    }
}

/*************************************
Pixel::Pixel(){cel_type = 'O'; M = 0; N = 0;};
Pixel::Pixel(char _type){cel_type = _type;};
char Pixel::getType(){return cel_type;}


Grid::Grid(){
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
        p[i][j] = &p0;
        }
    }
};


std::array<std::array<float*,NX>,NY> create_N0(float K0){
    std::array<std::array<float*,NX>,NY> N0;
    for(int j = 0; j<NY; j++){
        N0[0][j] = &K0;
    }
    return N0;
}

void neighbours(int node, int T[], std::vector<int> &neighbour_nodes){ // MEJORA: crear una funcion que te devuelva los nodos de al rededor

    //nodos internos
    if( (node%NX != 0) && (node%NX != (NX-1)) && (node > (NX-1)) && (node < (NX * (NY-1))) )
    {
        if ( T[node-1] == 0 ){
            neighbour_nodes.push_back(node-1);
        }
        if ( T[node+1] == 0 ){
            neighbour_nodes.push_back(node+1);
        }
        if ( T[node-NX] == 0 ){
            neighbour_nodes.push_back(node-NX);
        } 
        if ( T[node+NX] == 0 ){
            neighbour_nodes.push_back(node+NX);
        }
    }

    // nodos externos (sin vertices)
    else if ( (node > (NX * (NY-1))) && (node < (NX*NY-1)) )  //arriba
    {
        if ( T[node-1] == 0 ){
            neighbour_nodes.push_back(node-1);
        }
        if ( T[node+1] == 0 ){
            neighbour_nodes.push_back(node+1);
        }
        if ( T[node-NX] == 0 ){
            neighbour_nodes.push_back(node-NX);
        } 
    }

    else if ( (node%NX == 0) && (node != (NX * (NY-1))) && node != 0) // izqda
    { 
        if ( T[node+1] == 0 ){
            neighbour_nodes.push_back(node+1);
        }
        if ( T[node-NX] == 0 ){
            neighbour_nodes.push_back(node-NX);
        } 
        if ( T[node+NX] == 0 ){
            neighbour_nodes.push_back(node+NX);
        }
    }

    else if ( (node%NX == NX-1) && (node != (NX*NY-1)) && (node != (NX-1))) //dcha
    { 
        if ( T[node-1] == 0 ){
            neighbour_nodes.push_back(node-1);
        }
        if ( T[node-NX] == 0 ){
            neighbour_nodes.push_back(node-NX);
        } 
        if ( T[node+NX] == 0 ){
            neighbour_nodes.push_back(node+NX);
        }
    }
    else if ( (node < (NX-1)) && (node != 0) ){ //abajo
        if ( T[node-1] == 0 ){
            neighbour_nodes.push_back(node-1);
        }
        if ( T[node+1] == 0 ){
            neighbour_nodes.push_back(node+1);
        } 
        if ( T[node+NX] == 0 ){
            neighbour_nodes.push_back(node+NX);
        }
    }

    else{  

        if( node == (NX*NY - 1) ) // (NX,NY)
        {
            if ( T[node-1] == 0 ){
                neighbour_nodes.push_back(node-1);
            }

            if ( T[node-NX] == 0 ){
                neighbour_nodes.push_back(node-NX);
            } 
        }

        else if(node == 0) // (1,1)
        { 
            if ( T[node+1] == 0 ){
                neighbour_nodes.push_back(node+1);
            }

            if ( T[node+NX] == 0 ){
                neighbour_nodes.push_back(node+NX);
            } 
        }

        else if( node == (NX-1) ) // (NX,1)
        {
            if ( T[node-1] == 0 ){
                neighbour_nodes.push_back(node-1);
            }
            if ( T[node+NX] == 0 ){
                neighbour_nodes.push_back(node+NX);
            }
        }

        else // (1,NY)
        {
            if ( T[node+1] == 0 ){
                neighbour_nodes.push_back(node+1);
            }
            if ( T[node-NX] == 0 ){
                neighbour_nodes.push_back(node-NX);
            } 
        }
    }

    return;
};

void Grid::printPixel(int x, int y){std::cout<<p[x][y]->getType();};
void Grid::addPixel(int x, int y, Pixel pxl){p[x][y] = &pxl;};
//std::array<std::array<Pixel*,NX>,NY> Grid::getMatrix(char cell_type){
std::array<std::array<int,NX>,NY> Grid::getMatrix(char cell_type){
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            if(cell_type == p[i][j]->getType()){
                //X[i][j] = p[i][j];
                X[i][j] = 1;
            }
            else{
                //X[i][j] = &p0;
                X[i][j] = 0;
            }
        }
    }
return X;
};

*/



