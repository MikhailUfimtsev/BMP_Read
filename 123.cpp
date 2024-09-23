#include <cstdint>
#include "BMP_READ.h"
#include <iostream>


int main(int argc, char* argv[]) {
    //BMP_READ bmp_read("./bmp32.bmp");
    if (argc < 2) {
        std::cout << "Error: No argument. Add name file <*>.bmp" << std::endl;
        return 0;
    }
    BMP_READ bmp_read(argv[1]);
    return 0;
}