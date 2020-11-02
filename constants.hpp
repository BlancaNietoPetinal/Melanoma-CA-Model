#include <ctime>
#include <cmath>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  const int NNODES = 6;
  const int QUAD_NUM = 3;
  const int NX = 10;
  const int NY = 10;
  const int ITERATIONS = 350;
  const int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  const int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  const double L_N = 200;
  const double L_M = 10;
  const double COEF_DIFF = 0.1; //in assemble
  const double STARTING_NUTRIENTS = 0.2;
  const double ALPHA = 4/(2 * NX - 1 );
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