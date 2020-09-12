#include <iostream>
#include<fstream>
// MANANA: queremos tener un grid de punteros dirigidos a objetos (pixel) 
class Pixel{
    private:
        char cel_type;
    public:
        Pixel(){cel_type = ' ';};
        Pixel(char _type){cel_type = _type;};
        void get_type(){std::cout<<cel_type;}
};


class Grid{ // Creates a grid of MxN pixels and
    private:
        int M, N;
        Pixel p, *pt, grid[1][1];
        //pt = &p1;
    public:
        Grid(int _M, int _N, Pixel _p){M = _M; _N = N; p = _p;};
        void get_grid(Pixel &p){grid[M][N] = p;}

};


int main(){
    int M = 3, N = 4;
    Pixel p1('T'), *pt; //Set the pixel type
    Grid g(M, N, p1);
    g.get_grid(p1);
    //pt = &p1; // Set the pointer
    //std::cout<<"Direccion: ";
    //pt->get_type();
};


/*
class Pixel{
    private:
        char type;
    public:
        Pixel(char);
};

Pixel::Pixel(char _type){
    type = _type;
}; */