#include <iostream>
#include <array>
#include <fstream>
#include <vector>
# include <time.h>
#include "../constants.hpp"
using namespace constants;

void create_vec(int node_num, int mat[], int value);
void save_mat(int node_num, int mat[], std::string filename);
void grow(int node_num, double M[], double N[], int T[], int D[], int H[]);
void neighbours(int node, int T[], std::vector<int> &neighbour_nodes);
void free_neighbours(int T[], std::vector<int> &neighbour_nodes, std::vector<int> &free_nodes );



/*
std::array<std::array<float*,NX>,NY> create_N0(float K);

class Pixel{
    private:
        char cel_type;
        float M, N;
    public:
        Pixel();
        Pixel(char _type);
        char getType();
        ~Pixel(){};
};

class Grid{
    private:

        std::array<std::array<Pixel*,NX>,NY> p; //mejor usar array que *p[rows][cols]
        //std::array<std::array<Pixel*,NX>,NY> X;
        std::array<std::array<int,NX>,NY> X;
        Pixel  p0;
    public:
        Grid(); //create the grid
        std::array<std::array<int,NX>,NY> getMatrix(char cell_type);
        void printPixel(int x, int y);
        void addPixel(int x, int y, Pixel pxl);
        
        ~Grid(){};
};
*/
