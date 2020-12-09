/**
 * @file ADNode.h
 */

#ifndef ADNODE_H
#define ADNODE_H

/* header files */
#include "ADValue.hpp"

/* system header files */
#ifndef DOXYGEN_IGNORE
# include <algorithm>
# include <math.h>
# include <stdio.h>
# include <vector>
#endif

// Scoped enum representing all the elementary functions we support.
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

/**
 * The ADNode class is the handler for evaluating ADValues given an operation.
 * It handles both binary and unary operations by having a self and auxilary
 * ADValue. The auxilary value will be zero and unused in case of unary ops.
 * Once the ADNode is constructed, the Evaluate() function will return a new
 * ADValue that the result of the operation.
 */
template <class T>
class ADNode {
  private:
    // The main value of the operation.
    ADValue<T> self_vertex_;

    // The auxilary value of the operation. Will only be used for binary
    // functions and will be ignored in unary case.
    ADValue<T> aux_vertex_;

    // A boolean to represent if the auxilary vertex is present.
    bool aux_exists_;

    // One of the operations represented above. 
    Operation op_;
  
  public:
    /**
     * The main constructor of ADNode that takes multiple ADValues and an
     * operation.
     *
     * @param self: the main value of the operation. 
     * @param aux: the auxilary value of the operation. Only used in binary 
     * functions.
     * @param op: the op to use on the main (and potentiall aux) ADValues.
     */
    ADNode(ADValue<T> self, ADValue<T> aux, Operation op) : 
                           self_vertex_(self),
                           aux_vertex_(aux), 
                           aux_exists_(true),
                           op_(op) {}
    
    /**
     * An overload constructor for unary operations that do not require an
     * auxilary ADValue. It assert that the op that is passed in is unary
     * and throws an error if not.
     *
     * @param self: the main value of the operation. 
     * @param op: the op to use on the main (and potentiall aux) ADValues.
     */
    ADNode(ADValue<T> self, Operation op) : 
                           self_vertex_(self),
                           aux_exists_(false),
                           op_(op) {
      // List of ops that require an auxiliary node.
      std::vector<Operation> binary_ops = { 
            Operation::addition,
            Operation::subtraction,
            Operation::multiplication,
            Operation::division,
            Operation::log,
      }; 
      // Check if this is a binary op, and if so throw an error because we
      // need an auxilary node.
      if (std::find(binary_ops.begin(), binary_ops.end(), op) != binary_ops.end()) {
        throw std::logic_error("Auxilary node is needed for binary op.");
      }
    }
    
    /**
     * The handler of operations. This function is responsible for calling the
     * correct operation on the self (and aux in case of binary ops) ADValue(s). 
     *
     * @returns : an ADValue with the result of the operation being executed.
     */
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
