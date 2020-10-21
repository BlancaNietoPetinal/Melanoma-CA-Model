#include <iostream>
#include <fstream> //getMat
#include "destructionlib.h"

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

    get_coordinates(leftnode, xsize, ysize, xleft, _);
    get_coordinates(rightnode, xsize, ysize, xright, _);
    get_coordinates(supnode, xsize, ysize, _, ysup);
    get_coordinates(infnode, xsize, ysize, _, yinf);
     //std::cout<<"ysup: "<<ysup<<" yinf: "<<yinf<<" xl: "<<xleft<<" xright: "<<xright<<std::endl;
    mat = get_squeare(xleft, xright, ysup, yinf, xsize, ysize);

    match_matrices(T, mat, xsize, ysize);
    return mat;
};
void get_coordinates(int node, int xsize, int ysize, int &xcoor, int &ycoor){
    int n = 0;
    for(int x = 0; x<xsize; x++){
        for(int y = 0; y<ysize; y++){
            n++;
            if(n==node){
                xcoor = x;
                ycoor = y;
                break;
            }
        }
    }
}
int * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize){
    int node = 0;
    int * mat;
    mat = new int[xsize*ysize];
    for(int x = 0; x<xsize; x++){
        for(int y = 0; y<ysize; y++){
            if( ((x>=(xleft-1)) && (y>=ysup)) && ((x<=(xright+1)) && (y<=(yinf+2))) ){
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


