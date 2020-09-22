#include <iostream>
#include <array>
#include <fstream>
#include <random>
#include "MyFun.h"

void save_mat(int node_num, int mat[], std::string filename){
    std::ofstream File(filename); 
    for(int node = 0; node<node_num; node++){
        File << mat[node] << std::endl;
    }
    File.close();
}

void T_change(int node_num, double M[], int T[], int D[]){  
    //REVISAR: hace falta inicializarlo siempre o se puede poner fuera??
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0,1.0);
    float Pdiv, Pnec, Pmig;
    float ThNec = 2.0, ThMig = 2.0, ThDiv = 2.0; // CAMBIAR: buscar el valor real del param
    
    for(int node = 0; node < node_num; node++) // iteramos en cada pixel
    {
        //double rnd_n = distribution(generator);
        double rnd_n = 0;
        Pnec = exp(- pow((M[node]/T[node]),2)/pow(ThNec,2));
        if( (Pnec>rnd_n) && (D[node] == 0) && (T[node] != 0) ){ // hay cel tumoral + no hay cel necrosada
            T[node] = T[node] - 1;

            if(T[node] == 0){
                D[node] = 1;
            }
        }
    }
};


void create_vec(int node_num, int mat[]){
    for (int i = 0; i<node_num; i++) 
    {
        mat[i] = 0;
    }
}


//*************************************
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

std::array<std::array<float*,NX>,NY> create_N0(float K0){
    std::array<std::array<float*,NX>,NY> N0;
    for(int j = 0; j<NY; j++){
        N0[0][j] = &K0;
    }
    return N0;
}



