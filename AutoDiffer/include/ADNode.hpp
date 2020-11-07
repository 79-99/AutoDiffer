/**
 * @file ADNode.h
 */

#ifndef ADNODE_H
#define ADNODE_H

/* header files */
#include "ADValue.hpp"

/* system header files */
#ifndef DOXYGEN_IGNORE
# include <math.h>
# include <stdio.h>
# include <vector>
#endif

enum class Operation {
  addition = 1,
  power = 2,
  // division, mult, subtraction, exp, trig, negation
};

template <class T>
class ADNode {
  private:
    ADValue<T> self_vertex_;
    ADValue<T> aux_vertex_;
    Operation op_;
  
  public:
    ADNode(ADValue<T> self, ADValue<T> aux, Operation op) : 
                           self_vertex_(self), 
                           aux_vertex_(aux),
                           op_(op) {}
    
    ADValue<T> Evaluate() {
      switch(op_) {
        case Operation::addition : {
          return self_vertex_ + aux_vertex_;
        }

        case Operation::power : {
          return self_vertex_.power(aux_vertex_.val());
        }
      }
    }
};


#endif /* ADNODE_H */
