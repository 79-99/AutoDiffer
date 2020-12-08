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
 * AutoDiffer TESTS (vector)
 * 
 * 
*/

TEST(autodiffer_vector_single_func, double){
    AutoDiffer<double> ad;
    std::vector<double> x_seed = { 1, 0 };
    std::vector<double> y_seed = { 0, 1 };
    ad.SetSeedVector("x", /*value=*/3., /*dvals=*/x_seed);
    ad.SetSeedVector("y", /*value=*/-1., /*dvals=*/y_seed);

    std::pair<Status, ADValue<double>> res = ad.Derive(
        "((x^2)+(y^2))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 10, 0.001);
    EXPECT_NEAR(res.second.dval(0), 6, 0.001);
    EXPECT_NEAR(res.second.dval(1), -2, 0.001);
}

TEST(autodiffer_vector_single_func_trig, double){
    AutoDiffer<double> ad;
    std::vector<double> x_seed = { 1, 0 };
    std::vector<double> y_seed = { 0, 1 };
    ad.SetSeedVector("t", /*value=*/-1., /*dvals=*/x_seed);
    ad.SetSeedVector("q", /*value=*/5., /*dvals=*/y_seed);

    std::pair<Status, ADValue<double>> res = ad.Derive(
        "(((cos(t))^2)*((tan(q))+4))");
    EXPECT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second.val(), 0.1808, 0.001);
    EXPECT_NEAR(res.second.dval(0), 0.563296, 0.001);
    EXPECT_NEAR(res.second.dval(1), 3.628029, 0.001);
}

TEST(autodiffer_vector_mult_func, double){
    AutoDiffer<double> ad;
    std::vector<double> x_seed = { 1, 0 };
    std::vector<double> y_seed = { 0, 1 };
    ad.SetSeedVector("x", /*value=*/-1., /*dvals=*/x_seed);
    ad.SetSeedVector("y", /*value=*/-3., /*dvals=*/y_seed);

    std::pair<Status, ADValue<double>> res_f1 = ad.Derive(
        "((sin(x))*(exp(y)))");
    std::pair<Status, ADValue<double>> res_f2 = ad.Derive(
        "((x^2)*y)");
    
    EXPECT_EQ(res_f1.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f1.second.val(), -0.04189, 0.001);
    EXPECT_NEAR(res_f1.second.dval(0), 0.0269, 0.001);
    EXPECT_NEAR(res_f1.second.dval(1), -0.04189, 0.001);

    EXPECT_EQ(res_f2.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f2.second.val(), -3, 0.001);
    EXPECT_NEAR(res_f2.second.dval(0), 6, 0.001);
    EXPECT_NEAR(res_f2.second.dval(1), 1, 0.001);
}

TEST(autodiffer_vector_inverses_lots, double){
    AutoDiffer<double> ad;
    std::vector<double> x_seed = { 1, 0 };
    std::vector<double> y_seed = { 0, 1 };
    ad.SetSeedVector("x", /*value=*/.4, /*dvals=*/x_seed);
    ad.SetSeedVector("y", /*value=*/-.7, /*dvals=*/y_seed);

    std::pair<Status, ADValue<double>> res_f1 = ad.Derive(
        "((arcsin(-y))^((((arctan(5))+(arctan(x)))+((arccos(-.5))*(arccos((2*x)))))))" );
    std::pair<Status, ADValue<double>> res_f2 = ad.Derive(
        "((arccos((x+y)))^((((arctan(0))+(arctan(y)))+((arcsin(((x-y)-.2)))/(arcsin(.2))))))" );
    std::pair<Status, ADValue<double>> res_f3 = ad.Derive(
        "(((((arccos(0))-(5*(arccos(.4)))))+(arccos(-.3)))+((((arcsin(0))*(5*(arcsin(.4)))))/(arcsin((2*-.3)))))" );
    std::pair<Status, ADValue<double>> res_f4 = ad.Derive(
        "(((((arctan(100))-(5*(arctan((1/50.4))))))^(-.35))^(.23))" );
    std::pair<Status, ADValue<double>> res_f5 = ad.Derive(
        "(((((arcsin(x))/(arcsin(y)))+((arccos(x))/(arccos(y))))+((arctan(x))/(arctan((-(3*y)))))))" );

    
    EXPECT_EQ(res_f1.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f1.second.val(), 0.4543, 0.001);
    EXPECT_NEAR(res_f1.second.dval(0), .707169, 0.001);
    EXPECT_NEAR(res_f1.second.dval(1), -2.54464, 0.001);

    EXPECT_EQ(res_f2.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f2.second.val(), 22.4914, 0.001);
    EXPECT_NEAR(res_f2.second.dval(0), 98.9177, 0.001);
    EXPECT_NEAR(res_f2.second.dval(1), -213.89, 0.001);

    EXPECT_EQ(res_f3.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f3.second.val(), -2.3501121, 0.001);
    EXPECT_NEAR(res_f3.second.dval(0), 0., 0.001);
    EXPECT_NEAR(res_f3.second.dval(1), 0., 0.001);

    EXPECT_EQ(res_f4.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f4.second.val(), 0.9699095, 0.001);
    EXPECT_NEAR(res_f4.second.dval(0), 0., 0.001);
    EXPECT_NEAR(res_f4.second.dval(1), 0., 0.001);

    EXPECT_EQ(res_f5.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f5.second.val(), .301208, 0.001);
    EXPECT_NEAR(res_f5.second.dval(0), -1.10684, 0.001);
    EXPECT_NEAR(res_f5.second.dval(1), -.497205, 0.001);
}

