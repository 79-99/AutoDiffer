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
 * AutoDiffer TESTS (invalid)
 * 
 * 
*/


TEST(autodiffer_test_fails_init_broken_parens_left, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("((x^1.4)+3.7");
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
    ASSERT_EQ(res.first.message, "Unbalanced parentheses -- too many \'(\'");
}

TEST(autodiffer_test_fails_init_broken_parens_right, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(x^1.4)+3.7)");
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
    ASSERT_EQ(res.first.message, "Unbalanced parentheses -- too many \')\'");
}

TEST(autodiffer_test_fails_init_no_parens, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("x+5");
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
    ASSERT_EQ(res.first.message, "No parentheses found.");
}

TEST(autodiffer_test_fails_run_invalid, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("((x-)+3.7)");
    ASSERT_EQ(res.first.code, ReturnCode::parse_error);
    ASSERT_EQ(res.first.message, "Binary operation requires LHS and RHS");
}

TEST(autodiffer_test_fails_wrong_var_name, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(y^2)");
    EXPECT_EQ(res.first.code, ReturnCode::parse_error);
    EXPECT_EQ(res.first.message, "Key not found: y");
}

TEST(autodiffer_test_fails_wrong_var_name2, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("(2^z)");
    EXPECT_EQ(res.first.code, ReturnCode::parse_error);
    EXPECT_EQ(res.first.message, "Key not found: z");
}

TEST(autodiffer_test_fails_wrong_var_name3, double){
    AutoDiffer<double> ad;
    ad.SetSeed("x", /*value=*/2., /*dval=*/1.);

    std::pair<Status, ADValue<double>> res = ad.Derive("((sin(4*(x+2)))^z)");
    EXPECT_EQ(res.first.code, ReturnCode::parse_error);
    EXPECT_EQ(res.first.message, "Key not found: z");
}

