cmake_minimum_required(VERSION 3.29)
project(matrixlib)

include_directories(include)

file(GLOB SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*.hpp
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

set(CMAKE_CXX_STANDARD 20)


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})