#include <iostream>
#include <math.h>

class ComplexPol{
    public:
        float mod, arg;
        ComplexPol(float, float);
        ~ComplexPol(){}
};

ComplexPol::ComplexPol(float real, float img){
    mod = atan(img/real);
    arg = sqrt(pow(real,2) + pow(img,2));
};

int main(){
    float a = 3.0, b = 4.5;
    ComplexPol c1(a,b);
    std::cout<<"Modulo: "<<c1.mod<<" Argumento: "<<c1.arg<<std::endl;
};