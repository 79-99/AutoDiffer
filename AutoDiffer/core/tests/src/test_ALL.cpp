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

// TEST(Getter,int){
//     int value = 3;
//     int seed = 7;
//     ADValue<int> x1(value,seed);

//     /* test getters */
//     EXPECT_EQ(x1.val(),value);  // note: EXECT_EQ used only for integers
//     EXPECT_EQ(x1.dval(0),seed);
// }

// TEST(Getter,float){
//     float value = 9.8f;
//     float seed = 1.0f;
//     ADValue<float> x(value,seed);

//     /* test getters */
//     EXPECT_NEAR(x.val(), value, DTOL);
//     EXPECT_NEAR(x.dval(0), seed, DTOL);
// }

// TEST(Getter,double){
//     double value = 9.8;
//     double seed = 1.0;
//     ADValue<double> x(value,seed);

//     /* test getters */
//     EXPECT_NEAR(x.val(), value, DTOL);
//     EXPECT_NEAR(x.dval(0), seed, DTOL);
// }

// TEST(Setter,int){
//     int value = 2;
//     int seed = 1;
//     ADValue<int> x(value,seed);

//     /* test getters */
//     x.setval(3);
//     EXPECT_EQ(x.val(), 3);
// }

// TEST(Setter,float){
//     float value = 1.8f;
//     float seed = 1.2f;
//     ADValue<float> x(value,seed);

//     /* test getters */
//     x.setval(3.3);
//     EXPECT_NEAR(x.val(), 3.3, 1E-6);
// }

// TEST(Setter,double){
//     double value = 1.8;
//     double seed = 1.2;
//     ADValue<double> x(value,seed);

//     /* test getters */
//     x.setval(3.3);
//     EXPECT_NEAR(x.val(), 3.3, 1E-6);
// }

// TEST(Operators,Add_double){
//     double seed1 = 1.9;
//     double seed2 = 4.4;

//     ADValue<double> x1(1.0,seed1);
//     ADValue<double> x2(2.0,seed2);

//     /* add operator */
//     ADValue<double> c = x1 + x2;

//     EXPECT_NEAR(c.val(), 3.0, 1E-6);
//     EXPECT_NEAR(c.dval(0), 6.3, 1E-6);
// }

// /*
//  *
//  * 
//  * ADNode TESTS
//  * 
//  * 
// */

// TEST(adnode_float, float){
//     float value = 3;
//     float seed = 1;
//     ADValue<float> x1(value, seed);

//     float value2 = 5;
//     float seed2 = 0;
//     ADValue<float> v1(value2, seed2);

//     ADNode<float> node1(x1, v1, Operation::addition);
//     ADValue<float> v2 = node1.Evaluate();
//     EXPECT_EQ(v2.val(), 8);
//     EXPECT_EQ(v2.dval(0), 1);

//     float value3 = 3;
//     float seed3 = 0;
//     ADValue<float> v3(value3, seed3);

//     ADNode<float> node2(v2, v3, Operation::power);
//     ADValue<float> v4 = node2.Evaluate();

//     EXPECT_EQ(v4.val(), 512);
//     EXPECT_EQ(v4.dval(0), 192);

//     ADNode<float> node3(x1, v1, Operation::subtraction);
//     ADValue<float> v5 = node3.Evaluate();
//     EXPECT_EQ(v5.val(), -2);
//     EXPECT_EQ(v5.dval(0), 1);

//     // Multiplication and division tests for float case
//     ADNode<float> node4(x1, v2, Operation::multiplication);
//     ADValue<float> v6 = node4.Evaluate();
//     EXPECT_EQ(v6.val(), 24);
//     EXPECT_EQ(v6.dval(0), 11);

//     float value7 = 3;
//     float seed7 = 7;
//     ADValue<float> v7(value7,seed7);

//     ADNode<float> node5(x1, v7, Operation::division);
//     ADValue<float> v8 = node5.Evaluate();
//     EXPECT_EQ(v8.val(), 1);
//     EXPECT_EQ(v8.dval(0), -2);

// }

// TEST(adnode_double, double){
//     // Defining vals to start with 
//     double value = 3.2;
//     double seed = 1.1;
//     ADValue<double> x1(value, seed);

