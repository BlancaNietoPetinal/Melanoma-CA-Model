// To test whether the fem generates good solutions for N
# include <iostream>
# include <../FEM/fem2D.h>
# include "../constants.hpp"
# include "../MyFun/MyFun.h"
using namespace constants;

int main(){
    double *a;
    double eh1;
    double el2;
    double element_area[ELEMENT_NUM];
    int element_node[NNODES*ELEMENT_NUM];
    double *f;
    int *T;
    int *H;
    int *E;
    int *D;
    int ib;
    int ierr;
    int job;
    int node;
    int *node_boundary;
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
    string triangulation_txt_file_name = "Resultados/rectangle_elements.txt";
    double *N;
    double *M;
    double *N0;
    double *M0;
    double *N_old;
    double *M_old;
    double wq[QUAD_NUM];
    double xl = 0.0;
    double xq[QUAD_NUM*ELEMENT_NUM];
    double xr = 1.0;
    double yb = 0.0;
    double yq[QUAD_NUM*ELEMENT_NUM];
    double yt = 1.0;

    timestamp ( );
    // Setting up the matrices
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

    //  Set time stepping quantities.
    time_init = 0.0;
    time_final = 1.0;
    time_step_num = 10;
    time_step_size = ( time_final - time_init ) / ( double ) ( time_step_num );

    //  Allocate space.
    a = new double[(3*ib+1)*NODE_NUM];
    f = new double[NODE_NUM];
    T = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];
    E = new int[NODE_NUM];
    M = new double[NODE_NUM];
    pivot = new int[NODE_NUM];
    N = new double[NODE_NUM];
    N0 = new double[NODE_NUM];
    N_old = new double[NODE_NUM];
    M = new double[NODE_NUM];
    M0 = new double[NODE_NUM];
    M_old = new double[NODE_NUM];

    // Set T, D y H matrices
    create_vec(NODE_NUM, T, 0);
    create_vec(NODE_NUM, D, 0);
    create_vec(NODE_NUM, H, 0);
    create_vec(NODE_NUM, E, 0);
    
    // iniciar con una celula tumoral en el centro
    T[int((2*NX-1)/2)*int((2*NY)/2)] = 1; 
    H[int((2*NX-1)/2)*int((2*NY)/2)] = 0; 

    save_mat(NODE_NUM, T, "Resultados/T-0.txt");

    //  Set the value of U at the initial time
    time = time_init;
    initial_nutrients ( NX, NY, NODE_NUM, node_xy, time, N0);
    initial_nutrients ( NX, NY, NODE_NUM, node_xy, time, M0);

    for ( node = 0; node < NODE_NUM; node++ )
    {
        N[node] = N0[node];
        M[node] = M0[node];
    }
    time_unit.open ( time_file_name.c_str ( ) );
    time_unit << "  " << setw(14) << time << "\n";

    solution_write ( NODE_NUM, N, "Resultados/N-0.txt" );
    solution_write ( NODE_NUM, M, "Resultados/M-0.txt" );

    //  Time looping.
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

        // solve the equations for N and M
        fem(NODE_NUM,  QUAD_NUM, D_COEF, node_xy, NNODES, ELEMENT_NUM, element_node, 
            wq, xq, yq, element_area, ib, time, a, f, T, H, E, N_old, N, node_boundary,
            time_step_size, L_N);
        fem(NODE_NUM,  QUAD_NUM, D_COEF, node_xy, NNODES, ELEMENT_NUM, element_node, 
            wq, xq, yq, element_area, ib, time, a, f, T, H, E, M_old, M, node_boundary,
            time_step_size, L_M);

        // save the matrice
        solution_write ( NODE_NUM, N, "fem_resultados/N-"+std::to_string(time_step)+".txt");
    }
    //  Deallocate memory.
    delete [] a;
    delete [] f;
    delete [] node_boundary;
    delete [] pivot;
    delete [] N;
    delete [] N0;
    delete [] N_old;
    delete [] M;
    delete [] M0;
    delete [] M_old;
    time_unit.close ( );

    //  Terminate.
    std::cout << "\n";
    std::cout << "FEM2D_HEAT_RECTANGLE:\n";
    std::cout << "  Normal end of execution.\n";
    return 0;
}