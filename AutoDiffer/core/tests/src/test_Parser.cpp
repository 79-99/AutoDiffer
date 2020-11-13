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
#include "test_vars.h"

void Parser_testcheck(){
    printf("Starting Parser tests...\n");
}

TEST(parser_test, int){
    std::string equation = "((x+5)^3)";
    Parser<int> parser(equation);

    ADValue<int> seed_value(/*value=*/3, /*seed=*/1);
    std::pair<std::string, ADValue<int>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<int>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<int>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<int> output = res.second;
    EXPECT_EQ(output.val(), 512);
    EXPECT_EQ(output.dval(), 192);
}

TEST(parser_test2, int){
    std::string equation = "((((x+5)^3)+((x+2)^4))^2)";
    Parser<int> parser(equation);

    ADValue<int> seed_value(/*value=*/7, /*seed=*/1);
    std::pair<std::string, ADValue<int>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<int>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<int>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<int> output = res.second;
    EXPECT_EQ(output.val(), 68707521);
    EXPECT_EQ(output.dval(), 55503144);
}

TEST(parser_negation, int){
    std::string equation = "(-x)";
    Parser<int> parser(equation);

    ADValue<int> seed_value(/*value=*/7, /*seed=*/1);
    std::pair<std::string, ADValue<int>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<int>>> seeds = { seed };
    ASSERT_EQ(parser.Init(seeds).code, ReturnCode::success);
    
    std::pair<Status,ADValue<int>> res = parser.Run();
    ASSERT_EQ(res.first.code, ReturnCode::success);

    ADValue<int> output = res.second;
    EXPECT_EQ(output.val(), -7);
    EXPECT_EQ(output.dval(), -1);
}

TEST(parser_sin, float){
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

TEST(parser_test_float, float){
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


TEST(parser_test_double, double){
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
