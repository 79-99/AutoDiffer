/**
 * @file AutoDiffer.hpp
 */

#ifndef AUTODIFFER_H
#define AUTODIFFER_H

/* header files */
#include "ADNode.hpp"
#include "ADValue.hpp"
#include "Parser.hpp"

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
        seeds_.emplace_back(std::pair<std::string, ADValue<T>>(variable, seed_val));
    }

    void SetSeedVector(const std::string& variable, T value, 
                       const std::vector<T>& dvals) {
        ADValue<T> seed_val(value, dvals);
        seeds_.emplace_back(std::pair<std::string, ADValue<T>>(variable, seed_val));
    }

    std::pair<Status,ADValue<T>> Derive(const std::string& equation);
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


#endif /* AUTODIFFER_H */
