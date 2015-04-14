#include <iostream>
#include <fstream>
int main(){

    int number = 1;
    if(*(char *)&number)
        std::cout<<"Little-endian!\n";
    else
        std::cout<<"Big-endian!\n";

    short int a = 0x0061;

    std::ofstream of;
    of.open("zz.txt", std::ios::binary);
    of.write((char*)&a, sizeof(a));

    of.close();

    return 0;
}
