
#ifndef MATRIXLIB_PROJECT_RADICAL_H
#define MATRIXLIB_PROJECT_RADICAL_H

#include <string>

namespace matrixlib {


    template<typename T>
    struct Radical {

        [[maybe_unused]] virtual T get_algebraic() const = 0;
        [[maybe_unused]] [[nodiscard]] virtual std::string get_string() const = 0;

    };


}

#endif