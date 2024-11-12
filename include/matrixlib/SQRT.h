//
// Created by krekcr on 11/8/24.
//

#ifndef MATRIXLIB_PROJECT_SQRT_H
#define MATRIXLIB_PROJECT_SQRT_H

#include <cmath>
#include <matrixlib/Radical.h>

namespace matrixlib {


    template<typename T>
    struct SQRT : public Radical<T> {

        explicit SQRT(T value) {
            this->data = value;
            this->multiplier = 1;
        }

        explicit SQRT(T multiplier, T value) {
            this->data = value;
            this->multiplier = multiplier;
        }

        [[nodiscard]] bool is_integer() const {
            T algebraic = std::sqrt(this->data);
            return (algebraic * algebraic) == this->data;
        }

        T get_algebraic() const override {
            return multiplier * std::sqrt(this->data);
        };

        [[nodiscard]] std::string get_string() const override {

            if(this->is_integer())
                return std::to_string(this->get_algebraic());

            if(multiplier == 1)
                return "sqrt(" + std::to_string(this->data) + ")";

            return std::to_string(multiplier) + " * sqrt(" + std::to_string(this->data) + ")";
        }

        T data, multiplier;

    };


}

#endif //MATRIXLIB_PROJECT_SQRT_H
