#include <ctime>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  constexpr int NNODES = 6;
  constexpr int QUAD_NUM = 3;
  constexpr int NX = 10;
  constexpr int NY = 10;
  constexpr int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  constexpr int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  constexpr double DIFF = 1;
  constexpr double L_N  = 20;
  constexpr double L_M  = 2; //buscar el valor
  constexpr double K  = 2; //buscar el valor
}
#endif