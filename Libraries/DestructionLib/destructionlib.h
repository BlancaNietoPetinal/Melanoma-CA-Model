#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include <ctime>
#include <fstream> //getMat
#include <cmath> //is_integer
#include <vector> // neighbours
#include "../../constants.hpp"
#include "../Tools/toolslib.h"

using namespace constants;


void get_tumor_limits(double * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf);
void tumor_lysis(double T[], double E[], int Ecount[], double D[], double H[]);
void lysis(double T[], double E[], int Ecount[], double D[], double H[], int node, std::mt19937 generator);
void recruitment(double T[], double E[], double D[], double H[], int node, std::mt19937 generator);
void inactivation(double T[], double E[], int Ecount[], double H[], int node, std::mt19937 generator);
void Emigration(double T[], double E[], int Ecount[], double H[], double D[], int node, std::mt19937 generator);
int summation(double mat[], std::vector<int> neighbours);
bool no_cells(double mat[]);
void random_place_cell(double * mat, int n_cells_to_place); //BORRAR?
void effectorCellPlacement(double T[], double E[]);

void sector(double E[], double T[], int quadrant);
void first_quad(double E[], double T[]);
void second_quad(double E[], double T[]);
void third_quad(double E[], double T[]);
void fourth_quad(double E[], double T[]);