/*Construya una clase llamada Rectangulo 
que tenga los siguientes atributos: 
 - largo
 - ancho
y los siguientes metodos: 
 - perimetro()
 - area().*/
#include<iostream>

using namespace std;

 class Rectangle{
    private: // ATRIBUTOS
       float heigh, width; 
    public: // METODOS
        Rectangle(float, float); // CONSTRUCTOR
        void perimeter();
        void area();
 };

// CONSTRUCTOR
 Rectangle::Rectangle(float _heigh, float _width){
     heigh = _heigh;
     width = _width;
 };

 void Rectangle::perimeter(){
     cout<<"El perimetro es: "<< 2*heigh + 2*width<<endl;
 };

 void Rectangle::area(){
     cout<<"El area es: "<< heigh*width<<endl;
 };

int main(){
    Rectangle r1 = Rectangle(2, 3);
    r1.area();
    r1.perimeter();
};
