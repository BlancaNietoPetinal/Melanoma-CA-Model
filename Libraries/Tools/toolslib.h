#include <iostream>
#include <fstream> //getMat
#include <cmath> //is_integer
#include <vector> // neighbours
#include <array>
#include "../../constants.hpp"
using namespace constants;

int* get_mat(std::string filename, int matlen);
void node_to_coordinates(int node, int &x, int &y, int xsize, int ysize);
void coordinates_to_node(int &node, int x, int y, int xsize, int ysize);
std::vector<int> get_neighbours(int *mat, int node, int d, int xsize, int ysize);
std::vector<int> get_neighbours(double *mat, int node, int d, int xsize, int ysize);
void limits(int *mat, int node, int d, int &xmin, int &ymin, int &xmax, int &ymax, int xsize, int ysize);
void limits(double *mat, int node, int d, int &xmin, int &ymin, int &xmax, int &ymax, int xsize, int ysize);
std::vector<int> get_specific_neighbours(int *mat, int node, int d, int value, char mode, int xsize, int ysize);
std::vector<int> get_specific_neighbours(double *mat, int node, int d, int value, char mode,  int xsize, int ysize);
void create_vec(int node_num, int mat[], int value);
void save_mat(int node_num, int mat[], std::string filename);
void save_mat(int node_num, float mat[], std::string filename);
void save_mat(int node_num, double mat[], std::string filename);
int* get_random_nodes(int xsize, int ysize);
bool is_tumor_in_border(int *mat, int xsize, int ysize);
void changeNegativeValue(double &value);
double* int_2_double(int mat[], int matlen);
int cell_counter(int mat[], int node_num);
int cell_counter(double mat[], int node_num);