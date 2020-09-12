#include<iostream>
#include<stdlib.h>
using namespace std;


// CLASES
class Persona{
    private:
        string nombre;
        int edad;
    public:
        Persona(string, int);
        void mostrarPersona();
};

class Empleado : public Persona{
    private:
        string empresa;
    public:
        Empleado(string, int, string);
        void mostrarEmpleado();
};

class Estudiante: public Persona{
    private:
        int n_est;
    public:
        Estudiante(string, int, int);
        void mostrarEstudiante();
};

class Universitario : public Estudiante{
    private:
        string nombre_uni;
        int n_universitario;
    public:
        Universitario(string, int, int, string, int);
        void mostrarUniversitario();
};


// COSNTRUCTORES
Persona::Persona(string _nombre, int _edad){
    nombre = _nombre;
    edad = _edad;
};

Estudiante::Estudiante(string _nombre, int _edad, int _n_est): Persona (_nombre, _edad){
    n_est = _n_est;
};

Universitario::Universitario(string _nombre, int _edad, int _n_est, string _nombre_uni, int _n_universitario) : Estudiante(_nombre, _edad, _n_est){
    nombre_uni = _nombre_uni;
    n_universitario = _n_universitario;
};

Empleado::Empleado(string _nombre, int _edad, string _empresa) : Persona(_nombre, _edad){

    empresa = _empresa;
};

// METODOS
void Persona::mostrarPersona(){
    cout<<"Nombre: "<<nombre<<endl<<"Edad: "<<edad<<endl;
};

void Estudiante::mostrarEstudiante(){
    mostrarPersona();
    cout<<"Numero de estudiante: "<<n_est<<endl;
};

void Universitario::mostrarUniversitario(){
    mostrarEstudiante();
    cout<<"Universidad: "<<nombre_uni<<endl;
    cout<<"Numero de universitario: "<<n_universitario<<endl;
};

void Empleado::mostrarEmpleado(){
    mostrarPersona();
    cout<<"Nombre de la empresa: "<<empresa<<endl;
};

// FUNCION PRINCIPAL
int main(){
    Persona p1("Pepa",20);
    Estudiante e1("Blanca", 22, 123);
    e1.mostrarPersona();
};