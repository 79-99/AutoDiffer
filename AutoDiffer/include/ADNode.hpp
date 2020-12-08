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
  arcsin = 10,
  arccos = 11,
  arctan = 12,
  sinh = 13,
  cosh = 14,
  tanh = 15,
  logistic = 16,
  log = 17,
  sqrt = 18,
};

template <class T>
class ADNode {
  private:
    ADValue<T> self_vertex_;
    ADValue<T> aux_vertex_;
    bool aux_exists_;
    Operation op_;
  
  public:
    ADNode(ADValue<T> self, ADValue<T> aux, Operation op) : 
                           self_vertex_(self),
                           aux_vertex_(aux), 
                           aux_exists_(true),
                           op_(op) {}
    
    ADNode(ADValue<T> self, Operation op) : 
                           self_vertex_(self),
                           aux_exists_(false),
                           op_(op) {
      // List of ops that requiry an auxiliary node.
      std::vector<Operation> binary_ops = { 
            Operation::addition,
            Operation::subtraction,
            Operation::multiplication,
            Operation::division,
            Operation::log,
      }; 
      if (std::find(binary_ops.begin(), binary_ops.end(), op) != binary_ops.end()) {
        throw std::logic_error("Auxilary node is needed for binary op.");
      }
    }
    
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

        case Operation::arcsin : {
          return self_vertex_.ADarcsin();
        }

        case Operation::arccos : {
          return self_vertex_.ADarccos();
        }

        case Operation::arctan : {
          return self_vertex_.ADarctan();
        }

        case Operation::sinh : {
          return self_vertex_.ADsinh();
        }

        case Operation::cosh : {
          return self_vertex_.ADcosh();
        }

        case Operation::tanh : {
          return self_vertex_.ADtanh();
        }

        case Operation::logistic : {
          return self_vertex_.ADlogistic();
        }

        case Operation::log : {
          return self_vertex_.ADlog(aux_vertex_);
        }

        case Operation::sqrt : {
          return self_vertex_.ADsqrt();
        }
      }
    }
};


#endif /* ADNODE_H */
