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
#include "AutoDiffer.hpp"
#include "Parser.hpp"
#include "test_vars.h"

void All_testcheck(){
    printf("Starting ADNode Library tests...\n");
}

/*
 *
 * 
 * ADValue TESTS
 * 
 * 
*/

TEST(Getter,int){
    int value = 3;
    int seed = 7;
    ADValue<int> x1(value,seed);

    /* test getters */
    EXPECT_EQ(x1.val(),value);  // note: EXECT_EQ used only for integers
    EXPECT_EQ(x1.dval(),seed);
}

TEST(Getter,float){
    float value = 9.8f;
    float seed = 1.0f;
    ADValue<float> x(value,seed);

    /* test getters */
    EXPECT_NEAR(x.val(), value, DTOL);
    EXPECT_NEAR(x.dval(), seed, DTOL);
}

TEST(Getter,double){
    double value = 9.8;
    double seed = 1.0;
    ADValue<double> x(value,seed);

    /* test getters */
    EXPECT_NEAR(x.val(), value, DTOL);
    EXPECT_NEAR(x.dval(), seed, DTOL);
}

TEST(Setter,int){
    int value = 2;
    int seed = 1;
    ADValue<int> x(value,seed);

    /* test getters */
    x.setval(3);
    EXPECT_EQ(x.val(), 3);
}

TEST(Setter,float){
    float value = 1.8f;
    float seed = 1.2f;
    ADValue<float> x(value,seed);

    /* test getters */
    x.setval(3.3);
    EXPECT_NEAR(x.val(), 3.3, 1E-6);
}

TEST(Setter,double){
    double value = 1.8;
    double seed = 1.2;
    ADValue<double> x(value,seed);

    /* test getters */
    x.setval(3.3);
    EXPECT_NEAR(x.val(), 3.3, 1E-6);
}

TEST(Operators,Add_double){
    double seed1 = 1.9;
    double seed2 = 4.4;

    ADValue<double> x1(1.0,seed1);
    ADValue<double> x2(2.0,seed2);

    /* add operator */
    ADValue<double> c = x1 + x2;

    EXPECT_NEAR(c.val(), 3.0, 1E-6);
    EXPECT_NEAR(c.dval(), 6.3, 1E-6);
}

/*
 *
 * 
 * ADNode TESTS
 * 
 * 
*/

TEST(adnode_float, float){
    float value = 3;
    float seed = 1;
    ADValue<float> x1(value, seed);

    float value2 = 5;
    float seed2 = 0;
    ADValue<float> v1(value2, seed2);

    ADNode<float> node1(x1, v1, Operation::addition);
    ADValue<float> v2 = node1.Evaluate();
    EXPECT_EQ(v2.val(), 8);
    EXPECT_EQ(v2.dval(), 1);

    float value3 = 3;
    float seed3 = 0;
    ADValue<float> v3(value3, seed3);

    ADNode<float> node2(v2, v3, Operation::power);
    ADValue<float> v4 = node2.Evaluate();

    EXPECT_EQ(v4.val(), 512);
    EXPECT_EQ(v4.dval(), 192);

    ADNode<float> node3(x1, v1, Operation::subtraction);
    ADValue<float> v5 = node3.Evaluate();
    EXPECT_EQ(v5.val(), -2);
    EXPECT_EQ(v5.dval(), 1);

    // Multiplication and division tests for float case
    ADNode<float> node4(x1, v2, Operation::multiplication);
    ADValue<float> v6 = node4.Evaluate();
    EXPECT_EQ(v6.val(), 24);
    EXPECT_EQ(v6.dval(), 11);

    float value7 = 3;
    float seed7 = 7;
    ADValue<float> v7(value7,seed7);

    ADNode<float> node5(x1, v7, Operation::division);
    ADValue<float> v8 = node5.Evaluate();
    EXPECT_EQ(v8.val(), 1);
    EXPECT_EQ(v8.dval(), -2);

}

