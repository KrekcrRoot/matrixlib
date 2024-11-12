

#ifndef MATRIXLIB_PROJECT_MATH_H
#define MATRIXLIB_PROJECT_MATH_H

#include <tuple>
#include <matrixlib/math/Radical.h>
#include <matrixlib/math/Constant.h>
#include <matrixlib/math/Addition.h>
#include <matrixlib/math/Multiplication.h>
#include <matrixlib/math/Division.h>
#include <matrixlib/math/SQRT.h>
#include <matrixlib/math/Exponentiation.h>

namespace matrixlib::math {


    template<typename T>
    struct QuadraticEquation {

        QuadraticEquation(T _a, T _b, T _c) : a(_a), b(_b), c(_c) {}

        Radical<T> get_discriminant() {
            Addition<T> expression{
                new Multiplication<T> {
                    new Constant<T> {b},
                    new Constant<T> {b},
                },
                new Multiplication<T> {
                    new Constant<T> {-4},
                    new Constant<T> {a},
                    new Constant<T> {c},
                },
            };

            return expression;

        }

        Radical<T> get_vertex_parabola() {

            Division<float> expression {
                new Multiplication<T> {new Constant<T>{ -1 }, new Constant<T>{ b }},
                new Multiplication<T> {new Constant<T>{ 2 }, new Constant<T>{ a }},
            };

            return expression;

        }

        std::pair<Radical<T>, Radical<T>> get_solves() {

            Division<T> first {
                new Addition<T> {
                    new Constant<T> {-b}, new SQRT<T> {this->get_discriminant()},
                },
                new Multiplication<T> {2, a},
            };

            Division<T> second {
                new Addition<T> {
                    new Constant<T> {-b}, new Multiplication<float> {
                        -1, new SQRT<T> {this->get_discriminant()}
                    },
                },
                new Multiplication<T> {2, a},
            };

            std::pair<Radical<T>, Radical<T>> coordinates {
                first,
                second
            };

            return coordinates;

        }
        

        T a = 0, b = 0, c = 0;

    };


}


#endif