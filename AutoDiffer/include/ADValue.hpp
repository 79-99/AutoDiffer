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
    std::vector<T> dvs;   /**< derivative values */

  public:

    /* constructors */
    ADValue() {};
    ADValue(T val, T dval) : v(val) {
        dvs.emplace_back(dval);
    };
    ADValue(T val,const std::vector<T>& dvals) : v(val), dvs(dvals) {};

    /* getters */
    T val() const { return v; };
    T dval(int i) const { return dvs[i]; };

    /* setters */
    void setval(T val){v = val;}
    void setdval(T dval){
        dvs.emplace_back(dval);
    }
    void setdval(const std::vector<T>& dvals){ dvs = dvals; }

    /* ==================== */
    /* overloaded operators */
    /* ==================== */
    const ADValue<T> operator+(const ADValue<T> &other) const{
        T new_val = v + other.val();
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(dvs[i] + other.dval(i));
        }
        return ADValue<T>(new_val, new_derivs);
    }

    const ADValue<T> operator-(const ADValue<T> &other) const{
        T new_val = v - other.val();
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(dvs[i] - other.dval(i));
        }
        return ADValue<T>(new_val, new_derivs);
    }

    ADValue<T> power(const ADValue<T> &other) {
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

    ADValue<T> ADmul(const ADValue<T> &other) {
        T new_v = v * other.val();
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(dvs[i]*other.val() + other.dval(i)*v);
        }
        return ADValue<T>(new_v, new_derivs);
    }

    ADValue<T> ADdiv(const ADValue<T> &other) {
        T new_v = v / other.val();
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            T new_dv = (dvs[i]*other.val() - other.dval(i)*v) 
                        / pow(other.val(), 2);
            new_derivs.emplace_back(new_dv);
        }
        return ADValue<T>(new_v, new_derivs);
    }

    ADValue<T> ADexp() {
        T new_v = exp(this->val());
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(exp(this->val()) * this->dval(i));
        }
        return ADValue<T>(new_v, new_derivs);
    }

    ADValue<T> ADsin() {
        T new_v = sin(this->val());
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(cos(this->val()) * this->dval(i));
        }
        return ADValue<T>(new_v, new_derivs);
    }

    ADValue<T> ADcos() {
        T new_v = cos(this->val());
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(-sin(this->val()) * this->dval(i));
        }
        return ADValue<T>(new_v, new_derivs);
    }

    ADValue<T> ADtan() {
        T new_v = tan(this->val());
        std::vector<T> new_derivs;
        for (int i = 0; i < dvs.size(); ++i) {
            new_derivs.emplace_back(1/(pow(cos(this->val()), 2))*this->dval(i));
        }
        return ADValue<T>(new_v, new_derivs);
    }

};


#endif /* ADVALUE_H */
