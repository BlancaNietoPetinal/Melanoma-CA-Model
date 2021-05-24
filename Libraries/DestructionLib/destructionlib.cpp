#include "destructionlib.h"

void tumor_lysis(double T[], double E[], int Ecount[], double D[], double H[]){
    int var;
    std::seed_seq seed{static_cast<long long>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
                        static_cast<long long>(reinterpret_cast<intptr_t>(&var))};
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> dice_distribution(1,2);
    std::vector<int> Tneighbours;
    int dice, node = 0;
    for(int node = 0; node < NODE_NUM; node++){
        if(E[node]!=0){
            Tneighbours = get_specific_neighbours(T, node, 0,'>');
            if(Tneighbours.size()!=0){
                lysis(T, E, Ecount, D, H, node, generator);
            }
            else{
                dice = dice_distribution(generator);
                switch (dice)
                {
                case 1:
                    inactivation(T, E, Ecount, H, node, generator);
                    break;
                
                case 2:
                    Emigration(T, E, Ecount, H, D, node, generator);
                    break;
                }
            }
            
        }
    }
};

void lysis(double T[], double E[], int Ecount[], double D[], double H[], int node, std::mt19937 generator){
    std::vector<int> Eneighbours, Tneighbours, Hneighbours, Dneighbours;
    std::normal_distribution<double> distribution(0,0.7);
    std::uniform_int_distribution<> u_distrib(1,50);
    int neignode, index;
    double rnd_n = distribution(generator), P;
    Eneighbours = get_specific_neighbours(E, node, 0, '>');
    P = 1-exp(-pow(Eneighbours.size()/LYS,2));// PROBAR A PONER A 1x
    if(P>fabs(rnd_n)){
        Tneighbours = get_specific_neighbours(T, node, 0, '>');
        index = u_distrib(generator) % Tneighbours.size();
        neignode = Tneighbours[index];
        T[neignode]--; D[neignode]++; Ecount[node]++;

        recruitment(T, E, D, H, node, generator);

        if(Ecount[node] == 3){
            E[node] = 0; H[node] = 1; Ecount[node] = 0;
        }
    }
};
void recruitment(double T[], double E[], double D[], double H[], int node, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,0.5);
    std::uniform_int_distribution<> u_distrib(1,50);
    std::vector<int> Tneighbours, Hneighbours, Dneighbours;
    int index, neignode;
    double rnd_n = distribution(generator), P;
    Tneighbours = get_specific_neighbours(T, node, 0, '>');
    P = exp(-1/pow((summation(T, Tneighbours)*REC),2));

    Hneighbours = get_specific_neighbours(H, node, 0, '>');
    Dneighbours = get_specific_neighbours(D, node, 0, '>');
    std::vector<int> HDneighbours = Hneighbours; // set union of both vectors
    HDneighbours.insert(HDneighbours.end(), Dneighbours.begin(), Dneighbours.end());
    for(int j = 0; j<HDneighbours.size(); j++){
        rnd_n = distribution(generator);
        if(P>fabs(rnd_n)){
        index = u_distrib(generator) % HDneighbours.size();
        neignode = HDneighbours[index];
        if(T[neignode] == 0){
            D[neignode] = 0; H[neignode] = 0; E[neignode] = 1;
            HDneighbours.erase(HDneighbours.begin()+index);
            }   
        }
    }
    //}
};
void inactivation(double T[], double E[], int Ecount[], double H[], int node, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,1); 
    std::vector<int> Tneighbours;
    double rnd_n = distribution(generator), P;
    Tneighbours = get_specific_neighbours(T, node, 0, '>');
    P = 1 - exp(- pow(1/(summation(T, Tneighbours)*INC),2));
    if(P>fabs(rnd_n)){
        E[node] = 0; Ecount[node] = 0;
        H[node] = 1;
    }
};
//REVISAR RECRUITMENT
int summation(double mat[], std::vector<int> neighbours){
    int node, result = 0;
    for(int i; i<neighbours.size(); i++){
        node = neighbours[i];
        result += mat[node];
    }
    return result;
};
void Emigration(double T[], double E[], int Ecount[], double H[], double D[], int node, std::mt19937 generator){
    std::uniform_int_distribution<int> u_distrib(1,8);
    std::vector<int> neighbours;
    int index, neignode, temp;

    neighbours = get_neighbours(E, node);
    index = u_distrib(generator) % neighbours.size();
    neignode = neighbours[index];

    if(E[neignode] != 0){
        temp = Ecount[neignode];
        Ecount[neignode] = Ecount[node];
        Ecount[node] = temp;

        temp = E[neignode];
        E[neignode] = E[node]; 
        E[node] = temp;
    }

    else if( (H[neignode] == 1 ) ){
        E[neignode] = E[node]; E[node] = 0;
        Ecount[neignode] = Ecount[node]; Ecount[node] = 0; 
        H[node] = H[neignode]; H[neignode] = 0;
    }

    else if(((D[neignode] > 0) & (T[neignode] == 0))){
        E[neignode] = E[node];
        Ecount[neignode] = Ecount[node]; Ecount[node] = 0;
        D[neignode] = 0;
    }
};

