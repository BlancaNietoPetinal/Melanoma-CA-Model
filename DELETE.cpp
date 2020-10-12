#include <random>
#include <iostream>
#include <ctime>
#include <chrono>

bool isLateralBorder(int node, int nx, int ny);

int main()
{
    int NX = 5, NY = 5, node = 5;
    if(isLateralBorder(node, NX, NY)){
        std::cout<<"El nodo: "<<node<<" es un nodo lateral."<<std::endl;
    }
    else{
        std::cout<<"El nodo: "<<node<<" NO es un nodo lateral"<<std::endl;
    }

    
    return 0;
}

bool isLateralBorder(int node, int nx, int ny){ //TODO: Encontrar un algoritmo mejor
// con solo node y node_number
  bool result = false;
  for ( int j = 1; j <= 2 * ny - 1; j++ )
  {
    for ( int i = 1; i <= 2 * nx - 1; i++ )
    {
      if ( (j == 1 ||
            j == 2 * ny - 1) && (node == (i+j-2)))
      {
        result = true;
      }
      node = node + 1;
    }
  }
  return result;
}
