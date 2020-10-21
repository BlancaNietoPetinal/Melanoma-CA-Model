#include <iostream>
#include <fstream>
#include "../../DestructionLib/destructionlib.h"
#define SIZE 10
void createFile();
bool is_correct(int* mat);

int main(){
    int *mat;
    mat = new int[SIZE];

    createFile();
    mat = getMat("Tests/getMat/getMat_test.txt", SIZE);
    
    if (is_correct(mat)){
        std::cout<<"Funciona correctamente.";
    };
    return 0;
}

void createFile(){
    std::ofstream file("Tests/getMat/getMat_test.txt");
    for(int i = 0; i<10; i++){
        if(i%2 == 0){
            file<<1<<"\n";
        }
        else{
            file<<0<<"\n";
        }
    }
    file.close();
}

bool is_correct(int* mat){
    bool result = true;
    for(int i = 0; i<10; i++){
        if(i%2 == 0){
            if(mat[i] != 1){
                result = false;
            }
        }
        else{
            if(mat[i]!=0){
                result = false;
            }
        }
    }
    return result;
}