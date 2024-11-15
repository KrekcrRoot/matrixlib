//
// Created by krekcr on 10/30/24.
//

#include <iostream>
#include <cmath>
#include <random>

#include <matrixlib/Math.h>

#define template_matrix template<typename T, uint height, uint width>
#define XMatrix Matrix<T, height, width>

#define XDeterminant(typename) template<> math::Addition<typename>* Matrix<typename, 1, 1>::get_determinant() { return new math::Addition<typename>{ data[0][0] }; }

using namespace matrixlib;
using namespace std;

template_matrix
XMatrix::Matrix() {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Constant<T>{0};
        }
    }
}

template_matrix
XMatrix::Matrix(Radical<T>* arr[height][width]) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = arr[y][x];
        }
    }
}

template_matrix
XMatrix::Matrix(Radical<T>* arr[height * width]) {

    uint x = 0, y = 0;
    for (size_t i = 0; i < width * height; ++i) {
        data[y][x] = arr[i];

        ++x;
        x >= width && ({x = 0; ++y;});
    }

}

template_matrix
XMatrix::Matrix(T arr[height][width]) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Constant<T>{arr[y][x]};
        }
    }
}

template_matrix
XMatrix::Matrix(T arr[height * width]) {

    uint x = 0, y = 0;
    for (size_t i = 0; i < width * height; ++i) {
        data[y][x] = new math::Constant<T>{arr[i]};

        ++x;
        x >= width && ({x = 0; ++y;});
    }

}

template_matrix
void XMatrix::print() const
{


    for (uint y = 0; y < height; ++y) {

        std::string row {};

        if(height == 1) {
          row += "[ ";
        } else if (y == 0) {
            row += "⎡ ";
        } else if (y == height - 1) {
            row += "⎣ ";
        } else {
            row += "⎢ ";
        }

        for (uint x = 0; x < width; ++x) {
            row += this->data[y][x]->get_string();
            if(x != width - 1) row += " ";
        }

        if(height == 1) {
            row += " ]";
        } else if (y == 0) {
            row += " ⎤";
        } else if (y == height - 1) {
            row += " ⎦";
        } else {
            row += " ⎥";
        }

        cout << row << "\n";

    }

    cout << "\n";

};

template_matrix
Radical<T>* XMatrix::get(uint x, uint y) const {
    return this->data[y - 1][x - 1];
}

template_matrix
bool XMatrix::is_square() {
    return width == height;
}

template_matrix
bool XMatrix::set(uint x, uint y, Radical<T> *value) {

    if (x < 1 || x > width || y < 1 || y > height) {
        return false;
    }

    delete data[y - 1][x - 1];
    data[y - 1][x - 1] = value;

    return true;

}

template_matrix
bool XMatrix::set(uint x, uint y, T value) {

    if (x < 1 || x > width || y < 1 || y > height) {
        return false;
    }

    delete data[y - 1][x - 1];
    data[y - 1][x - 1] = new math::Constant<T> {value};

    return true;

}

template_matrix
XMatrix XMatrix::operator+(const XMatrix &matrix) {

    XMatrix result{};

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            result.set(x + 1, y + 1, new math::Addition<T>{
                    data[y][x],
                    matrix.get(x + 1, y + 1),
            });
        }
    }

    return result;

}

template_matrix
XMatrix XMatrix::operator-(const XMatrix &matrix) {

    XMatrix result{};

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            result.set(x + 1, y + 1, new math::Addition<T>{
                data[y][x],
                new math::Multiplication<T>{
                    new math::Constant<T> {-1},
                    matrix.get(x + 1, y + 1),
                }
            });
        }
    }

    return result;

}

template_matrix
XMatrix XMatrix::operator*(T multiplier) {

    XMatrix result{};

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            result.set(x + 1, y + 1, new math::Multiplication<T>{
                new math::Constant<T>{multiplier},
                data[y][x],
            });
        }
    }

    return result;

}

template_matrix
XMatrix XMatrix::operator*(Radical<T>* multiplier) {

    XMatrix result{};

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            result.set(x + 1, y + 1, new math::Multiplication<T>{
                multiplier,
                data[y][x],
            });
        }
    }

    return result;

}

template_matrix
void XMatrix::operator*=(T multiplier) {

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Multiplication<T>{
                new math::Constant<T>{multiplier},
                data[y][x],
            };
        }
    }

}

template_matrix
void XMatrix::operator*=(Radical<T>* multiplier) {

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Multiplication<T>{
                multiplier,
                data[y][x],
            };
        }
    }

}


template_matrix
void XMatrix::operator+=(const XMatrix& matrix) {

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Addition<T> {
                data[y][x],
                matrix.get(x + 1, y + 1),
            };
        }
    }

}

template_matrix
void XMatrix::operator-=(const XMatrix& matrix) {

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Addition<T> {
                data[y][x],
                new math::Multiplication<T> {
                    new math::Constant<T> {-1},
                    matrix.get(x + 1, y + 1),
                },
            };
        }
    }

}

