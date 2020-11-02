#include "generatorlib.h"


void grow(double M[], double N[], int T[], int D[], int H[], int xsize, int ysize){  
    int var;
    std::seed_seq seed{static_cast<long long>(std::chrono::high_resolution_clock::now()
                                   .time_since_epoch()
                                   .count()),
                            static_cast<long long>(reinterpret_cast<intptr_t>(&var))};
    std::mt19937 generator(seed);
    //std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> dice_distribution(1,3);
    int dice;
    for(int node = 0; node < xsize*ysize; node++)
    {   
        changeNegativeValue(N[node]);
        changeNegativeValue(M[node]);
        if(T[node] >= 1){
            dice = dice_distribution(generator);
            switch (dice)
            {
            case 1:
                necrosis(M, T, D, node, generator);
                break;
            case 2: 
                migracion(M, T, D, H, node, xsize, ysize, generator);
                break;
            case 3:
                division(N, T, D, H, node, xsize, ysize, generator);
                break;
            } 
        }
    }    
}

void changeNegativeValue(double &value){
    if(value<0){
        value = 0;
    }
    return;
}

void necrosis(double M[], int T[], int D[], int node, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,1);
    double rnd_n = distribution(generator), P; 
    P = exp(- pow(M[node]/(T[node]*NEC) ,2));
    
    if(P>abs(rnd_n)){ 
        std::cout<<"NECROSIS: "<<P<<" Random: "<<rnd_n<<std::endl;
        T[node]--;
        if(T[node] == 0){
            D[node] = 1;
        }
    }
    return;
}
void migracion(double M[], int T[], int D[], int H[], int node, int xsize, int ysize, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,1);
    std::uniform_int_distribution<> dice_distr(1,50);
    std::vector<int> neighbour_nodes, free_nodes;
    int neighbour_node, index;
    double rnd_n = distribution(generator);
    double P = 1 - exp( - (T[node] * pow(M[node]/MIG,2)));
    if(P>abs(rnd_n)){
        neighbour_nodes = get_neighbours(T, node, 1, xsize, ysize);
        free_nodes = get_specific_neighbours(T, node, 1, 0, '=', xsize, ysize);
        if( !free_nodes.empty() ){ // room, pick random
            index = dice_distr(generator) % free_nodes.size();
            neighbour_node = free_nodes[index];
            if(T[node] > 1){
                T[node]--;
                T[neighbour_node] = 1;
                if (H[neighbour_node] == 1){
                    H[neighbour_node] = 0;
                }
                else if (D[neighbour_node] == 1) {
                    D[neighbour_node] = 0;
                }
            }
            else{
                T[node]--;
                T[neighbour_node]++;
                if (H[neighbour_node] == 1){
                    H[neighbour_node] = 0;
                    H[node] = 1;
                }
                else if (D[neighbour_node] == 1) {
                    D[neighbour_node] = 0;
                    D[node] = 1;
                }
            }
        }
        else{
            index = dice_distr(generator) % neighbour_nodes.size();
            neighbour_node = neighbour_nodes[index];
            T[node]--;
            T[neighbour_node]++;
            if(T[node]==0){
                H[node] = 1;
            }
            //D[node]++; //Esto lo he supuesto, preguntar
        }
    }
};
void division(double N[], int T[], int D[], int H[], int node, int xsize, int ysize, std::mt19937 generator){
    std::normal_distribution<double> distribution(0,1);
    std::uniform_int_distribution<int> dice_dist(1,50);
    std::vector<int> free_nodes;
    
    int neighbour_node, index;
    double rnd_n = distribution(generator), P;
    P = 1 - exp( - pow(N[node]/(T[node]*DIV), 2));

    if(P>abs(rnd_n)){
        free_nodes = get_specific_neighbours(T,node,1,0,'=',xsize,ysize);
        if( free_nodes.empty() ){
            T[node]++;
        }
        else{
            index = dice_dist(generator) % free_nodes.size();
            neighbour_node = free_nodes[index];
            T[neighbour_node] = 1;
            if(H[neighbour_node] == 1){
                H[neighbour_node] = 0;
            }
            else{
                D[neighbour_node] = 0;
            }
        }
    }
    return;
};


