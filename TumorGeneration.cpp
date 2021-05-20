
# include <cmath>
# include <ctime>
# include <cstdlib>
# include <cstring>
# include <fstream>
# include <iostream>
# include <iomanip>
//# include <stdlib.h> //malloc
# include "constants.hpp"
# include "Libraries/GeneratorLib/generatorlib.h"
# include "Libraries/FEM/fem2D.h"
# include "Libraries/Tools/toolslib.h"

using namespace constants;
double *a_N;
double *a_M;
double *f_N;
double *f_M;
double *N;
double *M;
double *N_exact;
double *M_exact;
double *N_old;
double *M_old;
int *pivot_N;
int *pivot_M;
int *T;
int *D;
int *H;
float *DIV_mat;
double eh1;
double el2;
double element_area[ELEMENT_NUM];
int element_node[NNODES*ELEMENT_NUM];
int ib;
int ierr_N;
int ierr_M;
int job;
int node;
bool node_label;
int node_show;
double node_xy[2*NODE_NUM];
std::string folder = "Results/DELETE/";
std::string node_txt_file_name = folder + "rectangle_nodes.txt";
std::string time_file_name = folder + "rectangle_time.txt";
std::string triangulation_txt_file_name = folder + "rectangle_elements.txt";
std::string N_nutrients_name = folder + "N/000.txt";
std::string DIV_filename = folder + "DIV/000.txt";
std::string M_nutrients_name = folder + "M/000.txt";
std::string T_filename = folder + "T/000.txt";
std::string D_filename = folder + "D/000.txt";
std::string H_filename = folder + "H/000.txt";
int triangle_show;
int *node_boundary=(int *) malloc(sizeof(int)*NODE_NUM);
double wq[QUAD_NUM];
double xl = 0.0;
double xq[QUAD_NUM*ELEMENT_NUM];
double xr = 1.0;
double yb = 0.0;
double yq[QUAD_NUM*ELEMENT_NUM];
double yt = 1.0;

