/* system header files */
#include <stdlib.h>
#include <stdio.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADValue.hpp"
#include "ADNode.hpp"
#include "test_vars.h"

void ADNode_testcheck(){
    printf("Starting ADNode Library tests...\n");
}

TEST(functionality, int){
    int value = 3;
    int seed = 1;
    ADValue<int> x1(value, seed);

    int value2 = 5;
    int seed2 = 0;
    ADValue<int> v1(value2, seed2);

    ADNode<int> node1(x1, v1, Operation::addition);
    ADValue<int> v2 = node1.Evaluate();
    EXPECT_EQ(v2.val(), 8);
    EXPECT_EQ(v2.dval(), 1);

    int value3 = 3;
    int seed3 = 0;
    ADValue<int> v3(value3, seed3);

    ADNode<int> node2(v2, v3, Operation::power);
    ADValue<int> v4 = node2.Evaluate();

    EXPECT_EQ(v4.val(), 512);
    EXPECT_EQ(v4.dval(), 192);
}
