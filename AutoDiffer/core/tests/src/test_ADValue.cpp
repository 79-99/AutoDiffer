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

void All_testcheck(){
    printf("Starting AutoDiffer Library tests...\n");
}

/*
 *
 * 
 * ADValue TESTS
 * 
 * 
*/

TEST(Getter_int,int){
    int value = 3;
    int seed = 7;
    ADValue<int> x1(value,seed);

    /* test getters */
    EXPECT_EQ(x1.val(),value);  // note: EXECT_EQ used only for integers
    EXPECT_EQ(x1.dval(0),seed);
}

TEST(Getter_float,float){
    float value = 9.8f;
    float seed = 1.0f;
    ADValue<float> x(value,seed);

    /* test getters */
    EXPECT_NEAR(x.val(), value, DTOL);
    EXPECT_NEAR(x.dval(0), seed, DTOL);
}

TEST(Getter_double,double){
    double value = 9.8;
    double seed = 1.0;
    ADValue<double> x(value,seed);

    /* test getters */
    EXPECT_NEAR(x.val(), value, DTOL);
    EXPECT_NEAR(x.dval(0), seed, DTOL);
}

TEST(Operators,Add_double){
    double seed1 = 1.9;
    double seed2 = 4.4;

    ADValue<double> x1(1.0,seed1);
    ADValue<double> x2(2.0,seed2);

    /* add operator */
    ADValue<double> c = x1 + x2;

    EXPECT_NEAR(c.val(), 3.0, 1E-6);
    EXPECT_NEAR(c.dval(0), 6.3, 1E-6);
}

TEST(equality_comparison_operator, double){
    double seed1 = 1.9;
    double seed2 = 4.4;

    ADValue<double> x1(1.0,seed1);
    ADValue<double> x2(2.0,seed2);

    // Values don't match.
    EXPECT_FALSE(x1 == x2);

    // Equality is true.
    ADValue<double> x3(1.0,seed1);
    EXPECT_TRUE(x1 == x3);

    std::vector<double> seed_vec = { 5.4, 32 };
    // Vector seeds.
    ADValue<double> x4(1.0, seed_vec);

    // Different size seeds.
    EXPECT_FALSE(x1 == x4);

    std::vector<double> seed_vec2 = { 5.4, 31 };
    
    // Vector seeds diff.
    ADValue<double> x5(1.0, seed_vec2);

    EXPECT_FALSE(x4 == x5);

    // Vector seeds same.
    ADValue<double> x6(1.0, seed_vec2);
    EXPECT_TRUE(x5 == x6);
}

TEST(nq_comparison_operator, double){
    // Same test as before but flip expectations.
    double seed1 = 1.9;
    double seed2 = 4.4;

    ADValue<double> x1(1.0,seed1);
    ADValue<double> x2(2.0,seed2);

    // Values don't match.
    EXPECT_TRUE(x1 != x2);

    // Equality is true.
    ADValue<double> x3(1.0,seed1);
    EXPECT_FALSE(x1 != x3);

    std::vector<double> seed_vec = { 5.4, 32 };
    // Vector seeds.
    ADValue<double> x4(1.0, seed_vec);

    // Different size seeds.
    EXPECT_TRUE(x1 != x4);

    std::vector<double> seed_vec2 = { 5.4, 31 };
    
    // Vector seeds diff.
    ADValue<double> x5(1.0, seed_vec2);

    EXPECT_TRUE(x4 != x5);

    // Vector seeds same.
    ADValue<double> x6(1.0, seed_vec2);
    EXPECT_FALSE(x5 != x6);
}