template_matrix
[[maybe_unused]] Matrix<T, width, height> XMatrix::get_transposed() {
    Matrix<T, width, height> result {};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            result.data[x][y] = this->data[y][x];
        }
    }

    return result;
}

template_matrix
Matrix<T, height - 1, width - 1> XMatrix::get_submatrix(const XMatrix& matrix, uint i, uint j) {

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
[[maybe_unused]] Matrix<T, height - 1, width - 1> XMatrix::get_submatrix(uint i, uint j) {
    return XMatrix::get_submatrix(*this, i, j);
}

XDeterminant(float)
XDeterminant(int)
XDeterminant(uint)
XDeterminant(double)
XDeterminant(long long)
XDeterminant(long int)
XDeterminant(long double)
XDeterminant(long unsigned int)

template_matrix
math::Addition<T>* XMatrix::get_determinant() {

    if (!is_square())
        throw std::runtime_error("Matrix isn't square");

    auto* result = new math::Addition<T>{};

    for(uint x = 0; x < width; ++x) {

        result->add(new math::Multiplication<T> {
            new math::Exponentiation<T> {
                new math::Constant<T>{-1},
                new math::Constant<T>{(T) x},
            },
            data[0][x],
            get_submatrix(1, x + 1).get_determinant(),
        });

    }

    return result;

}

template_matrix
void XMatrix::calculate() {

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            data[y][x] = new math::Constant<T> {data[y][x]->calculate()};
        }
    }

}

template_matrix
XMatrix XMatrix::get_inverse() {

    if (width != height)
        throw std::runtime_error("Matrix isn't square");

    math::Addition<T>* determinant = this->get_determinant();

    if (determinant->calculate() == 0)
        throw std::runtime_error("Determinant equals zero");

    Matrix<T, height, width> transposed = this->get_transposed();

//    auto* transposed = new Matrix<T, height, width> {this->get_transposed()};

    for (uint y = 0; y < height; ++y)
    {
        for (uint x = 0; x < width; ++x)
        {
            auto* value = new math::Division<T> {
                new math::Multiplication<T> {
                    new math::Exponentiation<T> {
                        new math::Constant<T> {-1},
                        new math::Addition<T> {new math::Constant<T>{(T) x}, new math::Constant<T>{(T) y}}
                    },
                    this->get_submatrix(y + 1, x + 1).get_determinant(),
                },
                determinant,
            };

            transposed.data[x][y] = value;
        }
    }

    return transposed;

}

template_matrix
std::vector<Radical<T>*> XMatrix::get_eigenvalues() {

    if (height != width)
        return {};

    if (width == 2) {
        math::QuadraticEquation<T> equation {
            new math::Constant<T> {1},
            new math::Multiplication<T> {
                new math::Constant<T> {-1},
                new math::Addition<T> {
                    data[0][0],
                    data[1][1],
                },
            },
            new math::Addition<T> {
                new math::Multiplication<T> {
                    new math::Constant<T> {-1},
                    data[0][1],
                    data[1][0],
                },
                new math::Multiplication<T> {
                    data[0][0],
                    data[1][1],
                }
            }
        };

        auto solves = equation.get_solves();
        return std::vector<Radical<T>*> {solves.first, solves.second};
    }

}

template_matrix
XMatrix XMatrix::get_own_matrix() {

    if(!this->is_square())
        throw std::runtime_error("Matrix isn't square");

    std::vector<Radical<T>*> eigenvalues = this->get_eigenvalues();

    XMatrix result{};

    for (uint i = 0; i < width; ++i) {

        auto* x_lambda = new math::Addition<T> {
            data[0][0],
            new math::Multiplication<T> {new math::Constant<T> {-1}, eigenvalues[i]},
        };

        auto* y_lambda = new math::Multiplication<T> {
            new math::Constant<T> {-1},
            data[0][1],
        };

        if (abs(x_lambda->calculate()) < abs(y_lambda->calculate())) {

            auto* x = new math::Division<T> {
                y_lambda,
                x_lambda,
            };

            result.set(i + 1, 1, x);

            auto* y = new math::Division<T> {

                new math::Multiplication<T> {
                    x_lambda,
                    x,
                },

                y_lambda,

            };

            result.set(i + 1, 2, y);

        } else {

            auto* y = new math::Division<T> {
                x_lambda,
                y_lambda,
            };

            result.set(i + 1, 2, y);

            auto* x = new math::Division<T> {
                new math::Multiplication<T> {
                    y_lambda, y,
                },
                x_lambda
            };

            result.set(i + 1, 1, x);

        }

    }

    return result;

}

template_matrix
XMatrix XMatrix::random(Random<T> range) {

    XMatrix result {};

    std::random_device rd{};
    std::mt19937 mt199371 {rd()};
    std::uniform_int_distribution<int> distribution {(int) range.leftRange, (int) range.rightRange};


    for (uint y = 0; y < height; ++y) {
        for (uint x = 0; x < width; ++x) {
            result.set(x + 1, y + 1, new math::Constant<T>{(double) distribution(rd)});
        }
    }


    return result;

}