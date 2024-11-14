

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

        QuadraticEquation(Radical<T>* _a, Radical<T>* _b, Radical<T>* _c)
            : a{_a}, b{_b}, c{_c}
        {}

        QuadraticEquation(T _a, T _b, T _c) {
            a = new Constant<T> {_a};
            b = new Constant<T> {_b};
            c = new Constant<T> {_c};
        }

        Radical<T>* get_discriminant() {
            auto* expression = new Addition<T> {
                new Multiplication<T> { b, b },
                new Multiplication<T> { new Constant<T> {-4}, a, c },
            };

            return expression;
        }

        [[maybe_unused]] Radical<T>* get_vertex_parabola() {

            auto* expression = new Division<float> {
                new Multiplication<T> {new Constant<T>{ -1 }, b},
                new Multiplication<T> {new Constant<T>{ 2 }, a},
            };

            return expression;

        }

        std::pair<Radical<T>*, Radical<T>*> get_solves() {

            auto* first = new Division<T> {
                new Addition<T> {
                    new Multiplication<T> {new Constant<T> {-1}, b},
                    new SQRT<T> {this->get_discriminant()},
                },
                new Multiplication<T> { new Constant<T> {2}, a },
            };

            auto* second = new Division<T> {
                new Addition<T> {
                    new Multiplication<T> {new Constant<T> {-1}, b},
                    new Multiplication<T> {
                        new Constant<T> {-1}, new SQRT<T> {this->get_discriminant()}
                    },
                },
                new Multiplication<T> { new Constant<T> {2}, a },
            };

            std::pair<Radical<T>*, Radical<T>*> coordinates {
                first,
                second
            };

            return coordinates;

        }
        

        Radical<T>* a;
        Radical<T>* b;
        Radical<T>* c;

    };


}


#endif