bool no_cells(double mat[]){
    bool result = true;
    for(int node=0; node<NODE_NUM; node++){
        if(mat[node]!=0){
            result = false;
            break;
        }
    }
    return result;
}

void random_place_cell(double * mat, int n_cells_to_place){
    int var;
    int n, node;
    n = cell_counter(mat) - n_cells_to_place;
    std::seed_seq seed{static_cast<long long>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
                        static_cast<long long>(reinterpret_cast<intptr_t>(&var))};
    std::mt19937 generator(seed);
    while(n>0){
        std::uniform_int_distribution<int> dice_distribution(0,X_SIZE*Y_SIZE);
        node = dice_distribution(generator);
        if(mat[node]==1){
            mat[node]=0;
            n--;
        }
    }
}

void effectorCellPlacement(double T[], double E[]){
    std::vector<int> Tneighbours, Eneighbours;
    int ECells;

    ECells = E_PERCENTAGE*cell_counter(T);
    sector(E, T, QUADRANT);
    while(ECells > 0){
        int allocated = 0;
        for(int node = 0; node<NODE_NUM; node++){
            if(E[node] == -1){
                Tneighbours = get_specific_neighbours(T, node, 0, '>');
                if( (!Tneighbours.empty()) ){
                    E[node] = 1;
                    ECells--;
                    allocated++;
                }
                else{
                    Eneighbours =  get_specific_neighbours(E, node, 0, '>'); 
                    if(Eneighbours.size()>2){
                        E[node] = 1;
                        ECells--;
                        allocated++;
                        node++; // asi no se forma mal
                    }
                }
            }
        }
        if(allocated == 0){
            ECells = 0;
        };
    }
    for(int node = 0; node<NODE_NUM; node++){
        if(E[node]==-1){
            E[node] = 0;
        }
    }

    //random_place_cell
}


void sector(double E[], double T[], int quadrant){
    switch (quadrant)
    {
    case 1:
        first_quad(E, T);
        break;
    case 2:
        first_quad(E, T);
        second_quad(E, T);
        break;
    case 3:
        first_quad(E, T);
        second_quad(E, T);
        third_quad(E, T);
        break;
    case 4:
        first_quad(E, T);
        second_quad(E, T);
        third_quad(E, T);
        fourth_quad(E, T);
        break;
    }
};

void first_quad(double E[], double T[]){
    int node;
    for(int x = 0; x<X_SIZE/2;x++){
        for(int y = Y_SIZE/2; y<Y_SIZE; y++){
            coordinates_to_node(node, x, y);
            if(T[node]==0){
                E[node] = -1;
            }
        }
    }
};

void second_quad(double E[], double T[]){
    int node;
    for(int x = X_SIZE/2; x<X_SIZE;x++){
        for(int y = Y_SIZE/2; y<Y_SIZE; y++){
            coordinates_to_node(node, x, y);
            if(T[node]==0){
                E[node] = -1;
           }
        }
    }
};

void third_quad(double E[], double T[]){
    int node;
    for(int x = X_SIZE/2; x<X_SIZE;x++){
        for(int y = 0; y<Y_SIZE/2; y++){
            coordinates_to_node(node, x, y);
            if(T[node]==0){
                E[node] = -1;
            }
        }
    }
};

void fourth_quad(double E[], double T[]){
    int node;
    for(int x = 0; x<X_SIZE/2;x++){
        for(int y = 0; y<Y_SIZE/2; y++){
            coordinates_to_node(node, x, y);
            if(T[node]==0){
                E[node] = -1;
            }
        }
    }
};