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

const std::string TEST_MEDIUM_EQ = "((((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x)+((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x))+((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x))";

// Test helper to create long functions.
std::string CreateStringEq(int n) {
    std::string ret = "(x)";
    for (int i = 0; i < n-1; ++i) {
        ret = "(" + ret + "+x)";
    }
    return ret;
}

// Test Std Thread version for currectness.
TEST(autodiffer_multithread_std_correctness_multifunc, double) {
    AutoDifferStdThread<double> ad(/*numthreads=*/6);
    ad.SetSeed("x", /*value=*/0.5, /*dval=*/1);
    
    // Create string eq and vector.
    std::string eq = CreateStringEq(100);
    std::vector<std::string> vec_strings(/*num_eqs=*/6, eq);

    auto res = ad.DeriveStdThread(vec_strings);
    for (auto& r : res) {
        EXPECT_EQ(r.first.code, ReturnCode::success);
        EXPECT_NEAR(r.second.val(), 100 * 0.5, 0.001);
        EXPECT_NEAR(r.second.dval(0), 100, 0.001);
    }
}

TEST(autodiffer_multithread_std_correctness_multiseed, double) {
    AutoDifferStdThread<double> ad(/*numthreads=*/6);
    
    // Create string eq and vector.
    std::string eq = CreateStringEq(100);
    std::vector<std::vector<std::pair<std::string, ADValue<double>>>> seeds;
    for (int i = 0; i < 100; ++i) {
        // Initialize a vector with single seed value.
        std::vector<std::pair<std::string, ADValue<double>>> temp_seeds;
        std::pair<std::string, ADValue<double>> temp_seed(
            "x", ADValue<double>(i,1));
        temp_seeds.push_back(temp_seed);
        seeds.emplace_back(temp_seeds);
    }

    auto res = ad.DeriveStdThread(eq, seeds);
    for (int i = 0; i < 100; ++i) {
        auto r = res[i];
        EXPECT_EQ(r.first.code, ReturnCode::success);
        EXPECT_NEAR(r.second.val(), 100 * i, 0.001);
        EXPECT_NEAR(r.second.dval(0), 100, 0.001);
    }
}

// Test Std Thread version for currectness.
TEST(autodiffer_multithread_openmp_correctness_multifunc, double) {
    AutoDifferOpenMp<double> ad(/*numthreads=*/6);
    ad.SetSeed("x", /*value=*/0.5, /*dval=*/1);
    
    // Create string eq and vector.
    std::string eq = CreateStringEq(100);
    std::vector<std::string> vec_strings(/*num_eqs=*/6, eq);

    auto res = ad.DeriveOpenMp(vec_strings);
    for (auto& r : res) {
        EXPECT_EQ(r.first.code, ReturnCode::success);
        EXPECT_NEAR(r.second.val(), 100 * 0.5, 0.001);
        EXPECT_NEAR(r.second.dval(0), 100, 0.001);
    }
}

TEST(autodiffer_multithread_openmp_correctness_multiseed, double) {
    AutoDifferOpenMp<double> ad(/*numthreads=*/6);
    
    // Create string eq and vector.
    std::string eq = CreateStringEq(100);
    std::vector<std::vector<std::pair<std::string, ADValue<double>>>> seeds;
    for (int i = 0; i < 100; ++i) {
        // Initialize a vector with single seed value.
        std::vector<std::pair<std::string, ADValue<double>>> temp_seeds;
        std::pair<std::string, ADValue<double>> temp_seed(
            "x", ADValue<double>(i,1));
        temp_seeds.push_back(temp_seed);
        seeds.emplace_back(temp_seeds);
    }

    auto res = ad.DeriveOpenMp(eq, seeds);
    for (int i = 0; i < 100; ++i) {
        auto r = res[i];
        EXPECT_EQ(r.first.code, ReturnCode::success);
        EXPECT_NEAR(r.second.val(), 100 * i, 0.001);
        EXPECT_NEAR(r.second.dval(0), 100, 0.001);
    }
}

// Testing OpenMp version.
TEST(autodiffer_vector_in_LONG, double) {
    AutoDifferOpenMp<double> ad(/*num_threads=*/6);
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::vector<std::string> equations;
    for (int i = 0; i < 100; i++) {
        equations.push_back(TEST_MEDIUM_EQ); 
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<Status, ADValue<double>>> res = ad.DeriveOpenMp(
        equations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stop - start); 
    std::cout << duration.count() << std::endl; 
}

TEST(autodiffer_vector_in_LONG_seeds, double) {
    AutoDifferOpenMp<double> ad(/*num_threads=*/6);
    std::vector<std::vector<std::pair<std::string, ADValue<double>>>> seeds; 

    std::vector<double> x_seed = { 1, 1 };
    std::vector<double> y_seed = { 1, 1 };
    ADValue<double> seed_val1(0.444, x_seed);
    std::vector<std::pair<std::string, ADValue<double>>> single_seed_list; 
    single_seed_list.push_back(std::pair<std::string, ADValue<double>>(
        "x", seed_val1));
    ADValue<double> seed_val2(0.444, y_seed);
    single_seed_list.emplace_back(std::pair<std::string, ADValue<double>>(
        "y", seed_val2));

    for (int i = 0; i < 10; i++) {
        seeds.push_back(single_seed_list); 
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<Status, ADValue<double>>> res = ad.DeriveOpenMp(
        TEST_MEDIUM_EQ, seeds);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stop - start); 
    std::cout << duration.count() << std::endl; 
}
