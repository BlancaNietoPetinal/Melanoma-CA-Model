#include <iostream>
#include <array>

#define cols 300
#define rows 300
// TODO: display with gnuplot? o Qt?

class Pixel{
    private:
        char cel_type;
        float M, N;
    public:
        Pixel(){cel_type = 'O'; M = 0; N = 0;};
        Pixel(char _type){cel_type = _type;};
        char getType(){return cel_type;}
        ~Pixel(){};
};

class Grid{
    private:
        std::array<std::array<Pixel*,rows>,cols> p; //mejor usar array que *p[rows][cols]
        std::array<std::array<char,rows>,cols> X;
        Pixel  p0;
    public:
        Grid(); //create the grid
        void printPixel(int x, int y){std::cout<<p[x][y]->getType();};
        auto getMatrix(char);
        void addPixel(int x, int y, Pixel pxl){p[x][y] = &pxl;};
        ~Grid(){};
};

Grid::Grid(){
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
        p[i][j] = &p0;
        }
    }
};

auto Grid::getMatrix(char cell_type){
    
    switch (cell_type)
    {
    case 'T':
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if(cell_type == p[i][j]->getType()){
                    X[i][j] = p[i][j]->getType();
                }
                else{
                    X[i][j] = 'H';
                }
            }
        }
        break;
    case 'E':
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if(cell_type == p[i][j]->getType()){
                    X[i][j] = p[i][j]->getType();
                }
                else{
                    X[i][j] = 'O';
                }
            }
        }
        break;

    default:
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if(cell_type == p[i][j]->getType()){
                        X[i][j] = p[i][j]->getType();
                    }
                    else{
                        X[i][j] = 'O';
                    }
                }
            }
        break;
    }
    return X;
};

int main(){
    std::array<std::array<char,rows>,cols> Tmat, Emat, Hmat;
    Pixel p1('T'), p2('H');
    Grid g; //creamos el grid de pixeles
    
    g.addPixel(1,1,p1); // introducimos un valor
    Tmat = g.getMatrix('T'); // obtenemos las matrices de las celulas
    Emat = g.getMatrix('E'); 
    Hmat =  g.getMatrix('H');

    std::cout<<"(1,1) = "<<Tmat[1][1]<<std::endl;
    std::cout<<"(1,2) = "<<Tmat[1][2]<<std::endl;

    return 0;
};
