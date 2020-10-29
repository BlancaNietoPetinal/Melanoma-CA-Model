#include <iostream>
#include <fstream> //getMat
#include <cmath> //is_integer
#include <vector> // neighbours
#include "../constants.hpp"
using namespace constants;

int* getMat(std::string filename, int matlen);
void get_tumor_limits(int * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf);
int leftBorder(int * mat, int size);
int rightBorder(int * mat, int size);
int superiorBorder(int * mat, int xsize, int ysize);
int inferiorBorder(int * mat, int xsize, int ysize);
int * effectorCellPlacement(int x0, int y0, int xf, int yf, int xsize, int ysize, int *T);
void node_to_coordinates(int node, int &x, int &y, int xsize, int ysize);
void coordinates_to_node(int &node, int x, int y, int xsize, int ysize);
int * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize);
void match_matrices(int * T, int * mat, int xsize, int ysize);
std::vector<int> get_neighbours(int *mat, int node, int d, int xsize, int ysize);
void limits(int *mat, int node, int d, int &xmin, int &ymin, int &xmax, int &ymax, int xsize, int ysize);
std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value, char mode, int xsize, int ysize);

void tumor_lysis(int * T, int * E, int *Ecount, int *D, int *H, int xsize, int ysize);

void lysis(int * T, int *E, int *Ecount, int *D, int node, int xsize , int ysize);
void recruitment(int *T, int *E, int *D, int *H, int node, int xsize, int ysize);
void inactivation(int *T, int *E, int *H, int node, int xsize, int ysize);
void Emigration(int *E, int *H, int node, int xsize, int ysize);