TEST(adnode_double, double){
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
    EXPECT_NEAR(v4.dval(), -480.9036001769, 1e-6);

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

/*
 *
 * 
 * PARSER TESTS
 * 
 * 
*/

TEST(parser_test_basic, float){
    std::string equation = "((x+5)^3)";
    Parser<float> parser(equation);

    ADValue<float> seed_value(/*value=*/3, /*seed=*/1);
    std::pair<std::string, ADValue<float>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<float>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<float> output = res.second;
    EXPECT_EQ(output.val(), 512);
    EXPECT_EQ(output.dval(), 192);
}

TEST(parser_test_nested, float){
    std::string equation = "((((x+5)^3)+((x+2)^4))^2)";
    Parser<float> parser(equation);

    ADValue<float> seed_value(/*value=*/7, /*seed=*/1);
    std::pair<std::string, ADValue<float>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<float>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<float> output = res.second;
    EXPECT_EQ(output.val(), 68707521);
    EXPECT_EQ(output.dval(), 55503144);
}

TEST(parser_test_negation, float){
    std::string equation = "(-x)";
    Parser<float> parser(equation);

    ADValue<float> seed_value(/*value=*/7, /*seed=*/1);
    std::pair<std::string, ADValue<float>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<float>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<float> output = res.second;
    EXPECT_EQ(output.val(), -7);
    EXPECT_EQ(output.dval(), -1);
}

TEST(parser_test_sin, float){
    std::string equation = "(3+(sin(x)))";
    Parser<float> parser(equation);

    ADValue<float> seed_value(/*value=*/M_PI/6, /*seed=*/1);
    std::pair<std::string, ADValue<float>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<float>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<float> output = res.second;
    EXPECT_NEAR(output.val(), 3.5, 0.001);
    EXPECT_NEAR(output.dval(), 0.866, 0.001);
}

TEST(parser_test_float_power, float){
    std::string equation = "((x+4.2)^2.0)";
    Parser<float> parser(equation);

    ADValue<float> seed_value(/*value=*/2.4, /*seed=*/1.0);
    std::pair<std::string, ADValue<float>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);

    std::pair<Status,ADValue<float>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<float> output = res.second;
    EXPECT_NEAR(output.val(), 43.56, 0.001);
    EXPECT_NEAR(output.dval(), 13.2, 0.001);
}


TEST(parser_test_double_power, double){
    std::string equation = "((x^1.4)+3.7)";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);

    std::pair<Status,ADValue<double>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<double> output = res.second;
    EXPECT_NEAR(output.val(), 6.15615, 0.001);
    EXPECT_NEAR(output.dval(), 1.8098, 0.001);
}

TEST(parser_test_unbalanced_paren, double){
    std::string equation = "((x^1.4)+3.7";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::parse_error);
}

TEST(parser_test_invalid_unary, double){
    std::string equation = "((x-)+3.7)";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);

    std::pair<Status,ADValue<double>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
}

TEST(parser_test_invalid_binary, double){
    std::string equation = "((+x)+3.7)";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    std::pair<Status,ADValue<double>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
}

TEST(parser_test_incoherent_short, double){
    std::string equation = "(ln(x+3.7))";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    std::pair<Status,ADValue<double>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
}

TEST(parser_test_incoherent_med, double){
    std::string equation = "(log(x+3.7))";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    std::pair<Status,ADValue<double>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
}

TEST(parser_test_incoherent_long, double){
    std::string equation = "(function(x+3.7))";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    std::pair<Status,ADValue<double>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
}
/*
 *
 * 
 * AutoDiffer TESTS
 * 
 * 
*/

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

TEST(autodiffer_test_xx, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, double> res = ad.Derive("(x^x)");
    ASSERT_EQ(res.first.code, ReturnCode::success);
    EXPECT_NEAR(res.second, 6.772588, 0.001);
}


