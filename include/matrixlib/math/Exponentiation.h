//
// Created by krekcr on 11/13/24.
//

#ifndef MATRIXLIB_PROJECT_EXPONENTIATION_H
#define MATRIXLIB_PROJECT_EXPONENTIATION_H

#include <matrixlib/math/Radical.h>

namespace matrixlib::math {

    template<typename T>
    struct Exponentiation : Radical<T> {

        explicit Exponentiation(Radical<T>* _basis, Radical<T>* _exponent)
            : basis{_basis}, exponent{_exponent}
        {}

        bool is_complex() override {
            return false;
        }

        T calculate() override {
            return std::pow(basis->calculate(), exponent->calculate());
        }

        std::string get_string() override {

            std::string result {};

            if (basis->is_complex()) {
                result += "(" + basis->get_string() + ")";
            } else {
                result += basis->get_string();
            }

            result += "^";

            if (exponent->is_complex()) {
                result += "(" + exponent->get_string() + ")";
            } else {
                result += exponent->get_string();
            }

            return result;

        }

        Radical<T>* basis;
        Radical<T>* exponent;

    };

}

#endif //MATRIXLIB_PROJECT_EXPONENTIATION_H
