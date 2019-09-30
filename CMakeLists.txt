cmake_minimum_required (VERSION 2.8.11)
project (cake)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED YES)
set(CXX_EXTENSIONS NO)
set(PROJECT_HOME ${CMAKE_SOURCE_DIR} )

add_subdirectory (./ca_packfile)
add_subdirectory (./ca_libcake)
add_subdirectory (./ca_test)
add_subdirectory (./ca_cake)

