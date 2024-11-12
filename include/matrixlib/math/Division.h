//
// Created by krekcr on 11/12/24.
//

#ifndef MATRIXLIB_PROJECT_DIVISION_H
#define MATRIXLIB_PROJECT_DIVISION_H

#include <stdexcept>
#include <matrixlib/math/Radical.h>

namespace matrixlib::math {


    template<typename T>
    struct Division : Radical<T> {

        explicit Division(Radical<T>* _numerator, Radical<T>* _denominator)
            : numerator(_numerator), denominator(_denominator)
        {
            if (denominator->calculate() == 0) {
                throw std::runtime_error("Denominator can't be zero");
            }
        }

        bool is_complex() override {
            return false;
        }

        T calculate() override {
            return numerator->calculate() / denominator->calculate();
        }

        std::string get_string() override {

            std::string result {};

            if (numerator->is_complex()) {
                result += "(" + numerator->get_string() + ")";
            } else {
                result += numerator->get_string();
            }

            result += " / ";

            if (denominator->is_complex()) {
                result += "(" + denominator->get_string() + ")";
            } else {
                result += denominator->get_string();
            }

            return result;

        }

        Radical<T>* numerator;
        Radical<T>* denominator;


    };


}

#endif //MATRIXLIB_PROJECT_DIVISION_H
