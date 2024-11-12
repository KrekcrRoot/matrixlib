//
// Created by krekcr on 11/8/24.
//

#ifndef MATRIXLIB_PROJECT_EXPRESSION_H
#define MATRIXLIB_PROJECT_EXPRESSION_H

#include <matrixlib/Radical.h>
#include <matrixlib/SQRT.h>
#include <matrixlib/Constant.h>
#include <vector>
#include <iostream>
#include <string>

namespace matrixlib {


    template<typename T>
    struct Expression {

        std::vector<Radical<T>*> data;

        T calculate() {
            T result{};
            for(const auto item : data) {
                result += item->get_algebraic();
            }
            return result;
        }

        void add(Radical<T>* item) {
            this->data.push_back(item);
        }

        std::string get_string() {
            std::string result{};
            for(const auto item : data) {
                if(!result.empty())
                    result += " + ";

                if(item->get_algebraic() != 0)
                    result += item->get_string();
            }
            return result;
        };

        void simplify() {

            Expression<T> simplified = this->get_simplified();
            this->data = simplified.data;

        }

        Expression<T> get_simplified() {

            auto* constant = new Constant<T>{T{0}};
            std::vector<SQRT<T>*> squares{};

            Expression<T> result{};

            for (const auto item : this->data) {

                if (auto* ptr = dynamic_cast<SQRT<T>*>(item)) {
                    if(ptr->is_integer()) {
                        constant->data += ptr->get_algebraic();
                        continue;
                    }
                    result.data.push_back(ptr);
                } else {
                    constant->data += item->get_algebraic();
                }

            }


            result.data.push_back(constant);

            return result;
        }

    };


}

#endif //MATRIXLIB_PROJECT_EXPRESSION_H
