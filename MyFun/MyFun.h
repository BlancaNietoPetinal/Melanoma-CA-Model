#include <iostream>
#include <array>
#include <fstream>

class Pixel{
    private:
        char cel_type;
        float M, N;
    public:
        Pixel();
        Pixel(char _type);
        char getType();
        ~Pixel(){};
};

class Grid{
    private:
        std::array<std::array<Pixel*,30>,30> p; //mejor usar array que *p[rows][cols]
        std::array<std::array<Pixel*,30>,30> X;
        Pixel  p0;
    public:
        Grid(); //create the grid
        std::array<std::array<Pixel*,30>,30> getMatrix(char cell_type);
        void printPixel(int x, int y);
        void addPixel(int x, int y, Pixel pxl);
        
        ~Grid(){};
};