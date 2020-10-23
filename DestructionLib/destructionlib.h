#include <iostream>
#include <fstream> //getMat
#include <cmath> //is_integer
#include <vector> // neighbours
#include "../constants.hpp"
using namespace constants;

int* getMat(std::string filename, int matlen);
void get_limits(int * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf);
int leftBorder(int * mat, int size);
int rightBorder(int * mat, int size);
int superiorBorder(int * mat, int xsize, int ysize);
int inferiorBorder(int * mat, int xsize, int ysize);
int * effectorCellPlacement(int x0, int y0, int xf, int yf, int xsize, int ysize, int *T);
void node_to_coordinates(int node, int &x, int &y, int xsize, int ysize);
void coordinates_to_node(int &node, int x, int y, int xsize, int ysize);
int * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize);
void match_matrices(int * T, int * mat, int xsize, int ysize);

void tumor_lysis(int * T, int * E, int *D, int xsize, int ysize);

void cell_lysis(int * T, int *E, int node, int xsize , int ysize);
void recruitment();
void inactivation();
std::vector<int> n_neighbours(int n, int * mat, int node, int xsize, int ysize);
bool are_neighbours_interior(int node, int n, int xsize, int ysize);