//     double value2 = 5.8;
//     double seed2 = -2.2;
//     ADValue<double> v1(value2, seed2);

//     // Addition, subtraction, powers
//     ADNode<double> node1(x1, v1, Operation::addition);
//     ADValue<double> v2 = node1.Evaluate();
//     EXPECT_NEAR(v2.val(), 9, 1e-6);
//     EXPECT_NEAR(v2.dval(0), -1.1, 1e-6);

//     ADNode<double> node2(x1, v1, Operation::subtraction);
//     ADValue<double> v3 = node2.Evaluate();
//     EXPECT_NEAR(v3.val(), -2.6, 1e-6);
//     EXPECT_NEAR(v3.dval(0), 3.3, 1e-6);

//     ADNode<double> node3(x1, v1, Operation::power);
//     ADValue<double> v4 = node3.Evaluate();
//     EXPECT_NEAR(v4.val(), pow(3.2,5.8), 1e-6);
//     EXPECT_NEAR(v4.dval(0), -480.9036001769, 1e-6);

//     // Multiplication and division tests
//     ADNode<double> node4(x1, v1, Operation::multiplication);
//     ADValue<double> v5 = node4.Evaluate();
//     EXPECT_NEAR(v5.val(), 18.56, 1e-6);
//     EXPECT_NEAR(v5.dval(0), -.66, 1e-6);

//     ADNode<double> node5(x1, v1, Operation::division);
//     ADValue<double> v6 = node5.Evaluate();
//     EXPECT_NEAR(v6.val(), 3.2/5.8, 1e-6);
//     EXPECT_NEAR(v6.dval(0), 0.3989298, 1e-6);

//     // Trig and exp tests
//     ADNode<double> node6(v2, v2, Operation::sin);
//     ADValue<double> v7 = node6.Evaluate();
//     EXPECT_NEAR(v7.val(), sin(9), 1e-6);
//     EXPECT_NEAR(v7.dval(0), cos(9)*v2.dval(0), 1e-6);

//     ADNode<double> node7(v2, v2, Operation::exp);
//     ADValue<double> v8 = node7.Evaluate();
//     EXPECT_NEAR(v8.val(), exp(9), 1e-6);
//     EXPECT_NEAR(v8.dval(0), exp(9)*-1.1, 1e-6);

//     ADNode<double> node8(v2, v2, Operation::cos);
//     ADValue<double> v9 = node8.Evaluate();
//     EXPECT_NEAR(v9.val(), cos(9), 1e-6);
//     EXPECT_NEAR(v9.dval(0), -sin(9)*v2.dval(0), 1e-6);

//     ADNode<double> node9(v2, v2, Operation::tan);
//     ADValue<double> v10 = node9.Evaluate();
//     EXPECT_NEAR(v10.val(), tan(9), 1e-6);
//     EXPECT_NEAR(v10.dval(0), -1.3250484, 1e-6);

// }

// /*
//  *
//  * 
//  * PARSER TESTS
//  * 
//  * 
// */

// TEST(parser_test_basic, float){
//     std::string equation = "((x+5)^3)";
//     Parser<float> parser(equation);

//     ADValue<float> seed_value(/*value=*/3, /*seed=*/1);
//     std::pair<std::string, ADValue<float>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
//     std::pair<Status,ADValue<float>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<float> output = res.second;
//     EXPECT_EQ(output.val(), 512);
//     EXPECT_EQ(output.dval(0), 192);
// }

// TEST(parser_test_nested, float){
//     std::string equation = "((((x+5)^3)+((x+2)^4))^2)";
//     Parser<float> parser(equation);

//     ADValue<float> seed_value(/*value=*/7, /*seed=*/1);
//     std::pair<std::string, ADValue<float>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
//     std::pair<Status,ADValue<float>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<float> output = res.second;
//     EXPECT_EQ(output.val(), 68707521);
//     EXPECT_EQ(output.dval(0), 55503144);
// }

// TEST(parser_test_negation, float){
//     std::string equation = "(-x)";
//     Parser<float> parser(equation);

//     ADValue<float> seed_value(/*value=*/7, /*seed=*/1);
//     std::pair<std::string, ADValue<float>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
//     std::pair<Status,ADValue<float>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<float> output = res.second;
//     EXPECT_EQ(output.val(), -7);
//     EXPECT_EQ(output.dval(0), -1);
// }

