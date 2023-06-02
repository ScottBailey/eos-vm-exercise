cmake_minimum_required(VERSION 3.26)

project(eos-vm-investigation)

include(common.cmake)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(depends)
add_subdirectory(driver)

# Because contracts are built with the CDT toolchain, they are added as an external project.
find_package(cdt REQUIRED)
include(ExternalProject)
ExternalProject_Add(
   contracts
   SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/contracts
   BINARY_DIR      ${CMAKE_BINARY_DIR}/contracts
   CMAKE_ARGS      -DCMAKE_TOOLCHAIN_FILE=${CDT_ROOT}/lib/cmake/cdt/CDTWasmToolchain.cmake
   UPDATE_COMMAND  ""
   PATCH_COMMAND   ""
   TEST_COMMAND    ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS    1
)
