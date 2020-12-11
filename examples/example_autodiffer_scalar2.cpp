/**
 * @file    example_autodiffer_scalar2.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer class.
 *
 *    
 * To run this example run `make` in this directory, followed by 
 * `./example_autodiffer_scalar2`
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#include "../AutoDiffer/include/AutoDiffer.hpp"


int main() {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2.0, /*dval=*/1.0);
    std::pair<Status, ADValue<double>> res = ad.Derive(
        "(exp((sin((2*x)/3))/(x^2)))");
    
    std::cout << "AutoDiffer of function f(x) = exp(sin(2x/3)/x^2) at x=2" << std::endl;
    std::cout << "Expected function value = 1.27505; AutoDiffer function value = "
        << res.second.val() << std::endl;
    std::cout << "Expected derivative = -0.259827; AutoDiffer derivative = " 
        << res.second.dval(0) << std::endl;
    return 0;
}
