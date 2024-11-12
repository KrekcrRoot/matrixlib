//
// Created by krekcr on 10/30/24.
//

#ifndef MATRIXLIB_PROJECT_MATRIX_H
#define MATRIXLIB_PROJECT_MATRIX_H

#include <numeric>

#include <matrixlib/math/Radical.h>
#include <matrixlib/math/Addition.h>
#include <matrixlib/math/Multiplication.h>

using uint = unsigned int;

namespace matrixlib
{

    using math::Radical;

    template<typename T, uint height, uint width>
    struct Matrix
    {

        Matrix();

        explicit Matrix(Radical<T>* arr[height][width]);
        explicit Matrix(Radical<T>* arr[height * width]);

        explicit Matrix(T arr[height][width]);
        explicit Matrix(T arr[height * width]);

        [[maybe_unused]] void print() const;

        [[maybe_unused]] [[nodiscard]] Radical<T>* get(uint x, uint y) const;

        [[maybe_unused]] bool is_square();

        [[maybe_unused]] bool set(uint x, uint y, Radical<T>* value);
        [[maybe_unused]] bool set(uint x, uint y, T value);

        [[maybe_unused]] Matrix<T, height, width> operator+(const Matrix<T, height, width>& matrix);
        [[maybe_unused]] Matrix<T, height, width> operator-(const Matrix<T, height, width>& matrix);

        [[maybe_unused]] Matrix<T, height, width> operator*(T multiplier);
        [[maybe_unused]] Matrix<T, height, width> operator*(Radical<T>* multiplier);
        [[maybe_unused]] void operator*=(T multiplier);
        [[maybe_unused]] void operator*=(Radical<T>* multiplier);

        [[maybe_unused]] void operator+=(const Matrix<T, height, width>& matrix);
        [[maybe_unused]] void operator-=(const Matrix<T, height, width>& matrix);

        [[maybe_unused]] Matrix<T, width, height> get_transposed();

        [[maybe_unused]] static Matrix<T, height - 1, width - 1> get_submatrix(const Matrix<T, height, width>& matrix, uint i, uint j);

        [[maybe_unused]] Matrix<T, height - 1, width - 1> get_submatrix(uint i, uint j);

        [[maybe_unused]] math::Addition<T>* get_determinant();

        [[maybe_unused]] Matrix<T, height, width>* get_inverse();

        [[maybe_unused]] void calculate();

        template<uint width_c>
        Matrix<T, height, width_c> operator*(const Matrix<T, width, width_c>& matrix) {

            auto result = Matrix<T, height, width_c> {};

            for (int row = 0; row < height; ++row) {
                for (int column = 0; column < width_c; ++column) {
                    auto* value = new math::Addition<T>{};
                    for (int i = 0; i < width; ++i) {
                        value->add(new math::Multiplication<T>{
                            this->data[row][i],
                            matrix.data[i][column],
                        });
                    }
                    result.data[row][column] = value;
                }
            }

            return result;

        };

        /*




*/

        Radical<T>* data[height][width];
    };

}

#include "Matrix.hpp"

#endif //MATRIXLIB_PROJECT_MATRIX_H
