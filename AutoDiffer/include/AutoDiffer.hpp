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

    std::pair<Status,T> Derive(const std::string& equation);
};


/* Implementation */
template <class T>
std::pair<Status,T> AutoDiffer<T>::Derive(const std::string& equation) {
    Parser<T> parser(equation);
    Status status = parser.Init(seeds_);
    if (status.code != ReturnCode::success) {
        return std::pair<Status, T>(status, 0);
    }
    auto res = parser.Run();
    status = res.first;
    if (status.code != ReturnCode::success) {
        return std::pair<Status, T>(status, 0);
    }
    return std::pair<Status,T>(status, res.second.dval());
    
}


#endif /* AUTODIFFER_H */
