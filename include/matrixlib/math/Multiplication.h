//
// Created by krekcr on 11/12/24.
//

#ifndef MATRIXLIB_PROJECT_MULTIPLICATION_H
#define MATRIXLIB_PROJECT_MULTIPLICATION_H

#include <matrixlib/math/Radical.h>
#include <vector>

namespace matrixlib::math {

    template<typename T>
    struct Multiplication : Radical<T> {

        template<class... Args>
        explicit Multiplication(Args... args) {
            this->data = std::vector<Radical<T>*> {args ...};
        }

//        template<class... Args>
//        explicit Multiplication(Args... args) {
//            this->data = std::vector<Radical<T>*> {args ...};
//        }

        T calculate() override {

            T result{1};

            for (const auto item : data) {
                result *= item->calculate();
            }

            return result;

        }

        bool is_complex() override {
            return data.size() > 1;
        }

        std::string get_string() override {

            std::string result {};

            for (const auto item : data) {
                if(item->is_complex()) {
                    result += "(" + item->get_string() + ")";
                } else {
                    result += item->get_string();
                }

                if (item != data.back())
                    result += " * ";
            }

            return result;

        }

        std::vector<Radical<T>*> data;

    };

}

#endif //MATRIXLIB_PROJECT_MULTIPLICATION_H