// TEST(parser_test_sin, float){
//     std::string equation = "(3+(sin(x)))";
//     Parser<float> parser(equation);

//     ADValue<float> seed_value(/*value=*/M_PI/6, /*seed=*/1);
//     std::pair<std::string, ADValue<float>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
//     std::pair<Status,ADValue<float>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<float> output = res.second;
//     EXPECT_NEAR(output.val(), 3.5, 0.001);
//     EXPECT_NEAR(output.dval(0), 0.866, 0.001);
// }

// TEST(parser_test_cos, float){
//     std::string equation = "(cos(x))";
//     Parser<float> parser(equation);

//     ADValue<float> seed_value(/*value=*/6, /*seed=*/1);
//     std::pair<std::string, ADValue<float>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
//     std::pair<Status,ADValue<float>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<float> output = res.second;
//     EXPECT_NEAR(output.val(), 0.96017, 0.001);
//     EXPECT_NEAR(output.dval(0), 0.27942, 0.001);
// }

// TEST(parser_test_float_power, float){
//     std::string equation = "((x+4.2)^2.0)";
//     Parser<float> parser(equation);

//     ADValue<float> seed_value(/*value=*/2.4, /*seed=*/1.0);
//     std::pair<std::string, ADValue<float>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);

//     std::pair<Status,ADValue<float>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<float> output = res.second;
//     EXPECT_NEAR(output.val(), 43.56, 0.001);
//     EXPECT_NEAR(output.dval(0), 13.2, 0.001);
// }


// TEST(parser_test_double_power, double){
//     std::string equation = "((x^1.4)+3.7)";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);

//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::success);

//     ADValue<double> output = res.second;
//     EXPECT_NEAR(output.val(), 6.15615, 0.001);
//     EXPECT_NEAR(output.dval(0), 1.8098, 0.001);
// }

// TEST(parser_test_unbalanced_paren, double){
//     std::string equation = "((x^1.4)+3.7";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::parse_error);
// }

// TEST(parser_test_unbalanced_paren2, double){
//     std::string equation = "((x^1.4)+3.7))";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::parse_error);
// }

// TEST(parser_test_invalid_unary, double){
//     std::string equation = "((x-)+3.7)";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);

//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
// }

// TEST(parser_test_invalid_binary, double){
//     std::string equation = "((+x)+3.7)";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
// }

// TEST(parser_test_incoherent_short, double){
//     std::string equation = "(ln(x+3.7))";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
// }

// TEST(parser_test_incoherent_med, double){
//     std::string equation = "(log(x+3.7))";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
// }

// TEST(parser_test_incoherent_long, double){
//     std::string equation = "(function(x+3.7))";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
// }

// TEST(parser_test_invalid_sin, double){
//     std::string equation = "(sin(y))";
//     Parser<double> parser(equation);

//     ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
//     std::pair<std::string, ADValue<double>> seed("x", seed_value);
//     std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
//     ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
//     std::pair<Status,ADValue<double>> res = parser.Run();
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
// }

// /*
//  *
//  * 
//  * AutoDiffer TESTS
//  * 
//  * 
// */

// TEST(autodiffer_test_basic, float){
//     AutoDiffer<float> ad;
//     ad.SetSeed("x", /*value=*/7, /*dval=*/1);

//     std::pair<Status, ADValue<float>> res = ad.Derive("((x+5)^3)");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_EQ(res.second.dval(0), 432);
// }

// TEST(autodiffer_test_basic_division, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/7, /*dval=*/1);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(x/3)");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 0.3333, 0.001);
// }

// TEST(autodiffer_test_tan, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(tan(x/3))");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 0.37329, 0.001);
// }

// TEST(autodiffer_test_complex1, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("((sin((2*x)/3))/(x^2))");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.712814, 0.001);
// }

// TEST(autodiffer_test_power_x, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(2^x)");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 1.3863, 0.001);
// }

// TEST(autodiffer_test_exp, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(exp(x))");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 2.71828, 0.001);
// }

// TEST(autodiffer_test_complex2, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(exp((sin((2*x)/3))/(x^2)))");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -1.322912, 0.001);
// }

