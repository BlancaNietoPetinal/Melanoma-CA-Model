#include <iostream>
#include <fstream>
#include <math.h>
#include "../Tools/toolslib.h"
#include "../constants.hpp"
using namespace constants;

double* RK4(double T, double H, double E);
double f1(double t, double T,double H,double E);
double f2(double t, double T,double H,double E);
double f3(double t, double T,double H,double E);
