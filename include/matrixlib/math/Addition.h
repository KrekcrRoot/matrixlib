//
// Created by krekcr on 11/12/24.
//

#ifndef MATRIXLIB_PROJECT_ADDITION_H
#define MATRIXLIB_PROJECT_ADDITION_H

#include <matrixlib/math/Radical.h>

#include <vector>
#include <array>
#include <iostream>

namespace matrixlib::math {

    template<typename T>
    struct Addition : Radical<T> {

        template<class... Args>
        explicit Addition(Args... args) {
            this->data = std::vector<Radical<T>*> {args ...};
        }

        bool is_complex() override {
            return data.size() > 1;
        }

        std::string get_string() override {

            std::string result {};

            for (const auto item : data) {
                if (item->is_complex()) {
                    result += "(" + item->get_string() + ")";
                } else {
                    result += item->get_string();
                }

                if (item != data.back())
                    result += " + ";
            }

            return result;

        }

        T calculate() override {
            T result{};

            for (const auto item : data) {
                result += item->calculate();
            }

            return result;
        }

        [[maybe_unused]] void add(Radical<T>* value) {
            data.push_back(value);
        }

        std::vector<Radical<T>*> data;

    };

};

#endif //MATRIXLIB_PROJECT_ADDITION_H
