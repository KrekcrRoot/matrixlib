//
// Created by krekcr on 11/15/24.
//

#ifndef MATRIXLIB_PROJECT_RANDOM_H
#define MATRIXLIB_PROJECT_RANDOM_H

namespace matrixlib::random {

    template<typename T>
    struct Random {

        explicit Random(T _leftRange, T _rightRange)
        {
            this->leftRange = (T) _leftRange;
            this->rightRange = (T) _rightRange;

        }


        T leftRange, rightRange;


    };

}

#endif //MATRIXLIB_PROJECT_RANDOM_H
