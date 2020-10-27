#include <ctime>
#include <cmath>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  const int NNODES = 6;
  const int QUAD_NUM = 3;
  const int NX = 70;
  const int NY = 70;
  const int ITERATIONS = 200;
  const int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  const int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  const double L_N = 200;
  const double L_M = 100;
  const double COEF_DIFF = 1; //in assemble
  const double STARTING_NUTRIENTS = 1;
  const double ALPHA = 2;//10/(2 * NX - 1 );
  const double NEC = 0.1;
  const double MIG = 1000;
  const double DIV = 0.3;
  // tumor lysis consts
  const double LYS = 1;
  const int NEIGBOUR_NUMBER = 2; // for tumor destruction laws
}
#endif