/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADValue.hpp"
#include "ADNode.hpp"
#include "Parser.hpp"
#include "AutoDiffer.hpp"
#include "test_vars.h"

void AutoDiffer_testcheck(){
    printf("Starting AutoDiffer tests...\n");
}

TEST(autodiffer_test_basic, float){
    AutoDiffer<float> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    std::pair<Status, float> res = ad.Derive("((x+5)^3)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second, 432);
}

TEST(autodiffer_test_basic_division, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    std::pair<Status, double> res = ad.Derive("(x/3)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 0.3333, 0.001);
}

TEST(autodiffer_test_tan, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(tan(x/3))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 0.37329, 0.001);
}

TEST(autodiffer_test_complex1, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("((sin((2*x)/3))/(x^2))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, -0.712814, 0.001);
}

TEST(autodiffer_test_power_x, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(2^x)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 1.3863, 0.001);
}

TEST(autodiffer_test_exp, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(exp(x))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 2.71828, 0.001);
}

TEST(autodiffer_test_complex2, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(exp((sin((2*x)/3))/(x^2)))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, -1.322912, 0.001);
}

TEST(autodiffer_test_complex3, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(2^((sin((2*x)/3))/(x^2)))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, -0.75849, 0.001);
}

TEST(autodiffer_tes_xx, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(x^x)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 6.772588, 0.001);
}
