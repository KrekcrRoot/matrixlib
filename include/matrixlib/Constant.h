//
// Created by krekcr on 11/8/24.
//

#ifndef MATRIXLIB_PROJECT_CONSTANT_H
#define MATRIXLIB_PROJECT_CONSTANT_H

#include <matrixlib/Radical.h>

namespace matrixlib {

    template<typename T>
    struct Constant : Radical<T> {

        explicit Constant(T value) {
            this->data = value;
        };

        T get_algebraic() const override {
            return this->data;
        };

        [[nodiscard]] std::string get_string() const override {
            return std::to_string(this->data);
        }

        T data;

    };

}

#endif //MATRIXLIB_PROJECT_CONSTANT_H
