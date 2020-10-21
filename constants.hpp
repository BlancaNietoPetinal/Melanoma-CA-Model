#include <ctime>
#include <cmath>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  const int NNODES = 6;
  const int QUAD_NUM = 3;
  const int NX = 50;
  const int NY = 50;
  const int ITERATIONS = 90;
  const int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  const int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  const double L_N = 200;
  const double L_M = 100;
  const double COEF_DIFF = 0.6; //in assemble
  const double STARTING_NUTRIENTS = 1;
  const double ALPHA = 15;//10/(2 * NX - 1 );
  const double NEC = 0.1;
  const double MIG = 1;
  const double DIV = 0.3;
}
#endif