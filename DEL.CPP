#include <iostream>
#include <map>
#include<fstream>


class Grid{ // Creates a grid of MxN pixels and
    private:
        int M, N;
    public:
        Grid(int, int);
        auto getGrid();
};

Grid::Grid(int _N, int _M){
    N = _N;
    M = _M;
};

auto Grid::getGrid(){ // auto allows the compiler to guess the method type with the variable type
    std::map<int,std::map<int,std::string>> grid; // create a 2D map (it can also be done with pair, but this way is more readable)
    grid[M][N] = ""; // creamos el grid 
    return grid;
};


int main(){
    Grid g1 = Grid(10,10);
    std::map<int,std::map<int,std::string>> cuadrante;
    cuadrante =  g1.getGrid();
    std::cout<<"El valor 1,1 es: "<<cuadrante[1][1]<<std::endl;
    std::ofstream File("Cuadrante.txt"); // open the file

    std::ofstream ofs("output_file");

};


/*
class Pixel{
    private:
        char type;
    public:
        Pixel(char);
};

Pixel::Pixel(char _type){
    type = _type;
}; */