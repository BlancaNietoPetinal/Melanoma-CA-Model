#include <iostream>
#include <array>
#include <fstream>
#include "../Libraries/DestructionLib/destructionlib.h"


void test();

int main(){
    std::vector<int> vec;
    for(int i=0;i<5;i++){
        vec.push_back(i);
    }
    std::cout<<"Esta vacio?: "<<vec.empty()<<std::endl;
    return 0;
}

