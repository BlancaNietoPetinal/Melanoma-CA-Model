#include <iostream>
#include <fstream> //getMat
#include <cmath> //is_integer
#include <vector> // neighbours
#include "../constants.hpp"
using namespace constants;

int* get_mat(std::string filename, int matlen);
void node_to_coordinates(int node, int &x, int &y, int xsize, int ysize);
void coordinates_to_node(int &node, int x, int y, int xsize, int ysize);
std::vector<int> get_neighbours(int *mat, int node, int d, int xsize, int ysize);
void limits(int *mat, int node, int d, int &xmin, int &ymin, int &xmax, int &ymax, int xsize, int ysize);
std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value, char mode, int xsize, int ysize);
void create_vec(int node_num, int mat[], int value);
void save_mat(int node_num, int mat[], std::string filename);
