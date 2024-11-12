//
// Created by krekcr on 11/12/24.
//

#ifndef MATRIXLIB_PROJECT_RADICAL_H
#define MATRIXLIB_PROJECT_RADICAL_H

#include <string>

namespace matrixlib::math {

    template<typename T>
    struct Radical {

        [[maybe_unused]] virtual T calculate() = 0;
        [[maybe_unused]] virtual std::string get_string() = 0;
        [[maybe_unused]] virtual bool is_complex() = 0;

        virtual ~Radical() = default;

    };

}

#endif //MATRIXLIB_PROJECT_RADICAL_H
