#include <iostream>
#include <fstream> //getMat
#include <cmath> //is_integer
#include "../constants.hpp"
using namespace constants;

int* getMat(std::string filename, int matlen);
void get_limits(int * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf);
int leftBorder(int * mat, int size);
int rightBorder(int * mat, int size);
int superiorBorder(int * mat, int xsize, int ysize);
int inferiorBorder(int * mat, int xsize, int ysize);
int * effectorCellPlacement(int x0, int y0, int xf, int yf, int xsize, int ysize, int *T);
void get_coordinates(int node, int xsize, int ysize, int &xcoor, int &ycoor);
int * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize);
void match_matrices(int * T, int * mat, int xsize, int ysize);