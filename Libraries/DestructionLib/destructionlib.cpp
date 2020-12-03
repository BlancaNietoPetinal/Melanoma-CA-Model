#include "destructionlib.h"
//#include "../Tools/toolslib.h"
#include <array>


void get_tumor_limits(double * mat, int xsize, int ysize, int &left, int &right, int &sup, int &inf){
    left = leftBorder(mat, xsize*ysize);
    right = rightBorder(mat, xsize*ysize);
    sup = superiorBorder(mat, xsize, ysize);
    inf = inferiorBorder(mat, xsize, ysize);
}

int leftBorder(double * mat, int size){
    int node = 0;
    while(mat[node]==0){
        node++;
    }
    return node;
};
int rightBorder(double * mat, int size){
    int lastNode;
    for(int node = 0; node<size ; node++){
        if(mat[node] != 0){
            lastNode = node;
        }
    }
    return lastNode;
};
int superiorBorder(double * mat, int xsize, int ysize){
    int xcoordinate=0, ycoordinate=ysize, aux, node = 0, y,result;
    for(int x = 0; x<xsize; x++){
        aux = 0;
        y = 0;
        while((y<ysize)){
            if( (mat[node]!=0) && (ycoordinate>y) && (aux==0) ){
                xcoordinate = x;
                ycoordinate = y;
                aux = 1;
                result = node;
            }
            y++;
            node++;
            
        }
    }
    return result;
};
int inferiorBorder(double * mat, int xsize, int ysize){
    int xcoordinate=0, ycoordinate=0, aux, node = 0, y,result;
    for(int x = 0; x<xsize; x++){
        aux = 0;
        y = 0;
        while((y<ysize)){
            if( (mat[node]!=0) && (ycoordinate<y) && (aux==0) ){
                xcoordinate = x;
                ycoordinate = y;
                aux = 1;
                result = node;
            }
            y++;
            node++;
            
        }
    }
    return result;
}
double * effectorCellPlacement(int leftnode, int rightnode, int supnode, int infnode, int xsize, int ysize, double *T){
    double * mat;
    int xleft, xright, ysup, yinf, _;
    mat = new double[xsize*ysize];

    node_to_coordinates(leftnode, xleft, _, xsize, ysize);
    node_to_coordinates(rightnode, xright, _, xsize, ysize);
    node_to_coordinates(supnode, _, ysup, xsize, ysize);
    node_to_coordinates(infnode, _, yinf, xsize, ysize);
    mat = get_squeare(xleft, xright, ysup, yinf, xsize, ysize);

    match_matrices(T, mat, xsize, ysize);
    return mat;
};
double * get_squeare(int xleft, int xright, int ysup, int yinf, int xsize, int ysize){
    int node = 0;
    double * mat;
    mat = new double[xsize*ysize];
    for(int x = 0; x<xsize; x++){
        for(int y = 0; y<ysize; y++){
            if( ((x>=(xleft-1)) && (y>=(ysup-1))) && ((x<=(xright+1)) && (y<=(yinf+2))) ){
                mat[node] = 1;
            }
            else{
                mat[node] = 0;
            }
            node++;
        }
    }
    return mat;
};
void match_matrices(double *T,double *mat, int xsize, int ysize){
    int totalsize = xsize*ysize;
    for(int node = 0; node<totalsize; node++){
        if(T[node]!=0){
            mat[node] = 0;
        }
    }
};

void tumor_lysis(double T[], double E[], int Ecount[], double D[], double H[], int xsize, int ysize){
    int var;
    std::seed_seq seed{static_cast<long long>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
                        static_cast<long long>(reinterpret_cast<intptr_t>(&var))};
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> dice_distribution(1,2);
    std::vector<int> Tneighbours;
    int dice, node = 0;
    for(int x = 0; x < xsize; x++)
    {
        for(int y = 0; y < ysize; y++)
        {
            //if(E[node]==1){
            if(E[node]>=0){
                Tneighbours = get_specific_neighbours(T, node, 1, 0,'>', xsize, ysize);
                
                if(Tneighbours.size()!=0){
                    lysis(T, E, Ecount, D, H, node, xsize, ysize, generator);
                }
                else{
                    dice = dice_distribution(generator);
                    switch (dice)
                    {
                    case 1:
                        inactivation(T, E, Ecount, H, node, xsize, ysize, generator);
                        break;
                    
                    case 2:
                        Emigration(T, E, Ecount, H, D, node, xsize, ysize, generator);
                        break;
                    }
                }
                
            }
            //else if(T[node]!=1){
            else if(T[node]!=1){
                recruitment(T, E, D, H, node, xsize, ysize, generator);
            }
            node++;
        }
    }
};

