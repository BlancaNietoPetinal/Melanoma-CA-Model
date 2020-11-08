
# include <cmath>
# include <ctime>
# include <cstdlib>
# include <cstring>
# include <fstream>
# include <iostream>
# include <iomanip>
# include <stdlib.h> //for malloc
# include "GeneratorLib/generatorlib.h"
# include "FEM/fem2D.h"
# include "constants.hpp"
# include "Tools/toolslib.h"

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
std::string folder = "Resultados/";
std::string node_txt_file_name = folder + "rectangle_nodes.txt";
std::string time_file_name = folder + "rectangle_time.txt";
std::string triangulation_txt_file_name = folder + "rectangle_elements.txt";
std::string N_nutrients_name = folder + "N/000.txt";
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

//****************************************************************************80
//
//  Purpose:
//
//    MAIN is the main program for FEM2D_HEAT_RECTANGLE.
//
//  Discussion:
//
//    FEM2D_HEAT_RECTANGLE solves
//
//      dUdT - Laplacian U(X,Y,T) = F(X,Y,T)
//
//    in a rectangular region in the plane.
//
//    Along the boundary of the region, Dirichlet conditions
//    are imposed:
//
//      U(X,Y,T) = G(X,Y,T)
//
//    At the initial time T_INIT, the value of U is given at all points
//    in the region:
//
//      U(X,Y,T) = H(X,Y,T)
//
//    The code uses continuous piecewise quadratic basis functions on
//    triangles determined by a uniform grid of NX by NY points.
//
//    The backward Euler approximation is used for the time derivatives.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    15 April 2006
//
//  Author:
//
//    C++ version by John Burkardt
//
//  Local parameters:
//
//    Local, double A[(3*IB+1)*NODE_NUM], the coefficient matrix.
//
//    Local, double EH1, the H1 seminorm error.
//
//    Local, double EL2, the L2 error.
//
//    Local, double ELEMENT_AREA[ELEMENT_NUM], the area of each element.
//
//    Local, int ELEMENT_NODE[ELEMENT_NUM*NNODES]; ELEMENT_NODE(I,J) is the
//    global node index of the local node J in element I.
//
//    Local, int ELEMENT_NUM, the number of elements.
//
//    Local, double F[NODE_NUM], the right hand side.
//
//    Local, int IB, the half-bandwidth of the matrix.
//
//    Local, integer NODE_BOUNDARY[NODE_NUM], is
//    0, if a node is an interior node;
//    1, if a node is a Dirichlet boundary node.
//
//    Local, int NNODES, the number of nodes used to form one element.
//
//    Local, double NODE_XY[2*NODE_NUM], the X and Y coordinates of nodes.
//
//    Local, int NX, the number of points in the X direction.
//
//    Local, int NY, the number of points in the Y direction.
//
//    Local, int QUAD_NUM, the number of quadrature points used for assembly.
//
//    Local, double TIME, the current time.
//
//    Local, double TIME_FINAL, the final time.
//
//    Local, double TIME_INIT, the initial time.
//
//    Local, double TIME_OLD, the time at the previous time step.
//
//    Local, int TIME_STEP_NUM, the number of time steps to take.
//
//    Local, double TIME_STEP_SIZE, the size of the time steps.
//
//    Local, double U[NODE_NUM], the finite element coefficients
//    defining the solution at the current time.
//
//    Local, double WQ[QUAD_NUM], quadrature weights.
//
//    Local, double XL, XR, YB, YT, the X coordinates of
//    the left and right sides of the rectangle, and the Y coordinates
//    of the bottom and top of the rectangle.
//
//    Local, double XQ[QUAD_NUM*ELEMENT_NUM], YQ[QUAD_NUM*ELEMENT_NUM], the X and Y
//    coordinates of the quadrature points in each element.
//
{
  double time;
  double time_final;
  double time_init;
  int time_step;
  int time_step_num;
  double time_step_size;
  std::ofstream time_unit;

  timestamp ( );

//  Set the coordinates of the nodes.
  xy_set ( NX, NY, NODE_NUM, xl, xr, yb, yt, node_xy );

//  Organize the nodes into a grid of 6-node triangles.
  grid_t6 ( NX, NY, NNODES, ELEMENT_NUM, element_node );

//  Set the quadrature rule for assembly.
  quad_a ( node_xy, element_node, ELEMENT_NUM, NODE_NUM,
    NNODES, wq, xq, yq );

//  Determine the areas of the elements.
  area_set ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
    element_node, element_area );

//  Determine which nodes are boundary nodes and which have a
//  finite element unknown.  Then set the boundary values.
  node_boundary = node_boundary_set ( NX, NY, NODE_NUM );

  if ( false )
  {
    i4vec_print_some ( NODE_NUM, node_boundary, 10, "  NODE_BOUNDARY:" );
  }

//  Determine the bandwidth of the coefficient matrix.
  ib = bandwidth ( NNODES, ELEMENT_NUM, element_node, NODE_NUM );

//  Write the nodes to an ASCII file that can be read into MATLAB.
  nodes_write ( NODE_NUM, node_xy, node_txt_file_name );

//  Write the elements to a file that can be read into MATLAB.
  element_write ( NNODES, ELEMENT_NUM, element_node,
    triangulation_txt_file_name );

//  Set time stepping quantities.
  time_init = 0.0;
  time_final = 0.5;
  time_step_num = ITERATIONS;
  time_step_size = ( time_final - time_init ) / ( double ) ( time_step_num );
//  Allocate space.

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

