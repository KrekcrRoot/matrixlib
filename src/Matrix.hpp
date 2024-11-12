//
// Created by krekcr on 10/30/24.
//

#include <iostream>
#include <cmath>

#include <matrixlib/Math.h>

#define template_matrix template<typename T, uint height, uint width>
#define XMatrix Matrix<T, height, width>

using namespace matrixlib;
using namespace std;

template_matrix
XMatrix::Matrix() {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            this->data[y][x] = 0;
        }
    }
};

template_matrix
XMatrix::Matrix(T arr[height][width]) {

    if (!is_arithmetic<T>::value)
        throw std::runtime_error("Typename of matrix isn't arithmetic");

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            this->data[y][x] = arr[y][x];
        }
    }

}

template_matrix
XMatrix::Matrix(T arr[height * width]) {

    if (!is_arithmetic<T>::value)
        throw std::runtime_error("Typename of matrix isn't arithmetic");

    uint x = 0, y = 0;
    for (size_t i = 0; i < width * height; ++i) {
        this->data[y][x] = arr[i];

        ++x;
        if(x >= width) {
            x = 0;
            ++y;
        }


    }

}

template_matrix
void XMatrix::print() const
{

    for (uint y = 0; y < height; ++y) {
        for (uint x = 0; x < width; ++x) {
            cout << this->data[y][x] << " ";
        }
        cout << "\n";
    }

};

template_matrix
XMatrix XMatrix::operator+(const XMatrix &matrix) {

    Matrix<T, height, width> result{};

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            result.data[y][x] = this->data[y][x] + matrix.data[y][x];
        }
    }

    return result;

}

template_matrix
XMatrix XMatrix::operator-(const XMatrix &matrix) {

    Matrix<T, height, width> result{};

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            result.data[y][x] = this->data[y][x] - matrix.data[y][x];
        }
    }

    return result;

}

template_matrix
XMatrix XMatrix::operator*(T multiplier) {

    Matrix<T, height, width> result{};

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            result.data[y][x] = this->data[y][x] * multiplier;
        }
    }

    return result;

}

template_matrix
void XMatrix::operator*=(T multiplier) {

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            this->data[y][x] *= multiplier;
        }
    }

}

template_matrix
XMatrix* XMatrix::get_inverse() {

    if (width != height)
        return nullptr;

    const T determinant = this->get_determinant();

    if (determinant == 0)
        return nullptr;

    auto* transposed = new Matrix<T, height, width> {this->get_transposed()};

    for (uint y = 0; y < height; ++y)
    {
        for (uint x = 0; x < width; ++x)
        {
//            Expression<T> expression{};
//            expression.add(new Constant<T>{
//                std::pow(-1, x) * (this->get_submatrix(y + 1, x + 1).get_determinant()) / determinant
//            });

//            std::cout << expression.get_string() << "\n";

            transposed->data[x][y] = std::pow(-1, x + y) * (this->get_submatrix(y + 1, x + 1).get_determinant()) / determinant;
        }
    }

    return transposed;

}

template_matrix
T XMatrix::get(uint x, uint y) {
    return this->data[y - 1][x - 1];
}

template_matrix
T* XMatrix::get_p(uint x, uint y) {
    return &this->data[y - 1][x - 1];
}

template_matrix
bool XMatrix::set(uint x, uint y, T value) {

    if (x > width || y > height)
        return false;

    this->data[y - 1][x - 1] = value;

    return true;

}

template_matrix
void XMatrix::set(T arr[height][width]) {

    for (uint y = 0; y < height; ++y)
    {
        for (uint x = 0; x < width; ++x)
        {
            this->data[y][x] = arr[y][x];
        }
    }

}

template_matrix
void XMatrix::operator+=(const XMatrix &matrix) {

    for (uint y = 0; y < height; ++y)
    {
        for (uint x = 0; x < width; ++x)
        {
            this->data[y][x] += matrix.data[y][x];
        }
    }

}

template_matrix
void XMatrix::operator-=(const XMatrix &matrix) {

    for (uint y = 0; y < height; ++y)
    {
        for (uint x = 0; x < width; ++x)
        {
            this->data[y][x] -= matrix.data[y][x];
        }
    }

}

template_matrix
bool XMatrix::is_square() {
    return width == height;
}

template_matrix
Matrix<T, width, height> XMatrix::get_transposed() {
    Matrix<T, width, height> result {};

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            result.data[x][y] = this->data[y][x];

        }

    }

    return result;
}

template_matrix
Matrix<T, height - 1, width - 1> XMatrix::get_submatrix(const Matrix<T, height, width>& matrix, uint i, uint j) {

    if(height < 1 || width < 1) {
        throw std::runtime_error("Matrix can't be less than zero");
    }

    Matrix<T, height - 1, width - 1> result{};

    for (uint y = 0; y < height; ++y) {
        for (uint x = 0; x < width; ++x) {
            uint posX{x}, posY{y};
            if(x == (j - 1) || y == (i -1)) continue;

            if(x >= j) posX -= 1;
            if(y >= i) posY -= 1;

            result.data[posY][posX] = matrix.data[y][x];
        }
    }

    return result;

}

template_matrix
Matrix<T, height - 1, width -1> XMatrix::get_submatrix(uint i, uint j) {
    return XMatrix::get_submatrix(*this, i, j);
}

template<>
float Matrix<float, 2, 2>::get_determinant() {
    return this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0];
}

template<>
float Matrix<float, 1, 1>::get_determinant() {
    return this->data[0][0];
}

template<>
double Matrix<double, 2, 2>::get_determinant() {
    return this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0];
}

template<>
double Matrix<double, 1, 1>::get_determinant() {
    return this->data[0][0];
}

template_matrix
T XMatrix::get_determinant() {

    if (!is_arithmetic<T>::value)
        throw std::runtime_error("Typename of determinant isn't arithmetic");

    if (!is_square())
        throw std::runtime_error("Matrix isn't square");

    T result{};

    for(uint x = 0; x < width; ++x) {

        result += pow(-1, x) * this->data[0][x] * this->get_submatrix(1, x + 1).get_determinant();

    }

    return result;

}

