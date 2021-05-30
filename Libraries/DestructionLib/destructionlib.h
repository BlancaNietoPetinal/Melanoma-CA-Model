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


//void get_tumor_limits(int * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf);
void tumor_lysis(int T[], int E[], int Ecount[], int D[], int H[]);
void lysis(int T[], int E[], int Ecount[], int D[], int H[], int node, std::mt19937 generator);
void recruitment(int T[], int E[], int D[], int H[], int node, std::mt19937 generator);
void inactivation(int T[], int E[], int Ecount[], int H[], int node, std::mt19937 generator);
void Emigration(int T[], int E[], int Ecount[], int H[], int D[], int node, std::mt19937 generator);
int summation(int mat[], std::vector<int> neighbours);
bool no_cells(int mat[]);
void effectorCellPlacement(int T[], int E[]);
void get_lysis_ratio(int T[], int T0);

void sector(int E[], int T[], int quadrant);
void first_quad(int E[], int T[]);
void second_quad(int E[], int T[]);
void third_quad(int E[], int T[]);
void fourth_quad(int E[], int T[]);