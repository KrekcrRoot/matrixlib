

#ifndef MATRIXLIB_PROJECT_MATH_H
#define MATRIXLIB_PROJECT_MATH_H

#include <tuple>
#include <matrixlib/Expression.h>

#define variables std::tuple<Expression<T>*, Expression<T>*>

namespace matrixlib::math {


    template<typename T>
    struct QuadraticEquation {

        QuadraticEquation(T _a, T _b, T _c) : a(_a), b(_b), c(_c) {}

        Expression<T> get_discriminant() {

            Expression<T> expression{};

            expression.add(new Constant<T>{b * b});
            expression.add(new Constant<T>{-4 * a * c});

            return expression.get_simplified();

        }

        T get_vertex_parabola() {

            Expression<T> expression{};
            expression.add(new Constant<T>{ -b / (2*a) });

            return expression.calculate();

        }

        variables get_solves() {

            auto* first = new Expression<T>{};
            first->add(new Constant<T>{ -b / (2 * a) });
            first->add(new SQRT<T>{ -1 / (2 * a), this->get_discriminant().calculate() });
            first->simplify();

            auto* second = new Expression<T>{};
            second->add(new Constant<T>{ -b / (2 * a) });
            second->add(new SQRT<T>{ 1 / (2 * a), this->get_discriminant().calculate() });
            second->simplify();

            variables coordinates {
                first,
                second
            };

            return coordinates;

        }
        

        T a = 0, b = 0, c = 0;

    };


}


#endif