/**
 * @file AutoDiffer.hpp
 */
#ifndef AUTODIFFER_H
#define AUTODIFFER_H
/* header files */
#include "ADNode.hpp"
#include "ADValue.hpp"
#include "Parser.hpp"

#ifdef USE_THREAD
#include <omp.h>
#endif
/* system header files */
#ifndef DOXYGEN_IGNORE
#include <iostream>
#endif

template <class T>
class AutoDiffer {
  private:
    std::vector<std::pair<std::string, ADValue<T>>> seeds_;

  public:
    // Default ctor.
    AutoDiffer() {}

    void SetSeed(const std::string& variable, T value, T dval=1) {
        ADValue<T> seed_val(value, dval);
        seeds_.emplace_back(
            std::pair<std::string, ADValue<T>>(variable, seed_val));
    }

    void SetSeedVector(const std::string& variable, T value, 
                       const std::vector<T>& dvals) {
        ADValue<T> seed_val(value, dvals);
        seeds_.emplace_back(
            std::pair<std::string, ADValue<T>>(variable, seed_val));
    }

    std::pair<Status,ADValue<T>> Derive(const std::string& equation);
    std::vector<std::pair<Status,ADValue<T>>> Derive(
        std::vector<std::string> equation);
    std::vector<std::pair<Status,ADValue<T>>> Derive(
        const std::string&, std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds); 
};


/* Implementation */
template <class T>
std::pair<Status,ADValue<T>> AutoDiffer<T>::Derive(const std::string& equation) {
    Parser<T> parser(equation);
    Status status = parser.Init(seeds_);
    if (status.code != ReturnCode::success) {
        return std::pair<Status, ADValue<T>>(status, ADValue<T>(0,0));
    }
    return parser.Run();
}

/*Vector output implementation*/
template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDiffer<T>::Derive(std::vector<std::string> equations) {
    std::vector<std::pair<Status,ADValue<T>>> return_values(equations.size()); 
    #pragma omp parallel for
    for (int i = 0; i < equations.size(); i++) {
        #ifdef USE_THREAD
            // Uncomment this chunk to verify if OpenMP working
            // Should print out a number more than 1
            // int num_threads = omp_get_num_threads(); 
            // std::cout << "num_threads: " << num_threads << std::endl;
        #endif
        Parser<T> parser(equations[i]);
        Status status = parser.Init(seeds_);
        if (status.code != ReturnCode::success) {
            return_values[i] = std::pair<Status, ADValue<T>>(status, ADValue<T>(0,0));
        } else {
            return_values[i] = parser.Run();
        }
        // if (return_values[i].first.code != ReturnCode::success) {
        //     std::cout << "Failed" << std::endl; 
        //     // break; 
        // }
    }
    return return_values; 
} 

/*Vector output implementation*/
template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDiffer<T>::Derive(const std::string& equation, std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds) {
    std::vector<std::pair<Status,ADValue<T>>> return_values(seeds.size()); 
    #pragma omp parallel for
    for (int i = 0; i < seeds.size(); i++) {
        #ifdef USE_THREAD
            // Uncomment this chunk to verify if OpenMP working
            // Should print out a number more than 1
            // int num_threads = omp_get_num_threads(); 
            // std::cout << "num_threads: " << num_threads << std::endl;
        #endif
        Parser<T> parser(equation);
        Status status = parser.Init(seeds[i]);
        if (status.code != ReturnCode::success) {
            return_values[i] = std::pair<Status, ADValue<T>>(status, ADValue<T>(0,0));
        } else {
            return_values[i] = parser.Run();
        }
        // if (return_values[i].first.code != ReturnCode::success) {
        //     std::cout << "Failed" << std::endl; 
        //     // break; 
        // }
    }
    return return_values; 
} 


#endif /* AUTODIFFER_H */