// TEST(autodiffer_test_complex3, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(2^((sin((2*x)/3))/(x^2)))");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.75849, 0.001);
// }

// TEST(autodiffer_test_xx, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(x^x)");
//     ASSERT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 6.772588, 0.001);
// }

// TEST(autodiffer_test_fails_init_broken_parens, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("((x^1.4)+3.7");
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
//     ASSERT_EQ(res.first.message, "Unbalanced parentheses");
// }

// TEST(autodiffer_test_fails_run_invalid, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("((x-)+3.7)");
//     ASSERT_EQ(res.first.code, ReturnCode::parse_error);
//     ASSERT_EQ(res.first.message, "Binary operation requires LHS and RHS");
// }

// TEST(autodiffer_test_fails_wrong_var_name, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(y^2)");
//     EXPECT_EQ(res.first.code, ReturnCode::parse_error);
//     EXPECT_EQ(res.first.message, "Key not found: y");
// }

// TEST(autodiffer_test_fails_wrong_var_name2, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(2^z)");
//     EXPECT_EQ(res.first.code, ReturnCode::parse_error);
//     EXPECT_EQ(res.first.message, "Key not found: z");
// }

// TEST(autodiffer_test_fails_wrong_var_name3, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("((sin(4*(x+2)))^z)");
//     EXPECT_EQ(res.first.code, ReturnCode::parse_error);
//     EXPECT_EQ(res.first.message, "Key not found: z");
// }

// TEST(autodiffer_test_negation_exp, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(exp(-x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.135335, 0.001);
// }

// TEST(autodiffer_test_negation_trig, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(sin(-x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 0.41614, 0.001);
// }

// TEST(autodiffer_test_nested_trig, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(sin(cos(x)))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.83169, 0.001);
// }

// TEST(autodiffer_test_nested_trig_exp, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(tan(exp(sin(cos(x)))))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.90000, 0.001);
// }

// TEST(autodiffer_test_nested_trig_exp_binary, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("((-2)*((tan(exp(sin(cos(x)))))+x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.2, 0.001);
// }

// TEST(autodiffer_test_nested_trig_complex_in, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(tan(exp(sin(cos((x^(-x))+2)))))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 0.205133, 0.001);
// }


// TEST(autodiffer_test_nested_trig_exp_div, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("(((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 2.31039, 0.001);
// }

// TEST(autodiffer_test_nested_trig_exp_div_twice, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive("((((-2)/(x^x))*((tan(exp(sin(cos(x)))))+x))/x)");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), 1.50372, 0.001);
// }

// TEST(autodiffer_hayoun, double){
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

//     std::pair<Status, ADValue<double>> res = ad.Derive(
//         "((exp(sin(x)))-((cos(x^0.5))*(sin((((cos(x))^2)+(x^2))^0.5))))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.dval(0), -0.63952, 0.001);
// }

// /*
//  *
//  * 
//  * AutoDiffer TESTS (vector)
//  * 
//  * 
// */

// TEST(autodiffer_vector_single_func, double){
//     AutoDiffer<double> ad;
//     std::vector<double> x_seed = { 1, 0 };
//     std::vector<double> y_seed = { 0, 1 };
//     ad.SetSeedVector("x", /*value=*/3., /*dvals=*/x_seed);
//     ad.SetSeedVector("y", /*value=*/-1., /*dvals=*/y_seed);

//     std::pair<Status, ADValue<double>> res = ad.Derive(
//         "((x^2)+(y^2))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 10, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 6, 0.001);
//     EXPECT_NEAR(res.second.dval(1), -2, 0.001);
// }

// TEST(autodiffer_vector_single_func_trig, double){
//     AutoDiffer<double> ad;
//     std::vector<double> x_seed = { 1, 0 };
//     std::vector<double> y_seed = { 0, 1 };
//     ad.SetSeedVector("t", /*value=*/-1., /*dvals=*/x_seed);
//     ad.SetSeedVector("q", /*value=*/5., /*dvals=*/y_seed);

//     std::pair<Status, ADValue<double>> res = ad.Derive(
//         "(((cos(t))^2)*((tan(q))+4))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 0.1808, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.563296, 0.001);
//     EXPECT_NEAR(res.second.dval(1), 3.628029, 0.001);
// }

