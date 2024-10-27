cmake_minimum_required(VERSION 3.0)

project(Validation)

find_package(glm REQUIRED)

add_executable(val 
    validate.cpp
)

target_link_libraries(val PRIVATE glm)