TEST(autodiffer_vector_hyperbolics_lots, double){
    AutoDiffer<double> ad;
    std::vector<double> x_seed = { 1, 0 };
    std::vector<double> y_seed = { 0, 1 };
    ad.SetSeedVector("x", /*value=*/1.2, /*dvals=*/x_seed);
    ad.SetSeedVector("y", /*value=*/-1.3, /*dvals=*/y_seed);

    std::pair<Status, ADValue<double>> res_f1 = ad.Derive(
        "((sinh(-y))^((((tanh(5))+(tanh(x)))+((cosh(-.5))*(cosh((2*x)))))))" );
    std::pair<Status, ADValue<double>> res_f2 = ad.Derive(
        "((cosh((x+y)))^((((tanh(0))+(tanh(y)))+((sinh(((x-y)-.2)))/(sinh(.2))))))" );
    std::pair<Status, ADValue<double>> res_f3 = ad.Derive(
        "(((((cosh(0))-(5*(cosh(.4)))))+(cosh(-.3)))+((((sinh(0))*(5*(sinh(.4)))))/(sinh((2*-.3)))))" );
    std::pair<Status, ADValue<double>> res_f4 = ad.Derive(
        "(((((tanh(100))-(5*(tanh((1/50.4))))))^(-.35))^(.23))" );
    std::pair<Status, ADValue<double>> res_f5 = ad.Derive(
        "(((((sinh(x))/(sinh(y)))+((cosh(x))/(cosh(y))))+((tanh(x))/(tanh((-(3*y)))))))" );

    
    EXPECT_EQ(res_f1.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f1.second.val(), 72.9833, 0.001);
    EXPECT_NEAR(res_f1.second.dval(0), 488.351, 0.001);
    EXPECT_NEAR(res_f1.second.dval(1), -686.003, 0.001);

    EXPECT_EQ(res_f2.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f2.second.val(), 1.12536, 0.001);
    EXPECT_NEAR(res_f2.second.dval(0), -2.51313, 0.001);
    EXPECT_NEAR(res_f2.second.dval(1), -2.79277, 0.001);

    EXPECT_EQ(res_f3.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f3.second.val(), -3.360023, 0.001);
    EXPECT_NEAR(res_f3.second.dval(0), 0., 0.001);
    EXPECT_NEAR(res_f3.second.dval(1), 0., 0.001);

    EXPECT_EQ(res_f4.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f4.second.val(), 1.00844486, 0.001);
    EXPECT_NEAR(res_f4.second.dval(0), 0., 0.001);
    EXPECT_NEAR(res_f4.second.dval(1), 0., 0.001);

    EXPECT_EQ(res_f5.first.code, ReturnCode::success);
    EXPECT_NEAR(res_f5.second.val(), .864262, 0.001);
    EXPECT_NEAR(res_f5.second.dval(0), 0.00503275, 0.001);
    EXPECT_NEAR(res_f5.second.dval(1), -.235623, 0.001);
}

TEST(autodiffer_vector_in, double) {
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
    std::vector<std::string> equations;
    equations.push_back("(sin(-1))"); 
    equations.push_back("(2*(x+5))"); 
    std::vector<std::pair<Status, ADValue<double>>> res = ad.Derive(equations);
    EXPECT_EQ(res[0].first.code, ReturnCode::success);
    EXPECT_NEAR(res[0].second.val(), -0.8414, 0.001);
    EXPECT_EQ(res[0].second.dval(0), 0);
    EXPECT_EQ(res[1].first.code, ReturnCode::success);
    EXPECT_EQ(res[1].second.val(), 10.888);
    EXPECT_EQ(res[1].second.dval(0), 2);
}