// TEST(autodiffer_vector_mult_func, double){
//     AutoDiffer<double> ad;
//     std::vector<double> x_seed = { 1, 0 };
//     std::vector<double> y_seed = { 0, 1 };
//     ad.SetSeedVector("x", /*value=*/-1., /*dvals=*/x_seed);
//     ad.SetSeedVector("y", /*value=*/-3., /*dvals=*/y_seed);

//     std::pair<Status, ADValue<double>> res_f1 = ad.Derive(
//         "((sin(x))*(exp(y)))");
//     std::pair<Status, ADValue<double>> res_f2 = ad.Derive(
//         "((x^2)*y)");
    
//     EXPECT_EQ(res_f1.first.code, ReturnCode::success);
//     EXPECT_NEAR(res_f1.second.val(), -0.04189, 0.001);
//     EXPECT_NEAR(res_f1.second.dval(0), 0.0269, 0.001);
//     EXPECT_NEAR(res_f1.second.dval(1), -0.04189, 0.001);

//     EXPECT_EQ(res_f2.first.code, ReturnCode::success);
//     EXPECT_NEAR(res_f2.second.val(), -3, 0.001);
//     EXPECT_NEAR(res_f2.second.dval(0), 6, 0.001);
//     EXPECT_NEAR(res_f2.second.dval(1), 1, 0.001);
// }

// TEST(autodiffer_arcsin_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/-0.5, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), -0.523599, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 1.1547, 0.001);
// }

// TEST(autodiffer_arccos_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/-0.4, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(arccos(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 1.98231, 0.001);
//     EXPECT_NEAR(res.second.dval(0), -1.091, 0.001);
// }

// TEST(autodiffer_arctan_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/4, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(arctan(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 1.32582, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.05882, 0.001);
// }

// TEST(autodiffer_sinh_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/-0.2, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), -0.201366, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 1.02007, 0.001);
// }

// TEST(autodiffer_cosh_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1.5, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(cosh(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 2.35241, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 2.1293, 0.001);
// }

// TEST(autodiffer_tanh_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.63, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(tanh(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 0.558052, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.688578, 0.001);
// }

// TEST(autodiffer_logistic_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.92, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 0.715042, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.203757, 0.001);
// }

// TEST(autodiffer_log_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.4321, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(log_3.4_(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), -0.68566, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 1.8911, 0.001);
// }

// TEST(autodiffer_sqrt_simple, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/5.3, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(sqrt(x))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 2.30217, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.217186, 0.001);
// }

// TEST(autodiffer_arcsin_of_func, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.9, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(arcsin(x^2))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 0.944152, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 3.06942, 0.001);
// }

// TEST(autodiffer_sinh_of_func, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.01, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(sinh(x^2))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 0.001, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.02, 0.001);
// }

// TEST(autodiffer_logistic_of_func, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/1.6, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(logistic(x^2))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), 0.92824, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 0.213147, 0.001);
// }

// TEST(autodiffer_log_of_func, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.3, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(log_2.33_(x^2))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), -2.8467, 0.001);
//     EXPECT_NEAR(res.second.dval(0), 7.88145, 0.001);
// }

// TEST(autodiffer_basic_nop, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(x)");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_EQ(res.second.val(), 0.444);
//     EXPECT_EQ(res.second.dval(0), 1);
// }

// TEST(autodiffer_const_nop, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(5)");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_EQ(res.second.val(), 5);
//     EXPECT_EQ(res.second.dval(0), 0);
// }

// TEST(autodiffer_const_nop_long, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(6160)");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_EQ(res.second.val(), 6160);
//     EXPECT_EQ(res.second.dval(0), 0);
// }

// TEST(autodiffer_sin_const, double) {
//     AutoDiffer<double> ad;
//     ad.SetSeed("x", /*value=*/0.444, /*dval=*/1.);
//     std::pair<Status, ADValue<double>> res = ad.Derive("(sin(-1))");
//     EXPECT_EQ(res.first.code, ReturnCode::success);
//     EXPECT_NEAR(res.second.val(), -0.8414, 0.001);
//     EXPECT_EQ(res.second.dval(0), 0);
// }

/*************************************/
/* Tests CL */
/*************************************/

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