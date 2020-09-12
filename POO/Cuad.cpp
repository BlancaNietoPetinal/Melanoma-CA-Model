#include <iostream>

class Point{
    public:
        int p1, p2;
        Point(void){};
        Point(int, int);
        Point(int);
        ~Point(){};
};

Point::Point(int a, int b){
    p1 = a;
    p2 = b;
};

Point::Point(int a){
    p1 = a;
    p2 = a;
};

class Segment{
    public:
        Point P1, P2;
        Segment(void){};
        Segment(Point , Point);
        ~Segment(){};
};

Segment::Segment(Point s1, Point s2){
    P1 = s1; 
    P2 = s2;
};

class Cuad{
    public:
        Segment S1, S2;
        Cuad(void){};
        Cuad(Segment c1,Segment c2){S1 = c1; S2 = c2;};
        ~Cuad(){};
};

int main(){
    Point p1(0), p2(1), p3(2);
    Segment s1(p1,p2), s2(p1,p3);
    Cuad c(s1, s2);
};
