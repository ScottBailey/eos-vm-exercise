cmake_minimum_required(VERSION 3.26)

project(contracts)

find_package(cdt REQUIRED)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror" )

function(add_contract path)
   cmake_path(GET path FILENAME target_name)
   file(GLOB src_cpp ${path}/*.cpp)
   file(GLOB src_hpp ${path}/*.hpp)
   message(STATUS "Adding `${target_name}` from ${path}")
   add_executable(${target_name} ${src_cpp} ${src_hpp})
endfunction()

add_contract(hello)
add_contract(exit)
add_contract(print_string)
