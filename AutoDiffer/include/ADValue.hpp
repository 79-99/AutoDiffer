/**
 * @file ADValue.h
 */

#ifndef ADVALUE_H
#define ADVALUE_H

/* header files */


/* system header files */
#ifndef DOXYGEN_IGNORE
# include <iostream>
# include <math.h>
# include <stdio.h>
# include <vector>
#endif


/**
 * The ADValue class represents the main AutoDiffer value objects. ADValues 
 * contain a value (accessed via .val()) and a vector of derivatives (accessed
 * via .dval(i)). The vector of derivatives represent the partial with respect
 * to a given input variable. 
 */
template <class T>
class ADValue {
  private:
    // Value.
    T v;
    
    // Derivative values.
    std::vector<T> dvs;

  public:
    /**
     * Default constructor.
     */
    ADValue() {};

    /**
     * Overloaded constructor for the scalar case. Since in a scalar setting
     * there is only a single derivative, we simply emplace this onto the 
     * vector of derivatives.
     * 
     * @param: val: the inital value.
     * @param: dval: the inital value of the derivative.
     */
    ADValue(T val, T dval) : v(val) {
        dvs.emplace_back(dval);
    };

    /**
     * Overloaded constructor for the vector case. Construct with a entire
     * vector which contains the seeds.
     * 
     * @param: val: the inital value.
     * @param: dvals: vector with the inital value of the derivatives.
     */
    ADValue(T val,const std::vector<T>& dvals) : v(val), dvs(dvals) {};

    /* getters */
    T val() const { return v; };
    T dval(int i) const { return dvs[i]; };

    /**
     * Overloaded addition operator. Each derivative in the vector of derivs
     * is calculated and used to create a new_derivs vector.
     * 
     * @param: other: the right hand side of the addition operation.
     * @returns: ADValue with the result of the addition.
     */
    const ADValue<T> operator+(const ADValue<T> &other) const;

    /**
     * Overloaded subtraction operator.
     * 
     * @param: other: the right hand side of the subtraction operation.
     * @returns: ADValue with the result of the subtraction.
     */
    const ADValue<T> operator-(const ADValue<T> &other) const;

    /**
     * Power operator.
     * 
     * @param: other: the exponent.
     * @returns: ADValue with the result of the power.
     */
    ADValue<T> power(const ADValue<T> &other);

    /**
     * Multiplication operator. 
     * 
     * @param: other: the right hand side.
     * @returns: ADValue with the result of the multiplication.
     */
    ADValue<T> ADmul(const ADValue<T> &other);

    /**
     * Division operator.
     * 
     * @param: other: the denominator.
     * @returns: ADValue with the result of the division.
     */
    ADValue<T> ADdiv(const ADValue<T> &other);

    /**
     * Exponentiation operator.
     * 
     * @returns: ADValue with the result of the division.
     */
    ADValue<T> ADexp();

    /**
     * Sine operator.
     * 
     * @returns: ADValue with the result of the sin.
     */
    ADValue<T> ADsin();

    /**
     * Cosine operator.
     * 
     * @returns: ADValue with the result of the cos.
     */
    ADValue<T> ADcos();

    /**
     * Tangent operator.
     * 
     * @returns: ADValue with the result of the tan.
     */
    ADValue<T> ADtan();

    /**
     * Arcsin operator.
     * 
     * @returns: ADValue with the result of the arcsin.
     */
    ADValue<T> ADarcsin();

    /**
     * Arccos operator.
     * 
     * @returns: ADValue with the result of the arccos.
     */
    ADValue<T> ADarccos();

    /**
     * Arctan operator.
     * 
     * @returns: ADValue with the result of the arctan.
     */
    ADValue<T> ADarctan();

    /**
     * Sinh operator.
     * 
     * @returns: ADValue with the result of the sinh.
     */
    ADValue<T> ADsinh();

    /**
     * Cosh operator.
     * 
     * @returns: ADValue with the result of the cosh.
     */
    ADValue<T> ADcosh();

    /**
     * Tanh operator.
     * 
     * @returns: ADValue with the result of the tanh.
     */
    ADValue<T> ADtanh();

    /**
     * Logistic operator.
     * 
     * @returns: ADValue with the result of the logistic.
     */
    ADValue<T> ADlogistic();

    /**
     * Log operator.
     * 
     * @param: other: the base of the logarithm.
     * @returns: ADValue with the result of the log.
     */
    ADValue<T> ADlog(const ADValue<T> &other);

