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
  subtraction = 2,
  multiplication = 3,
  division = 4,
  power = 5,
  sin = 6, 
  cos = 7, 
  tan = 8,
  exp = 9,
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

        case Operation::multiplication : {
          return self_vertex_.ADmul(aux_vertex_);
        }

        case Operation::division : {
          return self_vertex_.ADdiv(aux_vertex_);
        }

        case Operation::power : {
          return self_vertex_.power(aux_vertex_);
        }

        case Operation::subtraction : {
          return self_vertex_ - aux_vertex_; 
        }

        case Operation::sin : {
          return self_vertex_.ADsin(); 
        }

        case Operation::cos : {
          return self_vertex_.ADcos(); 
        }

        case Operation::tan : {
          return self_vertex_.ADtan(); 
        }

        case Operation::exp : {
          return self_vertex_.ADexp();
        }
      }
    }
};


#endif /* ADNODE_H */
