/**
 * @file    example_autodiffer_scalar.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer class.
 *
 *    
 * To run this example run `make` in this directory, followed by 
 * `./example_autodiffer_scalar`
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#include "../AutoDiffer/include/AutoDiffer.hpp"


int main() {
    // Create AutoDiffer object.
    AutoDiffer<double> ad;

    // Set seed values for variables in the function.
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    // Call derive. 
    std::pair<Status, ADValue<double>> res = ad.Derive("((x+5)^3)");
    
    // Make sure that no error was returned.
    assert(res.first.code == ReturnCode::success);

    // Print results.
    std::cout << "AutoDiffer of function f(x) = ((x+5)^3) at x=7" << std::endl;
    std::cout << "Expected function value = 1728; AutoDiffer function value = "
        << res.second.val() << std::endl;
    std::cout << "Expected derivative = 432; AutoDiffer derivative = " 
        << res.second.dval(0) << std::endl;
    return 0;
}
