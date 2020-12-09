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
#include <thread>
#endif

/**
 * The AutoDiffer class is the main interface provided to the user. Once they 
 * have constructed an AutoDiffer object, they can set the seed variables with
 * the SetSeed function (e.g., SetSeed("y", 1.5, 1.0)). In the case of a vector
 * function where the seed of each partial derivative needs to be set, the 
 * SetSeedVector interface must be used. With the seeds in place, the Derive
 * function can be called. Derive is overloaded to handle 3 cases.
 * 
 * 1. Single function. In this case the function is just passed in as a string.
 * 2. Vector of functions. In this case a vector of strings is passed in.
 * 3. Single function with vector of seeds. In this case the function is passed 
 *    in as a string, and AutoDiffer is run on each of the different seeds.
 * 
 * Example usage: on f(x) = x^2 at x=1.5.
 * 
 * AutoDiffer<double> ad;
 * ad.SetSeed("x", 1.5, 1.0);
 * std::pair<Status, ADValue<double>> result = ad.Derive("(x^2)");
 * // Check for success.
 * assert(result.first.code == ReturnCode::success);
 * // Now can use the result.second (the ADValue object).
 * assert(result.second.val() == 2.25); // check value
 * assert(result.second.dval(0) == 3);  // check derivative
 */
template <class T>
class AutoDiffer {
  protected:
    // A vector containing the names and values of the seeds. In the scalar case
    // this is a single item vector.
    std::vector<std::pair<std::string, ADValue<T>>> seeds_;

  public:
    AutoDiffer() {}

    /**
     * Sets the value and derivative of a seed in the case of a scalar function.
     * For functions of multiple variables, use SetSeedVector instead.
     * 
     * @param: variable: the name of the variable (e.g., "y").
     * @param: val: the inital value of the variable.
     * @param: dval: the inital value of the derivative.
     */
    void SetSeed(const std::string& variable, T value, T dval=1) {
        ADValue<T> seed_val(value, dval);
        seeds_.emplace_back(
            std::pair<std::string, ADValue<T>>(variable, seed_val));
    }

    /**
     * Sets the value and the vector of derivatives  for a seed in the case of a 
     * multiple variable function. For scalar functions, use SetSeed instead.
     * 
     * @param: variable: the name of the variable (e.g., "y").
     * @param: val: the inital value of the variable.
     * @param: dvals: a vector with the initial derivatives with respect to each
     * input variable.
     */
    void SetSeedVector(const std::string& variable, T value, 
                       const std::vector<T>& dvals) {
        ADValue<T> seed_val(value, dvals);
        seeds_.emplace_back(
            std::pair<std::string, ADValue<T>>(variable, seed_val));
    }

    /**
     * Single function derive. For multiple functions use the overloaded derive
     * parameterized by a vector of strings.
     * 
     * @param: equation: the equation to run derivative on (e.g., "(exp(x))")..
     * @returns: a Status and ADValue pair. If the Status is not success, then
     * the ADValue object will evaluate to zero. It is up to the caller to
     * ensure that the Status is success before using the ADValue object.
     */
    std::pair<Status,ADValue<T>> Derive(const std::string& equation);
    
    /**
     * Multiple function derive. For a single function use the overloaded derive
     * parameterized by a single string.
     * 
     * @param: equations: A vector of the equations to derive.
     * @returns: a vector of a Status and ADValue pairs. If the Status is not 
     * success for any equation, then the ADValue object at that equations 
     * index will evaluate to zero. It is up to the caller to ensure that the 
     * Status is success before using any of the ADValue objects.
     */
    std::vector<std::pair<Status,ADValue<T>>> Derive(
        std::vector<std::string> equations);

    /**
     * Single function derive with multiple seed values.
     * 
     * @param: equation: A string representation of the equation.
     * @param: seeds: A vector of seeds at which to evaluate the derivative.
     * @returns: a vector of a Status and ADValue pairs. If the Status is not 
     * success for any equation, then the ADValue object at that equations 
     * index will evaluate to zero. It is up to the caller to ensure that the 
     * Status is success before using any of the ADValue objects.
     */
    std::vector<std::pair<Status,ADValue<T>>> Derive(
        const std::string& equation, 
        std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds); 
};


