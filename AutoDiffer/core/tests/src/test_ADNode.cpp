/* system header files */
#include <stdlib.h>
#include <stdio.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADValue.hpp"
#include "ADNode.hpp"
#include "test_vars.h"

void ADNode_testcheck(){
    printf("Starting ADNode Library tests...\n");
}

TEST(functionality, int){
    int value = 3;
    int seed = 1;
    ADValue<int> x1(value, seed);

    int value2 = 5;
    int seed2 = 0;
    ADValue<int> v1(value2, seed2);

    ADNode<int> node1(x1, v1, Operation::addition);
    ADValue<int> v2 = node1.Evaluate();
    EXPECT_EQ(v2.val(), 8);
    EXPECT_EQ(v2.dval(), 1);

    int value3 = 3;
    int seed3 = 0;
    ADValue<int> v3(value3, seed3);

    ADNode<int> node2(v2, v3, Operation::power);
    ADValue<int> v4 = node2.Evaluate();

    EXPECT_EQ(v4.val(), 512);
    EXPECT_EQ(v4.dval(), 192);

    ADNode<int> node3(x1, v1, Operation::subtraction);
    ADValue<int> v5 = node3.Evaluate();
    EXPECT_EQ(v5.val(), -2);
    EXPECT_EQ(v5.dval(), 1);

    // Multiplication and division tests for int case
    ADNode<int> node4(x1, v2, Operation::multiplication);
    ADValue<int> v6 = node4.Evaluate();
    EXPECT_EQ(v6.val(), 24);
    EXPECT_EQ(v6.dval(), 11);

    int value7 = 3;
    int seed7 = 7;
    ADValue<int> v7(value7,seed7);

    ADNode<int> node5(x1, v7, Operation::division);
    ADValue<int> v8 = node5.Evaluate();
    EXPECT_EQ(v8.val(), 1);
    EXPECT_EQ(v8.dval(), -2);

}

TEST(functionality, double){
    // Defining vals to start with 
    double value = 3.2;
    double seed = 1.1;
    ADValue<double> x1(value, seed);

    double value2 = 5.8;
    double seed2 = -2.2;
    ADValue<double> v1(value2, seed2);

    // Addition, subtraction, powers
    ADNode<double> node1(x1, v1, Operation::addition);
    ADValue<double> v2 = node1.Evaluate();
    EXPECT_NEAR(v2.val(), 9, 1e-6);
    EXPECT_NEAR(v2.dval(), -1.1, 1e-6);

    ADNode<double> node2(x1, v1, Operation::subtraction);
    ADValue<double> v3 = node2.Evaluate();
    EXPECT_NEAR(v3.val(), -2.6, 1e-6);
    EXPECT_NEAR(v3.dval(), 3.3, 1e-6);

    ADNode<double> node3(x1, v1, Operation::power);
    ADValue<double> v4 = node3.Evaluate();
    EXPECT_NEAR(v4.val(), pow(3.2,5.8), 1e-6);
    EXPECT_NEAR(v4.dval(), 1696.44808823, 1e-6);

    // Multiplication and division tests
    ADNode<double> node4(x1, v1, Operation::multiplication);
    ADValue<double> v5 = node4.Evaluate();
    EXPECT_NEAR(v5.val(), 18.56, 1e-6);
    EXPECT_NEAR(v5.dval(), -.66, 1e-6);

    ADNode<double> node5(x1, v1, Operation::division);
    ADValue<double> v6 = node5.Evaluate();
    EXPECT_NEAR(v6.val(), 3.2/5.8, 1e-6);
    EXPECT_NEAR(v6.dval(), 0.3989298, 1e-6);

    // Trig and exp tests
    ADNode<double> node6(v2, v2, Operation::sin);
    ADValue<double> v7 = node6.Evaluate();
    EXPECT_NEAR(v7.val(), sin(9), 1e-6);
    EXPECT_NEAR(v7.dval(), cos(9)*v2.dval(), 1e-6);

    ADNode<double> node7(v2, v2, Operation::exp);
    ADValue<double> v8 = node7.Evaluate();
    EXPECT_NEAR(v8.val(), exp(9), 1e-6);
    EXPECT_NEAR(v8.dval(), exp(9)*-1.1, 1e-6);

    ADNode<double> node8(v2, v2, Operation::cos);
    ADValue<double> v9 = node8.Evaluate();
    EXPECT_NEAR(v9.val(), cos(9), 1e-6);
    EXPECT_NEAR(v9.dval(), -sin(9)*v2.dval(), 1e-6);

    ADNode<double> node9(v2, v2, Operation::tan);
    ADValue<double> v10 = node9.Evaluate();
    EXPECT_NEAR(v10.val(), tan(9), 1e-6);
    EXPECT_NEAR(v10.dval(), -1.3250484, 1e-6);

}