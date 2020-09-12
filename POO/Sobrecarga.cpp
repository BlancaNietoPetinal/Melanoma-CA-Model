/*Construya una clase Tiempo que
 contenga los siguientes atributos enteros: 
  - horas
  - minutos
  - segundos. 
Haga que la clase contenga 2 constructores:
  - Tiempo(int,int,int)
  - Sólo tendrá un campo que serán los segundos y desensamble el número entero largo 
  en horas, minutos y segundos.*/
#include<iostream>

using namespace std;

class Tiempo{
  private:
    int horas, minutos, segundos;
  public:
    Tiempo(int, int, int);
    Tiempo(float);
    void mostrar();
};

Tiempo::Tiempo(int _horas, int _minutos, int _segundos){
  horas = _horas;
  minutos = _minutos;
  segundos = _segundos;
};

Tiempo::Tiempo(float _segundos){
  horas = int(_segundos/3600);
  minutos = int((_segundos-(horas*3600))/60);
  segundos = int(_segundos - minutos*60 - horas*3600);
};

void Tiempo::mostrar(){
  cout<<"Horas: "<<horas<<" Minutos: "<<minutos<<" Segundos: "<<segundos<<endl;
};

int main(){
  Tiempo t1 = Tiempo(3596);
  t1.mostrar();
};