/* Implementation AutoDiffer (single Threaded) */
template <class T>
std::pair<Status,ADValue<T>> AutoDiffer<T>::Derive(const std::string& equation) {
    // Create a parser with the equation and initialize it.
    Parser<T> parser(equation);
    Status status = parser.Init(seeds_);
    if (status.code != ReturnCode::success) {
        return std::pair<Status, ADValue<T>>(status, ADValue<T>(0,0));
    }
    return parser.Run();
}

template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDiffer<T>::Derive(
    std::vector<std::string> equations) {
    // Initialize a return value vector with same size as number of eqs.
    std::vector<std::pair<Status,ADValue<T>>> return_values(equations.size()); 
    for (int i = 0; i < equations.size(); i++) {
        // Create a parser for each equation.
        Parser<T> parser(equations[i]);
        Status status = parser.Init(seeds_);
        if (status.code != ReturnCode::success) {
            return_values[i] = std::pair<Status, ADValue<T>>(
                status, ADValue<T>(0,0));
        } else {
            return_values[i] = parser.Run();
        }
    }
    return return_values; 
} 


template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDiffer<T>::Derive(
    const std::string& equation, 
    std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds) {
    // Initialize a return value vector with same size as number of seeds.
    std::vector<std::pair<Status,ADValue<T>>> return_values(seeds.size()); 
    for (int i = 0; i < seeds.size(); i++) {
        Parser<T> parser(equation);
        // Initialized each parser with the same equation and the i^th seed vec.
        Status status = parser.Init(seeds[i]);
        if (status.code != ReturnCode::success) {
            return_values[i] = std::pair<Status, ADValue<T>>(
                status, ADValue<T>(0,0));
        } else {
            return_values[i] = parser.Run();
        }
    }
    return return_values; 
}


/**
 * The AutoDifferOpenMp class inherits from the AutoDiffer class and provides
 * some the multiple function and multiple seed versions of the Derive function
 * from the AutoDiffer, but with OpenMp versions of each Derive call.
 * In order to use this class, the entire project has to be compiled with the 
 * "--thread" flag. So run`bash config.sh --thread` at the top level directory 
 * if you have not already.
 */
template <class T>
class AutoDifferOpenMp : public AutoDiffer<T> {
  private:
    // How many threads to run with openmp.
    int num_threads_;

  public:
    // Constructor initializes the number of threads to be used.
    AutoDifferOpenMp(int num_threads) : num_threads_(num_threads) {}

    // Same as the multiple equation derive of AutoDiffer, but with openmp 
    // multithreading.
    std::vector<std::pair<Status,ADValue<T>>> DeriveOpenMp(
        std::vector<std::string> equation);
    
    // Same as the multiple seed derive of the AutoDiffer, but with openmp
    // multithreading.
    std::vector<std::pair<Status,ADValue<T>>> DeriveOpenMp(
        const std::string& equation, 
        std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds); 
};


template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDifferOpenMp<T>::DeriveOpenMp(
    std::vector<std::string> equations) {
    #ifdef USE_THREAD
        // Set the number of theads.
        omp_set_num_threads(num_threads_);
    #endif
    std::vector<std::pair<Status,ADValue<T>>> return_values(equations.size()); 
    #pragma omp parallel for
    for (int i = 0; i < equations.size(); i++) { 
        #ifdef USE_THREAD
            // Uncomment this line to verify if OpenMP is working
            // Should print out a number more than 1 
            // std::cout << "*** num_threads:" <<omp_get_num_threads()<< std::endl;
        #endif
        Parser<T> parser(equations[i]);
        Status status = parser.Init(this->seeds_);
        if (status.code != ReturnCode::success) {
            return_values[i] = std::pair<Status, ADValue<T>>(
                status, ADValue<T>(0,0));
        } else {
            return_values[i] = parser.Run();
        }
    }
    return return_values; 
} 

