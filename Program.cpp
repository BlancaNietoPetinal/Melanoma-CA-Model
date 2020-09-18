#include <iostream>
#include <array>
#include <fstream>
#include "FEM/fem2D.h"
#include "MyFun/MyFun.h"
#define cols 300
#define rows 300
// TODO: display with gnuplot? o Qt?






int main(){

    std::array<std::array<Pixel*,30>,30> Tmat, Emat, Hmat;
    Pixel p1('T'), p2('H');
    Grid g; //creamos el grid de pixeles
    
    g.addPixel(1,1,p1); // introducimos un valor
    Tmat = g.getMatrix('T'); // obtenemos las matrices de las celulas
    Emat = g.getMatrix('E'); 
    Hmat =  g.getMatrix('H');

    std::cout<<"(1,1) = "<<Tmat[1][1]->getType()<<std::endl;
    std::cout<<"(1,2) = "<<Tmat[1][2]->getType()<<std::endl;

    return 0;
};
