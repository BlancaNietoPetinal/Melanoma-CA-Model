#include <ctime>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  constexpr int NNODES = 6;
  constexpr int QUAD_NUM = 3;
  constexpr int NX = 20;
  constexpr int NY = 20;
  constexpr int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  constexpr int NODE_NUM = ( 2 * NX - 1 ) * ( 2 * NY - 1 );
  constexpr double DIFFUSION = 1;
  constexpr double L_N  = 100;
  constexpr double L_M  = 2; //buscar el valor
  constexpr double K  = 2; //buscar el valor
  constexpr float ThNec  = 0.1;
  constexpr float ThMig = 0;
  constexpr float ThDiv = 1.0;
}
#endif