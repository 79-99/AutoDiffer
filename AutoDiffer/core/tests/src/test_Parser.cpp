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
