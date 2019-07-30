cmake_minimum_required (VERSION 2.8.11)
project (cake)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED YES)
set(CXX_EXTENSIONS NO)

add_subdirectory (./ca_libcake)
add_subdirectory (./ca_test)
add_subdirectory (./ca_cake)

