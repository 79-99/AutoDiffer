/* system header files */
#include <stdlib.h>
#include <stdio.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "AutoDiffer.hpp"
#include "test_vars.h"

void AutoDiffer_testcheck(){
    printf("Starting AutoDiffer Library tests...\n");
}

TEST(Getter,int){
    int value = 3;
    int seed = 7;
    AutoDiffer<int> x1(value,seed);

    /* test getters */
    EXPECT_EQ(x1.val(),value);  // note: EXECT_EQ used only for integers
    EXPECT_EQ(x1.dval(),seed);
}

TEST(Getter,float){
    float value = 9.8f;
    float seed = 1.0f;
    AutoDiffer<float> x(value,seed);

    /* test getters */
    EXPECT_NEAR(x.val(), value, DTOL);
    EXPECT_NEAR(x.dval(), seed, DTOL);
}

TEST(Getter,double){
    double value = 9.8;
    double seed = 1.0;
    AutoDiffer<double> x(value,seed);

    /* test getters */
    EXPECT_NEAR(x.val(), value, DTOL);
    EXPECT_NEAR(x.dval(), seed, DTOL);
}

TEST(Setter,int){
    int value = 2;
    int seed = 1;
    AutoDiffer<int> x(value,seed);

    /* test getters */
    x.setval(3);
    EXPECT_EQ(x.val(), 3);
}

TEST(Setter,float){
    float value = 1.8f;
    float seed = 1.2f;
    AutoDiffer<float> x(value,seed);

    /* test getters */
    x.setval(3.3);
    EXPECT_NEAR(x.val(), 3.3, 1E-6);
}

TEST(Setter,double){
    double value = 1.8;
    double seed = 1.2;
    AutoDiffer<double> x(value,seed);

    /* test getters */
    x.setval(3.3);
    EXPECT_NEAR(x.val(), 3.3, 1E-6);
}

TEST(Operators,Add_double){
    double seed1 = 1.9;
    double seed2 = 4.4;

    AutoDiffer<double> x1(1.0,seed1);
    AutoDiffer<double> x2(2.0,seed2);

    /* add operator */
    AutoDiffer<double> c = x1 + x2;

    EXPECT_NEAR(c.val(), 3.0, 1E-6);
    EXPECT_NEAR(c.dval(), 6.3, 1E-6);
}
