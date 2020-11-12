/**
 * @file ADValue.h
 */

#ifndef ADVALUE_H
#define ADVALUE_H

/* header files */


/* system header files */
#ifndef DOXYGEN_IGNORE
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

    void print_hello() const;

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

    ADValue<T> power(double exponent) {
        T new_v = pow(v, exponent);
        T new_dv = exponent * pow(v, exponent - 1) * dv;
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
