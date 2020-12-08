/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <math.h>
#include <chrono>
/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADValue.hpp"
#include "ADNode.hpp"
#include "AutoDiffer.hpp"
#include "Parser.hpp"
#include "test_vars.h"

/*
 *
 * 
 * AutoDiffer TESTS (multithreaded)
 * 
 * 
*/


TEST(autodiffer_vector_in_LONG, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::vector<std::string> equations;
    for (int i = 0; i < 100; i++) {
        equations.push_back("((((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x)+((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x))+((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x))"); 
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<Status, ADValue<double>>> res = ad.Derive(equations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
    std::cout << duration.count() << std::endl; 
}

TEST(autodiffer_vector_in_LONG_seeds, double) {
    AutoDiffer<double> ad;
    std::vector<std::vector<std::pair<std::string, ADValue<double>>>> seeds; 

    std::vector<double> x_seed = { 1, 1 };
    std::vector<double> y_seed = { 1, 1 };
    ADValue<double> seed_val1(0.444, x_seed);
    std::vector<std::pair<std::string, ADValue<double>>> single_seed_list; 
    single_seed_list.push_back(std::pair<std::string, ADValue<double>>("x", seed_val1));
    ADValue<double> seed_val2(0.444, y_seed);
    single_seed_list.emplace_back(std::pair<std::string, ADValue<double>>("y", seed_val2));

    for (int i = 0; i < 10; i++) {
        seeds.push_back(single_seed_list); 
    }

    std::string equation = "((((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x)+((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x))+((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x))";
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<Status, ADValue<double>>> res = ad.Derive(equation, seeds);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
    std::cout << duration.count() << std::endl; 
}