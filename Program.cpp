#include <iostream>
#include <array>
#include <fstream>
#include "FEM/fem2D.h"
#include "MyFun/MyFun.h"

# define NNODES 6
# define QUAD_NUM 3
# define NODE_NUM ( 2 * NX - 1 ) * ( 2 * NY - 1 )
# define ELEMENT_NUM ( NX - 1 ) * ( NY - 1 ) * 2

// TODO: display with gnuplot? o Qt?


int main(){

    std::array<std::array<Pixel*,NX>,NY> Tmat, Emat, Hmat;
    Pixel p1('T'), p2('H');
    Grid g; //creamos el grid de pixeles
    
    g.addPixel(1,1,p1); // introducimos un valor
    Tmat = g.getMatrix('T'); // obtenemos las matrices de las celulas
    Emat = g.getMatrix('E'); 
    Hmat =  g.getMatrix('H');

    std::cout<<"(1,1) = "<<Tmat[1][1]->getType()<<std::endl;
    std::cout<<"(1,2) = "<<Tmat[1][2]->getType()<<std::endl;

    int *node_boundary;
    int *pivot;
    int ib;
    int ierr;
    int job;
    int time_step;
    int time_step_num;
    int element_node[NNODES*ELEMENT_NUM];
    double *a;
    double *f;
    double *u;
    double *u_exact;
    double *u_old;
    double time_final;
    double time_init;
    double time;
    double time_step_size;
    double element_area[ELEMENT_NUM];
    double xq[QUAD_NUM*ELEMENT_NUM], yq[QUAD_NUM*ELEMENT_NUM], wq[QUAD_NUM];
    double xr = 3.0, xl = 0.0, yt = 1.0, yb = 0.0, node_xy[2*NODE_NUM];
    string node_txt_file_name = "Resultados/rectangle_nodes.txt";
    string time_file_name = "Resultados/rectangle_time.txt";
    string triangulation_txt_file_name = "Resultados/rectangle_elements.txt";
    string u_file_name = "Resultados/rectangle_u0000.txt";
    ofstream time_unit;

    //Ecuaciones diferenciales de los nutrientes
    xy_set ( NX, NY, NODE_NUM, xl, xr, yb, yt, node_xy ); //  Set the coordinates of the nodes.
    grid_t6 ( NX, NY, NNODES, ELEMENT_NUM, element_node ); //  Organize the nodes into a grid of 6-node triangles.
    quad_a ( node_xy, element_node, ELEMENT_NUM, NODE_NUM, NNODES, wq, xq, yq ); //  Set the quadrature rule for assembly.
    area_set ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM, element_node, element_area ); //  Determine the areas of the elements.
    node_boundary = node_boundary_set ( NX, NY, NODE_NUM ); //  Determine which nodes are boundary nodes and which have a finite element unknown.  Then set the boundary values.
    
    i4vec_print_some ( NODE_NUM, node_boundary, 35, "  NODE_BOUNDARY:" );
    
    ib = bandwidth ( NNODES, ELEMENT_NUM, element_node, NODE_NUM );
    nodes_write ( NODE_NUM, node_xy, node_txt_file_name ); //  Write the nodes to an ASCII file that can be read into MATLAB.
    element_write ( NNODES, ELEMENT_NUM, element_node, triangulation_txt_file_name ); //  Write the elements to a file that can be read into MATLAB.
    
    //  Set time stepping quantities.
    time_init = 0.0;
    time_final = 0.5;
    time_step_num = 10;
    time_step_size = ( time_final - time_init ) / ( double ) ( time_step_num );

    //  Allocate space.
    a = new double[(3*ib+1)*NODE_NUM];
    f = new double[NODE_NUM];
    pivot = new int[NODE_NUM];
    u = new double[NODE_NUM];
    u_exact = new double[NODE_NUM];
    u_old = new double[NODE_NUM];

    //  Set the value of U at the initial time.
    time = time_init;
    exact_u ( NODE_NUM, node_xy, time, u_exact); // EMPEZAR A MODIFICAR POR AQUI
    for ( int node = 0; node < NODE_NUM; node++ )
        {
            u[node] = u_exact[node];
        }
    time_unit.open ( time_file_name.c_str ( ) );

    for ( time_step = 1; time_step <= time_step_num; time_step++ )
    {
        for ( int node = 0; node < NODE_NUM; node++ )
        {
        u_old[node] = u[node];
        }
        delete [] u;

        time = ( ( double ) ( time_step_num - time_step ) * time_init
            + ( double ) ( time_step ) * time_final )
            / ( double ) ( time_step_num );

    //  Assemble the coefficient matrix A and the right-hand side F of the
    //  finite element equations.
        assemble ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM, element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time, a, f );

    //  Modify the coefficient matrix and right hand side to account for the dU/dt
    //  term, which we are treating using the backward Euler formula.
        adjust_backward_euler ( NODE_NUM, node_xy, NNODES, ELEMENT_NUM, element_node, QUAD_NUM, wq, xq, yq, element_area, ib, time, time_step_size, u_old, a, f );

    //  Modify the coefficient matrix and right hand side to account for
    //  boundary conditions.
        adjust_boundary ( NODE_NUM, node_xy, node_boundary, ib, time, a, f );

    //  Solve the linear system using a banded solver.
        ierr = dgb_fa ( NODE_NUM, ib, ib, a, pivot );

        job = 0;
        u = dgb_sl ( NODE_NUM, ib, ib, a, pivot, f, job );

    //  Increment the file name, and write the new solution.
        time_unit << setw(14) << time << "\n";

        filename_inc ( &u_file_name );

        
        solution_write ( NODE_NUM, u, u_file_name, node_boundary);
    }
    return 0;
};
