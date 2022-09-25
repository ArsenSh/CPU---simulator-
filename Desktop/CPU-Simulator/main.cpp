#include <iostream>
#include <fstream>
#include "Header.h"

int main()
{
    std::ifstream file;
    std::string path = "";
    
      do{
          std::cout << "Enter file name: ";
          std::cin >> path;
          file.open(path + ".txt");
        }while(!file.is_open());
    
    CPU my_cpu;
    my_cpu.do_assembly(file);
    my_cpu.printing();
    
    file.close();
    
    return 0;
}

