#include <iostream>
#include <fstream>
#include "../Libraries/Tools/toolslib.h"
# include "../constants.hpp"
using namespace constants;

int cell_num;
int *T;

void test();

int main(){
    test();
    return 0;
}
void test(){
    T = new int[NODE_NUM];
    T = get_mat("Tests/Sample/Ttest_50x50_230.txt", NODE_NUM);
    cell_num = cell_counter(T, NODE_NUM);
    std::cout<<"Numero de celulas: "<<cell_num<<std::endl;
}