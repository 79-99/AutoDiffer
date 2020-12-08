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
 * AutoDiffer TESTS (correctness)
 * 
 * 
*/

TEST(autodiffer_test_basic, float){
    AutoDiffer<float> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    std::pair<Status, ADValue<float>> res = ad.Derive("((x+5)^3)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.dval(0), 432);
}

TEST(autodiffer_test_basic_division, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);

    std::pair<Status, ADValue<double>> res = ad.Derive("(x/3)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 0.3333, 0.001);
}

TEST(autodiffer_test_tan, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(x/3))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 0.37329, 0.001);
}

TEST(autodiffer_test_complex1, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("((sin((2*x)/3))/(x^2))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.712814, 0.001);
}

TEST(autodiffer_test_power_x, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(2^x)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 1.3863, 0.001);
}

TEST(autodiffer_test_exp, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(exp(x))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 2.71828, 0.001);
}

TEST(autodiffer_test_complex2, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(exp((sin((2*x)/3))/(x^2)))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -1.322912, 0.001);
}

TEST(autodiffer_test_complex3, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(2^((sin((2*x)/3))/(x^2)))");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.75849, 0.001);
}

TEST(autodiffer_test_xx, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(x^x)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 6.772588, 0.001);
}


TEST(autodiffer_arcsin_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.5, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.523599, 0.001);
    EXPECT_NEAR(res.second.dval(0), 1.1547, 0.001);
}

TEST(autodiffer_arccos_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.4, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arccos(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.98231, 0.001);
    EXPECT_NEAR(res.second.dval(0), -1.091, 0.001);
}

TEST(autodiffer_arctan_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/4, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arctan(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.32582, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.05882, 0.001);
}

TEST(autodiffer_sinh_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.2, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.201366, 0.001);
    EXPECT_NEAR(res.second.dval(0), 1.02007, 0.001);
}

TEST(autodiffer_cosh_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1.5, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cosh(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 2.35241, 0.001);
    EXPECT_NEAR(res.second.dval(0), 2.1293, 0.001);
}

TEST(autodiffer_tanh_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.63, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(tanh(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.558052, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.688578, 0.001);
}

TEST(autodiffer_logistic_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.92, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.715042, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.203757, 0.001);
}

TEST(autodiffer_log_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.4321, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_3.4_(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.68566, 0.001);
    EXPECT_NEAR(res.second.dval(0), 1.8911, 0.001);
}

TEST(autodiffer_sqrt_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/5.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sqrt(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 2.30217, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.217186, 0.001);
}

TEST(autodiffer_arcsin_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.9, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.944152, 0.001);
    EXPECT_NEAR(res.second.dval(0), 3.06942, 0.001);
}

TEST(autodiffer_sinh_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.01, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.001, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.02, 0.001);
}

TEST(autodiffer_logistic_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/1.6, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.92824, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.213147, 0.001);
}

TEST(autodiffer_log_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_2.33_(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -2.8467, 0.001);
    EXPECT_NEAR(res.second.dval(0), 7.88145, 0.001);
}

TEST(autodiffer_basic_nop, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(x)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), 0.444);
    EXPECT_EQ(res.second.dval(0), 1);
}

TEST(autodiffer_const_nop, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(5)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), 5);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_const_nop_long, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(6160)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), 6160);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_sin_const, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(-1))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.8414, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}


TEST(autodiffer_test_negation_exp, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(exp(-x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.135335, 0.001);
}

TEST(autodiffer_test_negation_trig, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(-x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 0.41614, 0.001);
}

TEST(autodiffer_test_nested_trig, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(cos(x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.83169, 0.001);
}

TEST(autodiffer_test_nested_trig_exp, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(exp(sin(cos(x)))))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.90000, 0.001);
}

TEST(autodiffer_test_nested_trig_exp_binary, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("((-2)*((tan(exp(sin(cos(x)))))+x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.2, 0.001);
}

TEST(autodiffer_test_nested_trig_complex_in, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(exp(sin(cos((x^(-x))+2)))))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 0.205133, 0.001);
}


TEST(autodiffer_test_nested_trig_exp_div, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 2.31039, 0.001);
}

TEST(autodiffer_test_nested_trig_exp_div_twice, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), 1.50372, 0.001);
}

TEST(autodiffer_hayoun, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive(
        "((exp(sin(x)))-((cos(x^0.5))*(sin((((cos(x))^2)+(x^2))^0.5))))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.dval(0), -0.63952, 0.001);
}
