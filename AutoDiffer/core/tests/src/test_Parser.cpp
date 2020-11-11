/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

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
    parser.Init(seeds);
    
    ADValue<int> res = parser.Run();
    EXPECT_EQ(res.val(), 512);
    EXPECT_EQ(res.dval(), 192);
}

TEST(parser_test2, int){
    std::string equation = "((((x+5)^3)+((x+2)^4))^2)";
    Parser<int> parser(equation);

    ADValue<int> seed_value(/*value=*/7, /*seed=*/1);
    std::pair<std::string, ADValue<int>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<int>>> seeds = { seed };
    parser.Init(seeds);
    
    ADValue<int> res = parser.Run();
    EXPECT_EQ(res.val(), 68707521);
    EXPECT_EQ(res.dval(), 55503144);
}

TEST(parser_negation, int){
    std::string equation = "(-x)";
    Parser<int> parser(equation);

    ADValue<int> seed_value(/*value=*/7, /*seed=*/1);
    std::pair<std::string, ADValue<int>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<int>>> seeds = { seed };
    parser.Init(seeds);
    
    ADValue<int> res = parser.Run();
    EXPECT_EQ(res.val(), -7);
    EXPECT_EQ(res.dval(), -1);
}

TEST(parser_test_float, float){
    std::string equation = "((x+4.2)^2.0)";
    Parser<float> parser(equation);

    ADValue<float> seed_value(/*value=*/2.4, /*seed=*/1.0);
    std::pair<std::string, ADValue<float>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<float>>> seeds = { seed };
    parser.Init(seeds);
    
    ADValue<float> res = parser.Run();
    EXPECT_NEAR(res.val(), 43.56, 0.001);
    EXPECT_NEAR(res.dval(), 13.2, 0.001);
}


TEST(parser_test_double, double){
    std::string equation = "((x^1.4)+3.7)";
    Parser<double> parser(equation);

    ADValue<double> seed_value(/*value=*/1.9, /*seed=*/1.0);
    std::pair<std::string, ADValue<double>> seed("x", seed_value);
    std::vector<std::pair<std::string, ADValue<double>>> seeds = { seed };
    parser.Init(seeds);
    
    ADValue<double> res = parser.Run();
    EXPECT_NEAR(res.val(), 6.15615, 0.001);
    EXPECT_NEAR(res.dval(), 1.8098, 0.001);
}
