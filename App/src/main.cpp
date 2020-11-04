/* system header files */
#include <stdio.h>
#include <iostream>

/* header files */
#include "AutoDiffer.hpp"

int main(int argc, char **argv){
    double seed1 = 1.9;
    double seed2 = 4.4;

    AutoDiffer<double> x1(1.0,seed1);
    AutoDiffer<double> x2(2.0,seed2);
    
    /* add operator */
    AutoDiffer<double> c = x1 + x2;

    std::cout << "     v, dv\n";
    std::cout << "  x1[" << x1.val() << ", " << x1.dval() << "]\n"
              << "+ x2[" << x2.val() << ", " << x2.dval() << "]\n"
              << "  ==========\n"
              << "   c[" <<  c.val() << ", " <<  c.dval() << "]\n";

    
    /* add equal operator */
    x1 += c;

    return 0;
}
