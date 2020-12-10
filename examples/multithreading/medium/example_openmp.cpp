/**
 * @file    example_std_thread.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer multithreaded class.
 *
 *    
 * To run this example run `make` in this directory, followed by `./example_std_thread`
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <vector>


#include "../../../AutoDiffer/include_examples/AutoDiffer.hpp"


// Helper to create long functions.
std::string CreateStringEq(int n) {
    std::string ret = "(x)";
    for (int i = 0; i < n-1; ++i) {
        ret = "(" + ret + "+x)";
    }
    return ret;
}

void TimeOpenMpAD(int num_eqs, int num_threads, bool verbose) {
    // Create Std Thread Autodiffer. 
    // std::cout << num_threads << std::endl;
    AutoDifferOpenMp<double> ad(6);
    ad.SetSeed("x", /*value=*/0.5, /*dval=*/1);

    // Create large equation and make copies of it.
    std::string eq = CreateStringEq(5);
    std::vector<std::string> vec_strings(num_eqs, eq);

    // Time the multithreaded derive.
    auto start = std::chrono::high_resolution_clock::now();
    auto res = ad.DeriveOpenMp(vec_strings);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        stop - start); 
    if (verbose) {
        std::cout << "Multi-threaded time (milliseconds): " <<  duration.count() 
            << std::endl;
    } else {
        std::cout << duration.count() << std::endl;
    }   
}

void TimeSingleThreadAD(int num_eqs, bool verbose) {
    // Create Autodiffer. 
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.5, /*dval=*/1);

    // Create large equation and make copies of it.
    std::string eq = CreateStringEq(5);
    std::vector<std::string> vec_strings(num_eqs, eq);

    // Time the single threaded derive.
    auto start = std::chrono::high_resolution_clock::now();
    auto res = ad.Derive(vec_strings);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        stop - start); 
    if (verbose) {
        std::cout << "Single-threaded time (milliseconds): " 
            <<  duration.count() << std::endl;
    } else {
        std::cout << num_eqs << ',' << duration.count() << ',';
    }
    
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Please specify number of equations and threads: ";
        std::cout << "Example Usage: ./example_openmp 100 6" << std::endl;
        return 0;
    }

    bool verbose = true;
    if (argc == 4 && std::strcmp(argv[3], "-nv") == 0) {
        verbose = false;
    }

    // Get number of eqs.
    std::istringstream ss(argv[1]);
    int num_eqs;
    if (!(ss >> num_eqs)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
        return 0;
    } else if (!ss.eof()) {
        std::cerr << "Trailing characters after number: " << argv[1] << '\n';
        return 0;
    }

    // Get number of threads.
    std::istringstream ss2(argv[2]);
    int num_threads;
    if (!(ss2 >> num_threads)) {
        std::cerr << "Invalid number: " << argv[2] << '\n';
        return 0;
    } else if (!ss2.eof()) {
        std::cerr << "Trailing characters after number: " << argv[2] << '\n';
        return 0;
    }
    // std::cout << num_threads << std::endl;

    // By changing the number of equations we can see speedup.
    TimeSingleThreadAD(num_eqs, verbose);
    TimeOpenMpAD(num_eqs, num_threads, verbose);
}