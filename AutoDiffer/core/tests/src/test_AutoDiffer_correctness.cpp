/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <math.h>
#include <cmath>
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

TEST(autodiffer_logistic_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(0.3))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.574443, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_logistic_pos_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.92, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.715042, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.203757, 0.001);
}

TEST(autodiffer_logistic_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-1, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.268941, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.196612, 0.001);   
}

TEST(autodiffer_logistic_fcn_in, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-1, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(exp(2*x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    std::cout << "res.second.val(): " << res.second.val() << std::endl; 
    EXPECT_NEAR(res.second.val(), 0.533782, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.0673587, 0.001);   
}

TEST(autodiffer_log_simple, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.4321, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_3.4_(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.68566, 0.001);
    EXPECT_NEAR(res.second.dval(0), 1.8911, 0.001);
}

TEST(autodiffer_log_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_5.8_(3))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.624972, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_log_negative, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-2.5, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_7.8_(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success); 
    EXPECT_EQ(std::isnan(res.second.val()), 1);
}

TEST(autodiffer_sqrt_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(sqrt(5.5))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 2.34521, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_sqrt_pos_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/5.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sqrt(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 2.30217, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.217186, 0.001);
}

TEST(autodiffer_sqrt_neg_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-5.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sqrt(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(std::isnan(res.second.val()), 1);
}


TEST(autodiffer_sqrt_fcn, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-5.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sqrt(((-2)*x)/(x^2)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.614295, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.0579524, 0.001);
}

TEST(autodiffer_arcsin_of_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(0.56))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.594386, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_arcsin_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.92, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -1.16808, 0.001);
    EXPECT_NEAR(res.second.dval(0), 2.55155, 0.001);
}

TEST(autodiffer_arcsin_out_of_domain, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-5.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(std::isnan(res.second.val()), 1);
}

TEST(autodiffer_arcsin_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.9, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.944152, 0.001);
    EXPECT_NEAR(res.second.dval(0), 3.06942, 0.001);
}

TEST(autodiffer_arccos_of_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(arccos(0.56))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.976411, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_arccos_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.92, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arccos(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 2.73888, 0.001);
    EXPECT_NEAR(res.second.dval(0), -2.55155, 0.001);
}

TEST(autodiffer_arccos_out_of_domain, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-5.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arccos(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(std::isnan(res.second.val()), 1);
}

TEST(autodiffer_arccos_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.9, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arccos(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.626644, 0.001);
    EXPECT_NEAR(res.second.dval(0), -3.06942, 0.001);
}

TEST(autodiffer_arctan_of_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(arctan(0.56))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.510488, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_arctan_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.59, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arctan(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.533034, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.741785, 0.001);
}

TEST(autodiffer_arctan_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.35, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(arctan(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.121893, 0.001);
    EXPECT_NEAR(res.second.dval(0), -0.689651, 0.001);
}

TEST(autodiffer_sinh_of_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(0.56))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.589732, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_sinh_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-1.59, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -2.34991, 0.001);
    EXPECT_NEAR(res.second.dval(0), 2.55384, 0.001);
}

TEST(autodiffer_sinh_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.01, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.001, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.02, 0.001);
}


TEST(autodiffer_cosh_of_const, double) {
    AutoDiffer<double> ad;
    // ad.SetSeed("x", /*value=*/0.9, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cosh(0.73))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.27849, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_cosh_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-1.59, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cosh(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 2.55384, 0.001);
    EXPECT_NEAR(res.second.dval(0), -2.34991, 0.001);
}

TEST(autodiffer_cosh_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.18, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cosh(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.00052, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.011666, 0.001);
}

TEST(autodiffer_tanh_of_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(tanh(0.73))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.623065, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_tanh_neg_variable, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-1.59, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(tanh(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.920149, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.153325, 0.001);
}

TEST(autodiffer_tanh_of_func, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.18, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(tanh(x^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.0323887, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.359622, 0.001);
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

TEST(autodiffer_exp_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(3^(-0.5))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.57735, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);

}
TEST(autodiffer_exp_pos_dec, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(x^1.5)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.164317, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.821584, 0.001);
}

TEST(autodiffer_exp_neg_dec, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(x^(-1.35))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 5.08026, 0.001);
    EXPECT_NEAR(res.second.dval(0), -22.8612, 0.001);
}