void lysis(double T[], double E[], int Ecount[], double D[], double H[], int node, int xsize, int ysize, std::mt19937 generator){
    std::vector<int> Eneighbours, Tneighbours, Hneighbours;
    std::normal_distribution<double> distribution(0,1);
    std::uniform_int_distribution<> u_distrib(1,50);
    int neignode, index;
    double rnd_n = distribution(generator), P;
    
    Eneighbours = get_specific_neighbours(E, node, NEIGBOUR_NUMBER1, 0, '>', xsize, ysize);
    P = 1-exp(-pow(Eneighbours.size()/LYS,2));
    if(P>fabs(rnd_n)){
        Tneighbours = get_specific_neighbours(T, node, 1, 0, '>', xsize, ysize);
        index = u_distrib(generator) % Tneighbours.size();
        neignode = Tneighbours[index];
        T[neignode]--; D[neignode]++; Ecount[node]++;

        Hneighbours = get_specific_neighbours(H, node, 1, 0, '>', xsize, ysize);
        for(int j = 0; j<Hneighbours.size(); j++){
            recruitment(T, E, D, H, Hneighbours[j], xsize, ysize, generator);
        }

        if(Ecount[node] == 3){
            E[node] = 0; H[node] = 1; Ecount[node] = 0;
        }
    }
};
void recruitment(double T[], double E[], double D[], double H[], int node, int xsize, int ysize, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,1);
    std::uniform_int_distribution<> u_distrib(1,50);
    std::vector<int> Tneighbours, Hneighbours;
    int index, neignode;
    double rnd_n = distribution(generator), P;
    
    Tneighbours = get_specific_neighbours(T, node, NEIGBOUR_NUMBER1, 0, '>', xsize, ysize);
    P = exp(-pow(1/(summation(T, Tneighbours)*REC),2));

    //Hneighbours = get_specific_neighbours(H, node, 1, 1, '=', xsize, ysize);
    Hneighbours = get_specific_neighbours(H, node, 1, 0, '>', xsize, ysize);
    if(P>fabs(rnd_n) && (Hneighbours.size()>0)){
        index = u_distrib(generator) % Hneighbours.size();
        neignode = Hneighbours[index];
        D[neignode] = 0; H[neignode] = 0; E[neignode] = 1;
    }
};
void inactivation(double T[], double E[], int Ecount[], double H[], int node, int xsize, int ysize, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,1); 
    std::vector<int> Tneighbours;
    double rnd_n = distribution(generator), P;
    Tneighbours = get_specific_neighbours(T, node, NEIGBOUR_NUMBER3, 0, '>', xsize, ysize);
    P = 1 - exp(- pow(1/(summation(T, Tneighbours)*INC),2));
    if(P>fabs(rnd_n)){
        E[node] = 0; Ecount[node] = 0;
        H[node] = 1;
    }
};
int summation(double mat[], std::vector<int> neighbours){
    int node, result = 0;
    for(int i; i<neighbours.size(); i++){
        node = neighbours[i];
        result += mat[node];
    }
    return result;
};
void Emigration(double T[], double E[], int Ecount[], double H[], double D[], int node, int xsize, int ysize, std::mt19937 generator){
    std::uniform_int_distribution<int> u_distrib(1,50);
    std::vector<int> neighbours;
    int index, neignode, temp;
    neighbours = get_neighbours(E, node, 1, xsize, ysize);
    index = u_distrib(generator) % neighbours.size();
    neignode = neighbours[index];
    /*if(E[neignode] == 1){
                temp = Ecount[neignode];
        Ecount[neignode] = Ecount[node];
        Ecount[node] = temp;

        temp = E[neignode];
        E[neignode] = E[node]; 
        E[node] = temp;

    else if(H[neignode] == 1){
        std::cout<<"Migracion: "<<std::endl
        E[neignode] = 1; Ecount[neignode] = Ecount[node]; H[neignode] = 0;
        E[node] = 0; Ecount[node] = 0; H[node] = 1;
    }
    */
    if(E[neignode] != 0){
        temp = Ecount[neignode];
        Ecount[neignode] = Ecount[node];
        Ecount[node] = temp;

        temp = E[neignode];
        E[neignode] = E[node]; 
        E[node] = temp;
    }

    else if(H[neignode] != 0){
        E[neignode] = E[node]; E[node] = 0;
        Ecount[neignode] = Ecount[node]; Ecount[node] = 0; 
        H[node] = H[neignode]; H[neignode] = 0;
        
    }
};

bool noTumorCells(double T[], int nnode){
    bool result = true;
    for(int node=0; node<nnode; node++){
        if(T[node]!=0){
            result = false;
            break;
        }
    }
    return result;
}