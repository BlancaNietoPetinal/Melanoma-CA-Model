# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <cmath>
# include <ctime>
# include <cstring>

using namespace std;
# include "fem2D.h"
#include "../MyFun/MyFun.h"

#define D_COEF 1

int main ( void )
    {
    # define NNODES 6
    # define QUAD_NUM 3
    # define NX 5
    # define NY 5
    # define ELEMENT_NUM ( NX - 1 ) * ( NY - 1 ) * 2
    # define NODE_NUM ( 2 * NX - 1 ) * ( 2 * NY - 1 )

    double *a;
    double eh1;
    double el2;
    double element_area[ELEMENT_NUM];
    int element_node[NNODES*ELEMENT_NUM];
    double *f;
    int *T;
    int *H;
    int *D;
    int ib;
    int ierr;
    int job;
    int node;
    int *node_boundary;
    string node_eps_file_name = "Resultados/rectangle_nodes.eps";
    string node_txt_file_name = "Resultados/rectangle_nodes.txt";
    bool node_label;
    int node_show;
    double node_xy[2*NODE_NUM];
    int *pivot;
    double time;
    string time_file_name = "Resultados/rectangle_time.txt";
    double time_final;
    double time_init;
    int time_step;
    int time_step_num;
    double time_step_size;
    ofstream time_unit;
    int triangle_show;
    string triangulation_eps_file_name = "Resultados/rectangle_elements.eps";
    string triangulation_txt_file_name = "Resultados/rectangle_elements.txt";
    double *N;
    double *M;
    double *N0;
    string u_file_name = "Resultados/rectangle_u0000.txt";
    double *N_old;
    double wq[QUAD_NUM];
    double xl = 0.0;
    double xq[QUAD_NUM*ELEMENT_NUM];
    double xr = 1.0;
    double yb = 0.0;
    double yq[QUAD_NUM*ELEMENT_NUM];
    double yt = 1.0;

    timestamp ( );
    cout << "\n";
    cout << "FEM2D_HEAT_RECTANGLE\n";
    cout << "  NX =                 " << NX << "\n";
    cout << "  NY =                 " << NY << "\n";
    cout << "\n";
    cout << "  Number of nodes    = " << NODE_NUM << "\n";
    cout << "  Number of elements = " << ELEMENT_NUM << "\n";
    
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

    cout << "\n";
    cout << "  The matrix half bandwidth is " << ib << "\n";
    cout << "  The matrix row size is       " << 3 * ib + 1 << "\n";
    //
    //  Make an EPS picture of the nodes.
    if ( NX <= 10 && NY <= 10 )
    {
        node_label = true;
        nodes_plot ( node_eps_file_name, NODE_NUM, node_xy, node_label );
    }

    //  Write the nodes to an ASCII file that can be read into MATLAB.
    nodes_write ( NODE_NUM, node_xy, node_txt_file_name );

    //  Make a picture of the elements.
    if ( NX <= 10 && NY <= 10 )
    {
        node_show = 2;
        triangle_show = 2;

        triangulation_order6_plot ( triangulation_eps_file_name, NODE_NUM,
        node_xy, ELEMENT_NUM, element_node, node_show, triangle_show );

    }

    //  Write the elements to a file that can be read into MATLAB.
    element_write ( NNODES, ELEMENT_NUM, element_node,
        triangulation_txt_file_name );

    //  Set time stepping quantities.
    time_init = 0.0;
    time_final = 1.0;
    time_step_num = 5;
    time_step_size = ( time_final - time_init ) / ( double ) ( time_step_num );

    //  Allocate space.
    a = new double[(3*ib+1)*NODE_NUM];
    f = new double[NODE_NUM];
    T = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];
    M = new double[NODE_NUM];
    pivot = new int[NODE_NUM];
    N = new double[NODE_NUM];
    N0 = new double[NODE_NUM];
    N_old = new double[NODE_NUM];

    // Creamos T, D y H
    create_vec(NODE_NUM, T, 0);
    create_vec(NODE_NUM, D, 0);
    create_vec(NODE_NUM, H, 0);
    
    // iniciar con una celula tumoral en el centro
    T[int((2*NX-1)/2)*int((2*NY)/2)] = 1; 
    H[int((2*NX-1)/2)*int((2*NY)/2)] = 0;
    save_mat(NODE_NUM, T, "Resultados/Tumor.txt");
    //  Set the value of U at the initial time
    time = time_init;
    exact_u ( NX, NY, NODE_NUM, node_xy, time, N0);
    for ( node = 0; node < NODE_NUM; node++ )
    {
        N[node] = N0[node];
    }
    time_unit.open ( time_file_name.c_str ( ) );
    time_unit << "  " << setw(14) << time << "\n";

    solution_write ( NODE_NUM, N, u_file_name );

    //  Time looping.
    for ( time_step = 1; time_step <= time_step_num; time_step++ )
    {
        for ( node = 0; node < NODE_NUM; node++ )
        {
        N_old[node] = N[node];
        }
        delete [] N;
        time = ( ( double ) ( time_step_num - time_step ) * time_init
            + ( double ) (                 time_step ) * time_final )
            / ( double ) ( time_step_num             );
    
    //  Assemble the coefficient matrix A and the right-hand side F.
        assemble ( NODE_NUM, D_COEF, node_xy, NNODES,
        ELEMENT_NUM, element_node, QUAD_NUM,
        wq, xq, yq, element_area, ib, time, a, f, T, N_old ); // CALCULO DE A Y F

    //  Modify the coefficient matrix and right hand side to account for the dU/dt term
        adjust_backward_euler ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM,
        element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time,
        time_step_size, N_old, a, f );

    //  Modify the coefficient matrix and right hand side to account for
    //  boundary conditions.
        adjust_boundary ( NX, NY, NODE_NUM, node_xy, node_boundary, ib, time, a, f );

    //  Solve the linear system using a banded solver.
        ierr = dgb_fa ( NODE_NUM, ib, ib, a, pivot );
        job = 0;
        N = dgb_sl ( NODE_NUM, ib, ib, a, pivot, f, job );

    // El tumor evoluciona
        evolve(NODE_NUM, N, N, T, D, H);

    // guardamos las matrices
        //save_mat(NODE_NUM, T, "Resultados/Tumor.txt");
        save_mat(NODE_NUM, D, "Resultados/Necrosis.txt");

    //  Increment the file name, and write the new solution.
        time_unit << setw(14) << time << "\n";
        filename_inc ( &u_file_name );
        solution_write ( NODE_NUM, N, u_file_name );
    }

    //  Deallocate memory.
    delete [] a;
    delete [] f;
    delete [] node_boundary;
    delete [] pivot;
    delete [] N;
    delete [] N0;
    delete [] N_old;
    time_unit.close ( );

    //  Terminate.
    cout << "\n";
    cout << "FEM2D_HEAT_RECTANGLE:\n";
    cout << "  Normal end of execution.\n";
    return 0;
    # undef ELEMENT_NUM
    # undef NNODES
    # undef NODE_NUM
    # undef NX
    # undef NY
    # undef QUAD_NUM
}