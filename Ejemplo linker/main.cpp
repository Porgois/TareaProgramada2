#pragma once
#include <iostream>
extern "C" int _print();
int main(){
    std::cout <<_print() << "\n";
}
