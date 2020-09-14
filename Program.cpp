#include <iostream>
#include <vector>

#define M 300
#define N 300
// https://processing.org/tutorials/2darray/
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
        Pixel  *p[M][N], p0 = 'R';
    public:
        Grid(); //create the grid
        Grid(int, int, Pixel); //place the pixel???
        void print_pixel(int, int);
        ~Grid(){};
        // Crear addpixel

};

Grid::Grid(){
    rows = M;
    cols = N;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
        p[i][j] = &p0;
        }
    }
};

void Grid::print_pixel(int x, int y){
    std::cout<<p[x][y]->getType();
};

int main(){
    //Pixel p1('T'), p2('H');
    Grid g;
    g.print_pixel(1,1);
    return 0;
};
