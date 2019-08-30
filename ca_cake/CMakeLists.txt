# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)

project (ca_cake)

include_directories(./inc)
include_directories(../ca_libcake/inc)


 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")

ADD_EXECUTABLE(ca_cake ${SOURCES})

install ( TARGETS ca_cake DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")


target_link_libraries (ca_cake cake )
target_link_libraries (ca_cake pthread )


add_custom_command (
    TARGET ca_cake
    PRE_BUILD
    COMMAND ${PROJECT_HOME}/beauty.sh ${CMAKE_CURRENT_SOURCE_DIR}
)