TEST(autodiffer_exp_both_fcns, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.3, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(x^(2*x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.485593, 0.001);
    EXPECT_NEAR(res.second.dval(0), -0.198096, 0.001);
}

TEST(autodiffer_sin_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(-1))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.8414, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_sin_neg_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.429555, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.903041, 0.001);
}

TEST(autodiffer_sin_pos_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.429555, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.903041, 0.001);
}

TEST(autodiffer_sin_fcn_in, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(sin(2*(x^x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.984528, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.045961, 0.001);
}


TEST(autodiffer_cos_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(cos(1))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.540302, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_cos_neg_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cos(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.903041, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.429555, 0.001);
}

TEST(autodiffer_cos_pos_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cos(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.903041, 0.001);
    EXPECT_NEAR(res.second.dval(0), -0.429555, 0.001);
}

TEST(autodiffer_cos_fcn_in, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.42, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(cos(2*(x^x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.180506, 0.001);
    EXPECT_NEAR(res.second.dval(0), -0.181057, 0.001);
}

TEST(autodiffer_tan_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(1.73))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -6.2281, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_tan_neg_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/-0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -0.475676, 0.001);
    EXPECT_NEAR(res.second.dval(0), 1.22627, 0.001);
}

TEST(autodiffer_tan_pos_var, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.475676, 0.001);
    EXPECT_NEAR(res.second.dval(0), 1.22627, 0.001);
}

TEST(autodiffer_tan_fcn_in, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(tan(2*(x^x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 5.30292, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.231721, 0.001);
}

TEST(autodiffer_neg_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(-(-1.2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.2, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_neg_const_lots_negs, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(-(-(-(-1.2))))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.2, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_sub_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(1.99-1.2)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), .79, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_sub_const_neg, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("((-1.)-1.2)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -2.2, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_log_long, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_1.299491_(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -3.79525, 0.001);
    EXPECT_NEAR(res.second.dval(0), 10.3167, 0.001);
}

TEST(autodiffer_log_short, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(log_3_(x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -.905007, 0.001);
    EXPECT_NEAR(res.second.dval(0), 2.46011, 0.001);
}

TEST(autodiffer_div_two_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(0.45/(-0.33))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -1.36364, 0.001);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_div_by_zero, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(x/0)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(std::isnan(res.second.val()), 1);
}

TEST(autodiffer_div_num_const, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(0.217/(x^x))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.313491, 0.001);
    EXPECT_NEAR(res.second.dval(0), -0.00180186, 0.001);
}

TEST(autodiffer_div_denom_const, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("((sin(x^x))/0.209)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 3.05376, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.014655, 0.001);
}

TEST(autodiffer_div_both_fcn, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("((sin(x^x))/(tan(x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.64552, 0.001);
    EXPECT_NEAR(res.second.dval(0), -4.87286, 0.001);
}


TEST(autodiffer_negation_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(-2020)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), -2020);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_negation_fcn, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("((sin(-(x^x)))/(tan(x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), -1.64552, 0.001);
    EXPECT_NEAR(res.second.dval(0), 4.87286, 0.001);
}

TEST(autodiffer_add_two_const, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(2019+(-2020))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), -1);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_add_one_const, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("(x+2020)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), 2020.37);
    EXPECT_EQ(res.second.dval(0), 1);
}

TEST(autodiffer_add_two_fcn, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.37, /*dval=*/1.);
    std::pair<Status, ADValue<double>> res = ad.Derive("((x^x)+(logistic(2*x)))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 1.3692, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.441324, 0.001);
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
    std::pair<Status, ADValue<double>> res = ad.Derive("(5)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), 5);
    EXPECT_EQ(res.second.dval(0), 0);
}

TEST(autodiffer_const_nop_long, double) {
    AutoDiffer<double> ad;
    std::pair<Status, ADValue<double>> res = ad.Derive("(6160)");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_EQ(res.second.val(), 6160);
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
