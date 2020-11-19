/**
 * @file    example.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer class.
 *
 *    
 * To run this example run `make` in this directory, followed by `./example`
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#include "../AutoDiffer/include/AutoDiffer.hpp"


int main() {
    AutoDiffer<float> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);
    std::pair<Status, float> res = ad.Derive("((x+5)^3)");
    
    std::cout << "AutoDiffer of function f(x) = ((x+5)^3) at x=7" << std::endl;
    std::cout << "Expected Result = 432; AutoDiffer Result = " << res.second 
        << std::endl;

    AutoDiffer<double> ad_double;
    ad_double.SetSeed("x", /*value=*/1.0, /*dval=*/1.0);
    std::pair<Status, double> res_double = ad_double.Derive(
        "(exp((sin((2*x)/3))/(x^2)))");
    
    std::cout << "AutoDiffer of function f(x) = exp(sin(2x/3)/x^2) at x=1" 
        << std::endl;
    std::cout << "Expected Result = -1.32291; AutoDiffer Result = " 
        << res_double.second << std::endl;

    return 0;
}
