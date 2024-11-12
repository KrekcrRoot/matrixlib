//
// Created by krekcr on 11/12/24.
//

#ifndef MATRIXLIB_PROJECT_SQRT_H
#define MATRIXLIB_PROJECT_SQRT_H

#include <matrixlib/math/Radical.h>
#include <vector>
#include <cmath>

namespace matrixlib::math {


    template<typename T>
    struct SQRT : Radical<T> {

        explicit SQRT(Radical<T>* arg) : data {arg} {}

        bool is_complex() override {
            return false;
        }

        std::string get_string() override {

            std::string result {};

            result += "sqrt(";
            result += data->get_string();
            result += ")";

            return result;

        }

        T calculate() override {
            return std::sqrt(data->calculate());
        }

        Radical<T>* data;

    };


}

#endif //MATRIXLIB_PROJECT_SQRT_H
