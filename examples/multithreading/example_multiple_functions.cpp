/**
 * @file    example_multiple_functions.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDifferStdThread class to calculate
 *          multiple function derivatives in a multithreaded way.
 *
 *    
 * To run this example run `make` in this directory, followed by `./example_multiple_functions`
 *
 */

#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <vector>

#include "../../AutoDiffer/include/AutoDiffer.hpp"

std::string LARGE_FUNCTION = 
        "(tan(log_2.3_(exp((sin(((x*y)/x)*3))*(cos(((x*y)/x)*4))))))";

std::string MakeMassiveFunction(int n) {
    std::string result = LARGE_FUNCTION;
    for (int i = 0; i < n; ++i) {
        result = "(" + result + "+" + LARGE_FUNCTION + ")";
    }
    return result;
}


int main() {
    // Multithreaded ad.
    AutoDifferStdThread<double> ad;

    // Make vector of large functions.
    std::string massive_function = MakeMassiveFunction(500);
    // std::cout << "Taking derivative of: " << massive_function << std::endl;
    std::vector<std::string> func_vec(6, massive_function);

    // Start timer. (multi)
    auto start = std::chrono::high_resolution_clock::now();
    
    // Result is a vector of statuses and ADValues. This is multithreaded. With
    // 6 threads (one per function).
    std::vector<std::pair<Status, ADValue<double>>> result = ad.DeriveStdThread(
        func_vec);
    
    // Stop timer and get duration.
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stop - start);

    std::cout << "Multithreaded time (microseconds): " << duration.count() 
        << std::endl;

    // Make second vector of large functions.
    std::vector<std::string> func_vec2(6, LARGE_FUNCTION);

    // Start timer. (single threaded)
    start = std::chrono::high_resolution_clock::now();
    
    // Result is a vector of statuses and ADValues. This is the single threaded
    // derive.
    std::vector<std::pair<Status, ADValue<double>>> result2 = ad.Derive(
        func_vec);
    
    // Stop timer and get duration.
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stop - start);

    std::cout << "Single threaded time (microseconds): " << duration.count() 
        << std::endl;
    return 0;
}
