#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <time.h>
#include "../constants.hpp"
#include "../Tools/toolslib.h"

using namespace constants;

void necrosis(double M[], int T[], int D[], int node, std::mt19937 generator);
void division(double N[], int T[],  int D[], int H[], int node, int xsize, int ysize, std::mt19937 generator);
void migracion(double M[], int T[], int D[], int H[], int node, int xsize, int ysize, std::mt19937 generator);
void grow(double M[], double N[], int T[], int D[], int H[], int xsize, int ysize);
void changeNegativeValue(double &value);

