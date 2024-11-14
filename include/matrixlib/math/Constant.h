//
// Created by krekcr on 11/12/24.
//

#ifndef MATRIXLIB_PROJECT_CONSTANT_H
#define MATRIXLIB_PROJECT_CONSTANT_H

#include <matrixlib/math/Radical.h>

namespace matrixlib::math {

    template<typename T>
    struct Constant : Radical<T> {

        explicit Constant(T value) : data(value) {}

        T calculate() override {
            return data;
        }

        bool is_complex() override {
            return false;
        }

        std::string get_string() override {
            std::string value = std::to_string(data);
            while (value.ends_with('0')) {
                value.pop_back();
            }
            if(value.ends_with('.')) value.pop_back();
            return value;
        }

        T data;

    };

}

#endif //MATRIXLIB_PROJECT_CONSTANT_H
