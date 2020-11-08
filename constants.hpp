#include <ctime>
#include <cmath>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  const int NNODES = 6;
  const int QUAD_NUM = 3;
  const int NX = 50;
  const int NY = 50;
  const int ITERATIONS = 650;
  const int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  const int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  const double L_N = 270;
  const double L_M = 10;
  const double COEF_DIFF = 0.9; //in assemble
  const double STARTING_NUTRIENTS = 1; //0.4;
  const double ALPHA = 1;
  const double NEC = 0;
  const double MIG = 10000;
  const double DIV = 0.3;

  // tumor lysis consts
  const double LYS = 0.01;
  const double REC = 2;
  const double INC = 2;
  const int NEIGBOUR_NUMBER1 = 2; // for tumor destruction laws
  const int NEIGBOUR_NUMBER3 = 2; // for tumor destruction laws
}
#endif