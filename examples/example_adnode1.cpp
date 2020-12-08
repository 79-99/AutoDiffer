/**
 * @file    example_adnode1.cpp
 * @brief   Demonstrates the used of the
 *          templated ADNode and ADValue classes.
 *
 *    
 * To run this example run `make` in this directory, followed by `./example_adnode1`
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#include "../AutoDiffer/include/AutoDiffer.hpp"


int main() {
    // ADNode and value usage for cos(x+5) at x=3.

    // First define ADValue for x.
    double value = 3;
    double seed = 1;
    ADValue<double> x(value, seed);

    // Then ADValue for the constant 5.
    double value2 = 5;
    double seed2 = 0;
    ADValue<double> v1(value2, seed2);

    // Use the ADNode to evaluate the addition of x and v1.
    ADNode<double> node1(x, v1, Operation::addition);
    ADValue<double> x2 = node1.Evaluate();

    // Create second ADNode for the cosine operation.
    ADNode<double> node2(x2, Operation::cos);

    // Get out final ADValue object.
    ADValue<double> final = node2.Evaluate();

    std::cout << "ADNode of function f(x) = cos(x+5) at x=3" << std::endl;
    std::cout << "Expected function value = -0.145500; AutoDiffer function value = "
        << final.val() << std::endl;
    std::cout << "Expected derivative = -0.989358; AutoDiffer derivative = " 
        << final.dval(0) << std::endl;
    
    return 0;
}
