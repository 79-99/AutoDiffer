/**
 * @file Autodiffer.h
 */

#ifndef AUTODIFFER_H
#define AUTODIFFER_H

/* header files */

/* system header files */
#ifndef DOXYGEN_IGNORE
#  include <stdio.h>
#endif


/* =============== */
/* Data Structures */
/* =============== */
template <class T>
class AutoDiffer {
  private:
    T v;    /**< value */
    T dv;   /**< derivative value */

  public:

    /* constructors */
    AutoDiffer(){};
    AutoDiffer(T val,T dval) : v(val),dv(dval) {};

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
    const AutoDiffer<T> operator+(const AutoDiffer<T> &other) const{
        return AutoDiffer<T>(v + other.val(), dv + other.dval());
    }

    AutoDiffer<T>& operator+=(const AutoDiffer<T> &other){
        v += other.val();
        dv += other.dval();
        return *this;
    }
};

#endif /* AUTODIFFER_H */
