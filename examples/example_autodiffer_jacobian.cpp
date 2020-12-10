/**
 * @file    example_autodiffer_vector.cpp
 * @brief   Demonstrates the used of the
 *          templated AutoDiffer class to calculate
 *          the jacobian of a set vector functions.
 *
 *    
 * To run this example run `make` in this directory, followed by `./example_autodiffer_vector`
 *
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#include "../AutoDiffer/include/AutoDiffer.hpp"

/**
 * For this example we will consider the follow three equations of x and y:
 * 
 * f1(x,y) = x + y
 * f2(x,y) = sin(x)^2
 * f3(x,y) = exp(y/3)
 * 
 * We can manually calculate the Jacobian to be the following 3 x 2 matrix.
 * 
 * J = [[       1                1       ]
 *      [ 2*sin(x)cos(x)         0       ]
 *      [      0           1/3*exp(y/3)  ]].
 * 
 * Lets say we want to evaluate the functions and the Jacobian at x = -1, y = 2.
 * This gives the following function values:
 * 
 * f1(-1,2) = 1
 * f2(-1,2) = sin(-1)^2 \approx 0.708073
 * f3(-1,2) = exp(2/3) \approx 1.947734
 * 
 * And the Jacobian values of:
 * J = [[       1                  1       ]
 *      [ 2*sin(-1)cos(-1)         0       ]
 *      [      0             1/3*exp(2/3)  ]].
 * 
 * which is approximately:
 * J = [[       1           1       ]
 *      [ -0.909297         0       ]
 *      [      0          0.649245  ]].
 * 
 * Now we can verify that this is what we get when we run the AutoDiffer.
 */

int main() {
    AutoDiffer<double> ad;

    // Order of the values matters here! The first entry must also be the first
    // value that SetSeedVector is called with.
    std::vector<double> x_seed = { 1, 0 };
    std::vector<double> y_seed = { 0, 1 };
    
    // Set x and y seeds in based on the above vectors.
    ad.SetSeedVector("x", -1, x_seed);
    ad.SetSeedVector("y", 2, y_seed);
    
    // Create our vector of functions.
    std::vector<std::string> functions = {
        "(x+y)",
        "((sin(x))^2)",
        "(exp(y/3))"
    };

    // We will run derive on a vector of 3 functions.
    std::vector<std::pair<Status, ADValue<double>>> res = ad.Derive(functions);

    // This is we manually calculated the function values to be.
    std::vector<double> expected_values = { 1., 0.708073, 1.947734};
    
    // This is we manually calculated the jacobian values to be.
    std::vector<std::vector<double>> expected_jacobs = { 
        { 1, 1 },
        { -0.909297, 0 },
        { 0, 0.649245 },
    };

    // Check that our values and jacobians match.
    for (int i = 0; i < 3; ++i) {
        std::cout << "Expected vs AutoDiffer values of function " << i << ": ";
        std::cout << expected_values[i] << " vs " << res[i].second.val() 
            << std::endl;
        for (int j = 0; j < 2; ++j) {
            std::cout << " --- Expected vs AutoDiffer values of jacobian with respect to " 
                << j << ": ";
            std::cout <<  expected_jacobs[i][j] << " vs " 
                << res[i].second.dval(j) << std::endl;
        }
    }
    return 0;
}
