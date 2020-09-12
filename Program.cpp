#include <iostream>
#include <array>
// MANANA: queremos tener un grid de punteros dirigidos a objetos (pixel) 
class Pixel{
    private:
        char cel_type;
    public:
        Pixel(){cel_type = ' ';};
        Pixel(char _type){cel_type = _type;};
        char get_type(){return cel_type;}
};

int main(){
    int M = 3, N = 4;
    Pixel p1('T'), *pt; //Set the pixel type
    std::cout<<"El pixel es de tipo: "<<pt->get_type();
};
