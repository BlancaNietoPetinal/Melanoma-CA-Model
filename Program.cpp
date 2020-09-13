#include <iostream>
#include <vector>

#define M 300
#define N 300
// https://processing.org/tutorials/2darray/
//PROBLEMA: me sobreexcribe el pixel (comparar con cuadrado??)
class Pixel{
    private:
        char cel_type;
    public:
        Pixel(){/*cel_type = 'O';*/};
        Pixel(char _type){cel_type = _type;};
        char getType(){return cel_type;}
        ~Pixel(){};
};

class Grid{
    private:
        int rows, cols;
        Pixel  *p[M][N], p0 = 'T';
    public:
        Grid(); //create the grid
        Grid(int, int, Pixel); //place the pixel
       //auto get_grid(){return g;}; //SEGUIR POR AQUI
        /*void add_pixel(int, int, Pixel);
        void print_pixel(int, int);*/

};

Grid::Grid(){
    rows = M;
    cols = N;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
        //g[i][j] = p0;
        p[i][j] = &p0;
        }
    }
};

/*void Grid::add_pixel(int _rows, int _cols, Pixel _p){
    //p[_rows][_cols] = &_p;
    //[_rows][_cols] = _p;
};

void Grid::print_pixel(int x, int y){
    std::cout<<p[x][y]->getType();
};
*/

int main(){
    Pixel p1('T'), p2('H');
    std::cout<<"Before: "<<p1.getType()<<p2.getType()<<std::endl;
    Grid g();
    std::cout<<"After: "<<p1.getType()<<p2.getType()<<std::endl;
    
};
