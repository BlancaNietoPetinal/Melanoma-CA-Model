
/* ---------- https://www.codesansar.com/numerical-methods/runge-kutta-rk-fourth-order-using-cpp-output.htm --*/
#include "rk4lib.h"
#include "../Tools/toolslib.h"

double f1(double t, double T,double H,double E){
    double result = (R1*T*(1 - (T/K1))) - (A12*T*H) - ((DC*pow((E/T),L)/(S+pow((E/T),L)))*T);
    if(isnan(result)){
        result=0;
    }
    return result;
}
double K(double E, double T){
    //return DC*pow((E/T),L)/(S+pow((E/T),L));
    return DC*pow(E,L)/((S*pow(T,L))+pow(E,L));
}
double f2(double t, double T,double H,double E){
    double result = (R2*H*(1- (H/K2))) - (A21*T*H);
    if(isnan(result)){
        result=0;
    }
    return result;
}
double f3(double t, double T,double H,double E){
    double result = SIGMA-(D3*E)+((G*E*(pow((K(E,T)*T),2))/(HC + pow((K(E,T)*T),2)))) -(A31*T*E);
    if(isnan(result)){
        result=0;
    }
    return result;
}


double* RK4(double T, double H, double E){
    static double mat[3];
    double t0 = 0, t = 0.1, Tn, Hn, En;
    double kh1, kh2, kh3, kh4, kt1, kt2, kt3, kt4, ke1, ke2, ke3, ke4;
    int n = 100;
    double h = ((t-t0)/n);

    for(int i = 0; i < n; i++){
        kt1 = h*f1(t0, T, H, E);
        kh1 = h*f2(t0, T, H, E);
        ke1 = h*f3(t0, T, H, E);

        kt2 = h*f1(t0 + 0.5*h, T + 0.5*kt1, H + 0.5*kh1, E + 0.5*ke1);
        kh2 = h*f2(t0 + 0.5*h, T + 0.5*kt1, H + 0.5*kh1, E + 0.5*ke1);
        ke2 = h*f3(t0 + 0.5*h, T + 0.5*kt1, H + 0.5*kh1, E + 0.5*ke1);
        
        kt3 = h*f1(t0 + 0.5*h, T + 0.5*kt2, H + 0.5*kh2, E + 0.5*ke2);
        kh3 = h*f2(t0 + 0.5*h, T + 0.5*kt2, H + 0.5*kh2, E + 0.5*ke2);
        ke3 = h*f3(t0 + 0.5*h, T + 0.5*kt2, H + 0.5*kh2, E + 0.5*ke2);

        kt4 = h*f1(t0 + h, T + kt3, H + kh3, E + ke3);
        kh4 = h*f2(t0 + h, T + kt3, H + kh3, E + ke3);
        ke4 = h*f3(t0 + h, T + kt3, H + kh3, E + ke3);

        Tn = T + (kt1 + 2*kt2 + 2*kt3 + kt4) / 6; 
        Hn = H + (kh1 + 2*kh2 + 2*kh3 + kh4) / 6; 
        En = E + (ke1 + 2*ke2 + 2*ke3 + ke4) / 6; 

        t0 = t0 + h;
        T = Tn;
        H = Hn;
        E = En;
    }
    changeNegativeValue(T);
    changeNegativeValue(H);
    changeNegativeValue(E);
    mat[0] = T;
    mat[1] = H;
    mat[2] = E;
    return mat;
}

