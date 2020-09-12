#include <iostream>
#include <array>
// https://processing.org/tutorials/2darray/
class Pixel{
    private:
        char cel_type;
    public:
        Pixel(){cel_type = 'S';};
        Pixel(char _type){cel_type = _type;};
        char get_type(){return cel_type;}
};

class Grid{
    private:
        int rows, cols;
        Pixel g[0][0], *p[0][0]; //g guarda objetos y p guarda punteros
    public:
        Grid(int, int); //create the grid
        Grid(int, int, Pixel); //place the pixel
        auto get_grid(){return g;}; //SEGUIR POR AQUI
        void print_pixel(int, int);

};

Grid::Grid(int M, int N){
    Pixel p0;
    rows = M;
    cols = N;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            g[i][j] = p0;
            p[i][j] = &p0;
        }
    }
};

Grid::Grid(int _rows, int _cols, Pixel _p){
    p[0][0] = &_p;
    std::cout<<p[0][0];
    g[_rows][_cols] = _p;
};

void Grid::print_pixel(int x, int y){
    std::cout<<"El pixel deseado es:"<<g[x][y].get_type();
};

int main(){
    int M = 3, N = 4;
    Pixel p1('T'), *pt; //Set the pixel type
    pt = &p1;
    //std::cout<<"El pixel es de tipo: "<<pt->get_type();

    Grid g(M,N);
    //std::cout<<"El pixel es de tipo: ";
    g.print_pixel(1,1);
};