    /**
     * Sqrt operator.
     * 
     * @returns: ADValue with the result of the sqrt.
     */
    ADValue<T> ADsqrt();
};

// Implementation

template<class T>
const ADValue<T> ADValue<T>::operator+(const ADValue<T> &other) const {
    // Just add values.
    T new_val = v + other.val();
    std::vector<T> new_derivs;

    // Add each derivative.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(dvs[i] + other.dval(i));
    }
    return ADValue<T>(new_val, new_derivs);
}

template<class T>
const ADValue<T> ADValue<T>::operator-(const ADValue<T> &other) const {
    // Just subtract vals.
    T new_val = v - other.val();
    std::vector<T> new_derivs;
    // Subtract each derivative.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(dvs[i] - other.dval(i));
    }
    return ADValue<T>(new_val, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::power(const ADValue<T> &other) {
    // Take v to power of exponent.
    T new_v = pow(v, other.val());
    if (v == 0) {
        return ADValue<T>(0, 0);    
    }
    std::vector<T> new_derivs;
    for (int i = 0; i < dvs.size(); ++i) {
        T new_dv;
        if (v > 0) {
            // Use generalized chain rule.
            new_dv = new_v * (other.dval(i)*log(v) + other.val() * dvs[i] / v);
        } else {
            // Other must be a constant.
            if (other.dval(i) != 0) {
                throw std::logic_error("Derivative not defined or complex.");
            }
            // Use power rule in this case.
            new_dv = other.val() * pow(v, other.val() - 1) * dvs[i];
        }
        new_derivs.emplace_back(new_dv);
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADmul(const ADValue<T> &other) {
    // Multiply values.
    T new_v = v * other.val();
    std::vector<T> new_derivs;
    // Product rule for each derivative.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(dvs[i]*other.val() + other.dval(i)*v);
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADdiv(const ADValue<T> &other) {
    // Divide values.
    T new_v = v / other.val();
    std::vector<T> new_derivs;
    // Quotient rule for each derivative.
    for (int i = 0; i < dvs.size(); ++i) {
        T new_dv = (dvs[i]*other.val() - other.dval(i)*v) 
                    / pow(other.val(), 2);
        new_derivs.emplace_back(new_dv);
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADexp() {
    // Exp value.
    T new_v = exp(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(exp(this->val()) * this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADsin() {
    // Sin value.
    T new_v = sin(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(cos(this->val()) * this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADcos() {
    // cos value.
    T new_v = cos(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(-sin(this->val()) * this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADtan() {
    // tan value.
    T new_v = tan(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(1/(pow(cos(this->val()), 2))*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADarcsin() {
    // asin value.
    T new_v = asin(this->val());
    std::vector<T> new_derivs;
    // Derivative of asin.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(1/sqrt(1-pow(this->val(), 2))*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADarccos() {
    // acos value.
    T new_v = acos(this->val());
    std::vector<T> new_derivs;
    // Derivative of acos.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(-1/sqrt(1-pow(this->val(), 2))*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADarctan() {
    // atan value.
    T new_v = atan(this->val());
    std::vector<T> new_derivs;
    // Derivative of atan.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(1/(1+pow(this->val(), 2))*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADsinh() {
    // sinh value.
    T new_v = sinh(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(cosh(this->val())*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADcosh() {
    // cosh value.
    T new_v = cosh(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(sinh(this->val())*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADtanh() {
    // tanh value.
    T new_v = tanh(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(1/pow(cosh(this->val()), 2)*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADlogistic() {
    // logistic value.
    T new_v = exp(this->val()) / (1 + exp(this->val()));
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(
            exp(this->val()) / pow(1 + exp(this->val()), 2)*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADlog(const ADValue<T> &other) {
    // log base other of value.
    T new_v = log(this->val()) / log(other.val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(1/(this->val()*log(other.val()))*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

template<class T>
ADValue<T> ADValue<T>::ADsqrt() {
    // sqrt value.
    T new_v = sqrt(this->val());
    std::vector<T> new_derivs;
    // Chain rule.
    for (int i = 0; i < dvs.size(); ++i) {
        new_derivs.emplace_back(0.5 * pow(this->val(), -0.5)*this->dval(i));
    }
    return ADValue<T>(new_v, new_derivs);
}

#endif /* ADVALUE_H */
