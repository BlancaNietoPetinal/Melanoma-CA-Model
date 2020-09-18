#include <iostream>
#include <array>
#include <fstream>
#include "MyFun.h"

Pixel::Pixel(){cel_type = 'O'; M = 0; N = 0;};
Pixel::Pixel(char _type){cel_type = _type;};
char Pixel::getType(){return cel_type;}


Grid::Grid(){
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
        p[i][j] = &p0;
        }
    }
};
void Grid::printPixel(int x, int y){std::cout<<p[x][y]->getType();};
void Grid::addPixel(int x, int y, Pixel pxl){p[x][y] = &pxl;};
std::array<std::array<Pixel*,30>,30> Grid::getMatrix(char cell_type){
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            if(cell_type == p[i][j]->getType()){
                X[i][j] = p[i][j];
            }
            else{
                X[i][j] = &p0;
            }
        }
    }
return X;
};


