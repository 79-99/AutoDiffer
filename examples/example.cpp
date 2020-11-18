/**
 * @file    example.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer class.
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#include "../AutoDiffer/install/include/AutoDiffer.hpp"


int main(){
    AutoDiffer<int> ad;
    ad.SetSeed("x", /*value=*/7, /*dval=*/1);
    std::pair<Status, int> res = ad.Derive("((x+5)^3)");
    
    std::cout << "AutoDiffer of function f(x) = ((x+5)^3) at x=7" << std::endl;
    std::cout << "Expected Result = 432; AutoDiffer Result = " << res.second 
        << std::endl;

    return 0;
}