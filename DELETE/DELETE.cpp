#include<iostream> 
#include<chrono> 
#include<random> 

int main() 
{ 
    /* Create random engine with the help of seed */
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count(); 
    std::default_random_engine e (seed); 
    std::normal_distribution<double> distN(0,1); 
    
    double X;
    for(int i =0; i<5;i++){
      X = distN(e);
      std::cout<<"X: "<<X<<" ABS: "<<fabs(X)<<"\n"; 
    }
    

  
  return 0; 
}