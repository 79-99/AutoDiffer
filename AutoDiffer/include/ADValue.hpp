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

template <class T>
class ADValue {
  private:
    T v;    /**< value */
    T dv;   /**< derivative value */

  public:

    /* constructors */
    ADValue(){};
    ADValue(T val,T dval) : v(val),dv(dval) {};

    /* getters */
    T val() const {return v;};
    T dval() const {return dv;};

    /* setters */
    void setval(T val){v = val;}
    void setdval(T dval){dv = dval;}

    /* ==================== */
    /* overloaded operators */
    /* ==================== */
    const ADValue<T> operator+(const ADValue<T> &other) const{
        return ADValue<T>(v + other.val(), dv + other.dval());
    }

    ADValue<T>& operator+=(const ADValue<T> &other){
        v += other.val();
        dv += other.dval();
        return *this;
    }

    const ADValue<T> operator-(const ADValue<T> &other) const{
        return ADValue<T>(v - other.val(), dv - other.dval());
    }

    ADValue<T>& operator-=(const ADValue<T> &other){
        v -= other.val();
        dv -= other.dval();
        return *this;
    }

    ADValue<T> power(const ADValue<T> &other) {
        T new_v = pow(v, other.val());
        if (v == 0) {
            return ADValue<T>(0, 0);    
        }
        T new_dv;
        if (v > 0) {
            // Use generalized chain rule.
            new_dv = new_v * (other.dval()*log(v) + other.val() * dv / v);
        } else {
            // Other must be a constant.
            if (other.dval() != 0) {
                throw std::logic_error("Derivative not defined or complex.");
            }
            // Use power rule in this case.
            new_dv = other.val() * pow(v, other.val() - 1) * dv;
        }
        return ADValue<T>(new_v, new_dv);
    }

    ADValue<T> ADmul(const ADValue<T> &other) {
        T new_v = v * other.val();
        T new_dv = dv*other.val() + v*other.dval();
        return ADValue<T>(new_v, new_dv);
    }

    ADValue<T> ADdiv(const ADValue<T> &other) {
        T new_v = v / other.val();
        T new_dv = (dv*other.val() - other.dval()*v)/ pow(other.val(), 2);
        return ADValue<T>(new_v, new_dv);
    }

    ADValue<T> ADexp() {
        T new_v = exp(this->val());
        T new_dv = exp(this->val()) * this->dval();
        return ADValue<T>(new_v, new_dv);
    }

    ADValue<T> ADsin() {
        T new_v = sin(this->val());
        T new_dv = cos(this->val()) * this->dval(); 
        return ADValue<T>(new_v, new_dv);
    }

    ADValue<T> ADcos() {
        T new_v = cos(this->val());
        T new_dv = -sin(this->val()) * this->dval(); 
        return ADValue<T>(new_v, new_dv);
    }

    ADValue<T> ADtan() {
        T new_v = tan(this->val());
        T new_dv = (1/(pow(cos(this->val()), 2)))*this->dval();
        return ADValue<T>(new_v, new_dv);
    }

};


#endif /* ADVALUE_H */
