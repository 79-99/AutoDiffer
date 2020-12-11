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


/**
 * For this example we will consider the follow vector equation:
 * 
 * f1(x,y) = x^2 + 5*y 
 * 
 * We can manually calculate the gradient:
 * 
 * grad = [ 2x   5  ]
 * 
 * Lets say we want to evaluate the function and the gradient at x = -1, y = 2.
 * This gives the following function values:
 * 
 * f1(-1,2) = 11
 * 
 * And the gradient values of:
 * grad = [    -2    5    ]
 * 
 * Now we can verify that this is what we get when we run the AutoDiffer.
 */

int main() {
    // Create AutoDiffer object.
    AutoDiffer<double> ad;

    // Set up seed vectors. Order matters here! The first seed in the seed vector
    // need to correspond to the first variable that SetSeedVector is called with.
    std::vector<double> x_seed = {1, 0};
    std::vector<double> y_seed = {0, 1};

    // Set the seed vectors (in the correct order).
    ad.SetSeedVector("x", -1, x_seed);
    ad.SetSeedVector("y", 2, y_seed);

    // Run derive.
    std::pair<Status, ADValue<double>> res = ad.Derive("((x^2)+(5*y))");
    
    // Make sure that no error was returned.
    assert(res.first.code == ReturnCode::success);

    std::cout << "AutoDiffer of function f(x,y) = x^2+5y at x=-1, y=2" << std::endl;
    std::cout << "Expected function value = 11; AutoDiffer function value = "
        << res.second.val() << std::endl;
    std::cout << "Expected partial x = -2; AutoDiffer partial x = " 
        << res.second.dval(0) << std::endl;
    std::cout << "Expected partial y = 5; AutoDiffer partial y = " 
        << res.second.dval(1) << std::endl;
    return 0;
}
