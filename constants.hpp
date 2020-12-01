#include <ctime>
#include <cmath>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  const int NNODES = 6;
  const int QUAD_NUM = 3;
  const int NX = 50;
  const int NY = 50;
  const int ITERATIONS = 30;
  const int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  const int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  const double L_N = 270;
  const double L_M = 10;
  const double COEF_DIFF = 0.9; //in assemble
  const double STARTING_NUTRIENTS = 1; //0.4;
  const double ALPHA = 0.01;
  const double NEC = 0.01;
  const double MIG = 10000;
  const double DIV = 0.3;

  // tumor lysis consts
  const double LYS = 0.2;
  const double REC = 1;
  const double INC = 0.5;
  const int NEIGBOUR_NUMBER1 = 2; // for tumor destruction laws
  const int NEIGBOUR_NUMBER3 = 2; // for tumor destruction laws

  const float A12 = 1.1*pow(10,-10);
  const float A21 = 4.8*pow(10,-10);
  const float A31 = 2.8*pow(10,-9);
  const float R1 = 0;//5.14*pow(10,-1);
  const float R2 = 1.8*pow(10,-1);
  const float K1 = 9.8*pow(10,8);
  const float K2 = pow(10,9);
  const float DC = 20;//2.2;
  const float D3 = 6.12*pow(10,-2);
  const float G = 0.15; //3.75*pow(10,-2);
  const float SIGMA = 0; //7.5*pow(10,4);
  const float HC = 2.02*pow(10,7);
  const float L = 0.87; //1.2*pow(10,-1);
  const float S = 0.15; //1.6;
}
#endif