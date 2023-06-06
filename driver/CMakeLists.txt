add_executable(driver main.cpp static_analysis_visitor.hpp)
target_include_directories(driver PRIVATE . )
target_link_libraries(driver eos-vm)
