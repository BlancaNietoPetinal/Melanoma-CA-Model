#include <chrono>
#include <iostream>
#include <random>
#include <fstream> //getMat
#include <cmath> //is_integer
#include <vector> // neighbours
#include "../constants.hpp"
#include "../Tools/toolslib.h"

using namespace constants;


void get_tumor_limits(double * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf);
int leftBorder(double * mat, int size);
int rightBorder(double * mat, int size);
int superiorBorder(double * mat, int xsize, int ysize);
int inferiorBorder(double * mat, int xsize, int ysize);
double * effectorCellPlacement(int x0, int y0, int xf, int yf, int xsize, int ysize, double *T);
double * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize);
void match_matrices(double * T, double * mat, int xsize, int ysize);
void tumor_lysis(double T[], double E[], int Ecount[], double D[], double H[], int xsize, int ysize);
void lysis(double T[], double E[], int Ecount[], double D[], double H[], int node, int xsize , int ysize, std::mt19937 generator);
void recruitment(double T[], double E[], double D[], double H[], int node, int xsize, int ysize, std::mt19937 generator);
void inactivation(double T[], double E[], int Ecount[], double H[], int node, int xsize, int ysize, std::mt19937 generator);
void Emigration(double T[], double E[], int Ecount[], double H[], double D[], int node, int xsize, int ysize, std::mt19937 generator);
int summation(double mat[], std::vector<int> neighbours);
