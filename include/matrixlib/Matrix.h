//
// Created by krekcr on 10/30/24.
//

#ifndef MATRIXLIB_PROJECT_MATRIX_H
#define MATRIXLIB_PROJECT_MATRIX_H

#include <numeric>

using uint = unsigned int;

namespace matrixlib
{

    template<typename T, uint height, uint width>
    struct Matrix
    {

        Matrix();
        explicit Matrix(T arr[height][width]);
        explicit Matrix(T arr[height * width]);

        void print() const;

        T get(uint x, uint y);
        T* get_p(uint x, uint y);

        T get_determinant();

        bool is_square();

        bool set(uint x, uint y, T value);
        void set(T arr[height][width]);


        static Matrix<T, height - 1, width - 1> get_submatrix(const Matrix<T, height, width>& matrix, uint i, uint j);
        Matrix<T, height - 1, width - 1> get_submatrix(uint i, uint j);


        void operator*=(T multiplier);

        Matrix<T, height, width> operator+(const Matrix<T, height, width>& matrix);
        Matrix<T, height, width> operator-(const Matrix<T, height, width>& matrix);
        Matrix<T, height, width> operator*(T multiplier);

        template<uint width_c>
        Matrix<T, height, width_c> operator*(const Matrix<T, width, width_c>& matrix) {

            auto result = Matrix<T, height, width_c> {};

            for (int row = 0; row < height; ++row) {
                for (int column = 0; column < width_c; ++column) {
                    for (int i = 0; i < width; ++i) {
                        result.data[row][column] += this->data[row][i] * matrix.data[i][column];
                    }
                }
            }

            return result;

        };

        Matrix<T, width, height> get_transposed();

        Matrix<T, height, width>* get_inverse();

        /*






         * */

        void operator+=(const Matrix<T, height, width>& matrix);
        void operator-=(const Matrix<T, height, width>& matrix);

        T data[height][width];
    };

}

#include "Matrix.hpp"

#endif //MATRIXLIB_PROJECT_MATRIX_H