//  Set the value of U at the initial time.
  time = time_init;
  initial_nutrients ( NODE_NUM, node_xy, N_exact, NX, NY);
  initial_nutrients ( NODE_NUM, node_xy, M_exact, NX, NY);

  for ( node = 0; node < NODE_NUM; node++ )
  {
    N[node] = N_exact[node];
    M[node] = M_exact[node];
  }

  time_unit.open ( time_file_name.c_str ( ) );

  if ( !time_unit )
  {
    std::cout << "\n";
    std::cout << "FEM2D_HEAT_RECTANGLE- Warning!\n";
    std::cout << "  Could not write the time file \""
         << time_file_name << "\".\n";
    exit ( 1 );
  }

  time_unit << "  " << std::setw(14) << time << "\n";


//creamos T H y E
    create_vec(NODE_NUM, T, 0);
    create_vec(NODE_NUM, H, 1);
    create_vec(NODE_NUM, D, 0);

    T[int((2*NX -1)*(2*NY - 1)/2)] = 1;
    H[int((2*NX -1)*(2*NY - 1)/2)] = 0;

//  Time looping.
  solution_write ( NODE_NUM, N, N_nutrients_name );
  solution_write ( NODE_NUM, M, M_nutrients_name );
  save_mat(NODE_NUM, T, T_filename);
  
  
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

//  Assemble the coefficient matrix A and the right-hand side F of the
//  finite element equations.
    assemble ( NODE_NUM, node_xy, NNODES,
      ELEMENT_NUM, element_node, QUAD_NUM,
      wq, xq, yq, element_area, ib, time, a_N, f_N, N_old, T, H, L_N, ALPHA );
    assemble ( NODE_NUM, node_xy, NNODES,
      ELEMENT_NUM, element_node, QUAD_NUM,
      wq, xq, yq, element_area, ib, time, a_M, f_M, M_old, T, H, L_M, ALPHA );
    if ( false )
    {
      dgb_print_some ( NODE_NUM, NODE_NUM, ib, ib, a_N, 10, 1, 12, 25,
        "  Initial block of coefficient matrix A:" );

      r8vec_print_some ( NODE_NUM, f_N, 1, 10,
        "  Part of the right hand side F:" );
    }

//  Modify the coefficient matrix and right hand side to account for the dU/dt
//  term, which we are treating using the backward Euler formula.
    adjust_backward_euler ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
      element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time,
      time_step_size, N_old, a_N, f_N );
    adjust_backward_euler ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
      element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time,
      time_step_size, M_old, a_M, f_M );

    if ( false )
    {
      dgb_print_some ( NODE_NUM, NODE_NUM, ib, ib, a_N, 10, 1, 12, 25,
        "  A after DT adjustment:" );

      r8vec_print_some ( NODE_NUM, f_N, 1, 10,
        "  F after DT adjustment:" );
    }

//  Modify the coefficient matrix and right hand side to account for
//  boundary conditions.
    adjust_boundary ( NODE_NUM, node_xy, node_boundary, ib, time, a_N, f_N, NX, NY );
    adjust_boundary ( NODE_NUM, node_xy, node_boundary, ib, time, a_M, f_M, NX, NY );

    if ( false )
    {
      dgb_print_some ( NODE_NUM, NODE_NUM, ib, ib, a_N, 10, 1, 12, 25,
        "  A after BC adjustment:" );

      r8vec_print_some ( NODE_NUM, f_N, 1, 10,
        "  F after BC adjustment:" );
    }

//  Solve the linear system using a banded solver.
    ierr_N = dgb_fa ( NODE_NUM, ib, ib, a_N, pivot_N );
    ierr_M = dgb_fa ( NODE_NUM, ib, ib, a_M, pivot_M );

    if ( (ierr_N != 0) && (ierr_M != 0))
    {
      std::cout << "\n";
      std::cout << "FEM2D_HEAT_RECTANGLE - Error!\n";
      std::cout << "  DGB_FA returned an error condition.\n";
      std::cout << "\n";
      std::cout << "  The linear system was not factored, and the\n";
      std::cout << "  algorithm cannot proceed.\n";
      exit ( 1 );
    }

    job = 0;
    N = dgb_sl ( NODE_NUM, ib, ib, a_N, pivot_N, f_N, 0 );
    M = dgb_sl ( NODE_NUM, ib, ib, a_M, pivot_M, f_M, 0 );
    if ( false )
    {
      r8vec_print_some ( NODE_NUM, N, 1, 10,
        "  Part of the solution vector:" );
    }

// El tumor evoluciona
    grow(M, N, T, D, H, 2*NX-1, 2*NY-1);
    
//  Increment the file name, and write the new solution.
    time_unit << std::setw(14) << time << "\n";

    filename_inc ( &N_nutrients_name );
    filename_inc ( &M_nutrients_name );
    filename_inc ( &T_filename );
    filename_inc ( &D_filename );
    filename_inc ( &H_filename );
  
  if(time_step%10==0){
    solution_write(NODE_NUM, N, N_nutrients_name);
    save_mat(NODE_NUM, T, T_filename);
    save_mat(NODE_NUM, H, H_filename);
    save_mat(NODE_NUM, D, D_filename);
  }
  if(is_tumor_in_border(T,2*NX - 1,2*NY - 1)){
    break;
  }
  }

//
//  Deallocate memory.
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
//
//  Terminate.
//
  std::cout << "\n";
  std::cout << "FEM2D_HEAT_RECTANGLE:\n";
  std::cout << "  Normal end of execution.\n";

  std::cout << "\n";
  timestamp ( );

  return 0;
}