template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDifferOpenMp<T>::DeriveOpenMp(
    const std::string& equation, 
    std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds) {
    #ifdef USE_THREAD
        // Set the number of theads.
        omp_set_num_threads(num_threads_);
    #endif
    std::vector<std::pair<Status,ADValue<T>>> return_values(seeds.size()); 
    #pragma omp parallel for
    for (int i = 0; i < seeds.size(); i++) {
        #ifdef USE_THREAD
            // Uncomment this line to verify if OpenMP is working
            // Should print out a number more than 1 
            // std::cout << "*** num_threads:" <<omp_get_num_threads()<< std::endl;
        #endif
        Parser<T> parser(equation);
        Status status = parser.Init(seeds[i]);
        if (status.code != ReturnCode::success) {
            return_values[i] = std::pair<Status, ADValue<T>>(
                status, ADValue<T>(0,0));
        } else {
            return_values[i] = parser.Run();
        }
    }
    return return_values; 
} 


/**
 * The AutoDifferStdThread class inherits from the AutoDiffer class and provides
 * some the multiple function and multiple seed versions of the Derive function
 * from the AutoDiffer, but with std::thread versions of each Derive call.
 */
template <class T>
class AutoDifferStdThread : public AutoDiffer<T> {
  private:
    // How many std::threads to spin up.
    int num_threads_;

  public:
    // Constructor initializes the number of threads to be used.
    AutoDifferStdThread(int num_threads) : num_threads_(num_threads) {}

    // Same as the multiple equation derive of AutoDiffer, but with std::thread 
    // multithreading.
    std::vector<std::pair<Status,ADValue<T>>> DeriveStdThread(
        std::vector<std::string> equation);
    
    // Same as the multiple seed derive of the AutoDiffer, but with std::thread
    // multithreading.
    std::vector<std::pair<Status,ADValue<T>>> DeriveStdThread(
        const std::string& equation, 
        std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds); 
};

// Function to handle a single threads worth of work. Everything passed in by
// reference to allow it to be updated.
template <class T>
void SingleThreadWork(
    int idx, const std::string& eq, 
    std::vector<std::pair<Status,ADValue<T>>>& return_vals,
    const std::vector<std::pair<std::string, ADValue<T>>>& seeds) {
    
    // Create parser.
    Parser<T> parser(eq);
    Status status = parser.Init(seeds);
    if (status.code != ReturnCode::success) {
            return_vals[idx] = std::pair<Status, ADValue<T>>(
                status, ADValue<T>(0,0));
    } else {
        return_vals[idx] = parser.Run();
    }
}

template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDifferStdThread<T>::DeriveStdThread(
    std::vector<std::string> equations) {
    // Initialize vector of return values.
    std::vector<std::pair<Status,ADValue<T>>> return_values(equations.size());
    
    // Thread vector.
    std::vector<std::thread> thread_vec;
    for (int i = 0; i < equations.size(); i++) {
        // Construct a thread with SingleThreadWork.
        thread_vec.push_back(std::thread(
            SingleThreadWork<T>, i, std::ref(equations[i]), 
            std::ref(return_values), std::ref(this->seeds_)));
    }
    // Join all threads.
    for(auto& t: thread_vec) {
        t.join();
    }
    return return_values; 
} 

template <class T>
std::vector<std::pair<Status,ADValue<T>>> AutoDifferStdThread<T>::DeriveStdThread(
    const std::string& equation, 
    std::vector<std::vector<std::pair<std::string, ADValue<T>>>> seeds) {
    
    // Initialize vector of return values.
    std::vector<std::pair<Status,ADValue<T>>> return_values(seeds.size());
    
    // Thread vector.
    std::vector<std::thread> thread_vec;
    for (int i = 0; i < seeds.size(); i++) {
        // Construct a thread with SingleThreadWork.
        thread_vec.push_back(std::thread(
            SingleThreadWork<T>, i, std::ref(equation), 
            std::ref(return_values), std::ref(seeds[i])));
    }
    // Join all threads.
    for(auto& t: thread_vec) {
        t.join();
    }
    return return_values; 
} 


#endif /* AUTODIFFER_H */