int main ( void )
{
  double time;
  double time_final;
  double time_init;
  int time_step;
  int time_step_num;
  double time_step_size;
  std::ofstream time_unit;
  
  timestamp ( );

  // coordenadas de los nodos
  xy_set ( NX, NY, NODE_NUM, xl, xr, yb, yt, node_xy );
  grid_t6 ( NX, NY, NNODES, ELEMENT_NUM, element_node );
  quad_a ( node_xy, element_node, ELEMENT_NUM, NODE_NUM,
    NNODES, wq, xq, yq );
  area_set ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
    element_node, element_area );
  node_boundary = node_boundary_set ( NX, NY, NODE_NUM );
  ib = bandwidth ( NNODES, ELEMENT_NUM, element_node, NODE_NUM );
  nodes_write ( NODE_NUM, node_xy, node_txt_file_name );
  element_write ( NNODES, ELEMENT_NUM, element_node,
    triangulation_txt_file_name );

  // tiempos
  time_init = 0.0;
  time_final = 0.5;
  time_step_num = GENERATION_IT;
  time_step_size = ( time_final - time_init ) / ( double ) ( time_step_num );

  // asignacion de memoria
  a_N = new double[(3*ib+1)*NODE_NUM];
  a_M = new double[(3*ib+1)*NODE_NUM];
  f_N = new double[NODE_NUM];
  f_M = new double[NODE_NUM];
  pivot_N = new int[NODE_NUM];
  pivot_M = new int[NODE_NUM];
  N = new double[NODE_NUM];
  N_exact = new double[NODE_NUM];
  N_old = new double[NODE_NUM];
  M = new double[NODE_NUM];
  M_exact = new double[NODE_NUM];
  M_old = new double[NODE_NUM];
  T = new int[NODE_NUM];
  D = new int[NODE_NUM];
  H = new int[NODE_NUM];
  DIV_mat = new float[NODE_NUM];


  time = time_init;
  //stain_generator();
  //save_theta_DIV();
  // creamos matrices de nutrientes
  initial_nutrients ( NODE_NUM, node_xy, N_exact, NX, NY);
  initial_nutrients ( NODE_NUM, node_xy, M_exact, NX, NY);
  for ( node = 0; node < NODE_NUM; node++ )
  {
    N[node] = N_exact[node];
    M[node] = M_exact[node];
  }

  time_unit.open ( time_file_name.c_str ( ) );

  time_unit << "  " << std::setw(14) << time << "\n"; //se puede quitar?

  // creamos T H y D
  create_vec(NODE_NUM, DIV_mat, DIV);
  create_vec(NODE_NUM, T, 0);
  create_vec(NODE_NUM, H, 1);
  create_vec(NODE_NUM, D, 0);

  // posicionamos una celula T
  T[int((2*NX -1)*(2*NY - 1)/2)] = 1;
  H[int((2*NX -1)*(2*NY - 1)/2)] = 0;

  solution_write ( NODE_NUM, N, N_nutrients_name );
  solution_write ( NODE_NUM, M, M_nutrients_name );
  save_mat(NODE_NUM, T, T_filename);
  
  // comienzo del periodo de crecimiento
  for ( time_step = 1; time_step <= time_step_num; time_step++ )
  {
    for ( node = 0; node < NODE_NUM; node++ )
    {
      N_old[node] = N[node];
      M_old[node] = M[node];
    }
    delete [] N;
    delete [] M;

    time = ( ( double ) ( time_step_num - time_step ) * time_init
           + ( double ) (                 time_step ) * time_final )
           / ( double ) ( time_step_num             );

    // ensamblamos la matriz de coeficientes A y el lado dcho F
    assemble ( NODE_NUM, node_xy, NNODES,
      ELEMENT_NUM, element_node, QUAD_NUM,
      wq, xq, yq, element_area, ib, time, a_N, f_N, N_old, T, H, L_N, ALPHA );
    assemble ( NODE_NUM, node_xy, NNODES,
      ELEMENT_NUM, element_node, QUAD_NUM,
      wq, xq, yq, element_area, ib, time, a_M, f_M, M_old, T, H, L_M, ALPHA );

    // Modificamos A y F para conseguir dN/dt o dM/dt
    adjust_backward_euler ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
      element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time,
      time_step_size, N_old, a_N, f_N );
    adjust_backward_euler ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
      element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time,
      time_step_size, M_old, a_M, f_M );

    // Modificamos A y F para las condiciones de contorno
    adjust_boundary ( NODE_NUM, node_xy, node_boundary, ib, time, a_N, f_N, NX, NY );
    adjust_boundary ( NODE_NUM, node_xy, node_boundary, ib, time, a_M, f_M, NX, NY );

    // Resolvemos el sistema
    ierr_N = dgb_fa ( NODE_NUM, ib, ib, a_N, pivot_N );
    ierr_M = dgb_fa ( NODE_NUM, ib, ib, a_M, pivot_M );
    N = dgb_sl ( NODE_NUM, ib, ib, a_N, pivot_N, f_N, 0 );
    M = dgb_sl ( NODE_NUM, ib, ib, a_M, pivot_M, f_M, 0 );

    // El tumor evoluciona
    std::cout<<"ITERACION: "<<time_step<<std::endl;
    grow(M, N, T, D, H, DIV_mat, 2*NX-1, 2*NY-1);
    
    //  Incremento del filename y guardar la solucion
    time_unit << std::setw(14) << time << "\n"; //se puede quitar??
    filename_inc ( &N_nutrients_name );
    filename_inc ( &M_nutrients_name );
    filename_inc ( &DIV_filename );
    filename_inc ( &T_filename );
    filename_inc ( &D_filename );
    filename_inc ( &H_filename );

    if(time_step%5==0){
      solution_write(NODE_NUM, N, N_nutrients_name);
      save_mat(NODE_NUM, DIV_mat, DIV_filename);
      //solution_write(NODE_NUM, M, M_nutrients_name);
      save_mat(NODE_NUM, T, T_filename);
      save_mat(NODE_NUM, H, H_filename);
      //save_mat(NODE_NUM, D, D_filename);
    }
  
    if(metastasis(T, 2*NX - 1, 2*NY - 1)){
      break;
    }
  }

  // Liberamos memoria
  delete [] a_N;
  delete [] a_M;
  delete [] f_N;
  delete [] f_M;
  delete [] node_boundary;
  delete [] pivot_N;
  delete [] pivot_M;
  delete [] N;
  delete [] N_exact;
  delete [] N_old;
  delete [] M;
  delete [] M_exact;
  delete [] M_old;
  delete [] T;
  delete [] H;
  delete [] D;

  time_unit.close ( );
  std::cout << "\nTerminado\n";
  timestamp ( );

  return 0;
}
