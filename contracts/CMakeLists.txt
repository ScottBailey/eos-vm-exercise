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


file(GLOB file_list LIST_DIRECTORIES true ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(f ${file_list})
   message("Testing ${f}")
   if(IS_DIRECTORY ${f})
      add_contract(${f})
   endif()
endforeach()
