#include <ctime>
#include <cmath>
#ifndef Program_constants_hpp
#define Program_constants_hpp
namespace constants {
  const int NNODES = 6;
  const int QUAD_NUM = 3;
  const int NX = 30;
  const int NY = 30;
  const int X_SIZE = 2 * NX - 1;
  const int Y_SIZE = 2 * NY - 1;
  const int GENERATION_IT = 20000;
  const int ELEMENT_NUM = ( NX - 1 ) * ( NY - 1 ) * 2;
  const int NODE_NUM = (2 * NX - 1) * (2 * NY - 1);
  const double L_N = 25; //F: 270 
  const double L_M = 10;
  //const double COEF_DIFF = 10;//1; // F: 10 cambiar??
  const double STARTING_NUTRIENTS = 1;
  const double ALPHA = 0.625; //F: 2.5
  const double NEC = 0;//0.01;
  const double MIG = 1000; //0.5;
  const double DIV = 0.3; //0.1

  // Modelizacion de melanomas
  const double MAX_PILED_CELL = 50;
  const int MUTATED_CELLS = 30;

  // tumor lysis consts
  const int DESTRUCTION_IT = 1000;
  const double LYS = 0.3;
  const double REC = 1;
  const double INC = 0.5;
  const double E_PERCENTAGE = 1; //percentage of E cells, E = E_PER*T_CELLS
  const int QUADRANT = 1;
}
#endif