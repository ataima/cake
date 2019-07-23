# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)



project (ca_libcake)

include_directories(./inc )
 
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")
file(GLOB HEADERS "./inc/*.h")


add_library (cake  STATIC ${SOURCES} inc/cacakemanager.h src/cacakemanager.cpp src/caconfenv.cpp inc/caconfenv.h)

install ( TARGETS cake DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")

add_custom_command (
    TARGET cake
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh
)

add_custom_target(
    generate_source_from_xml
    COMMAND make -C ../templatexml all
)
add_dependencies( cake  generate_source_from_xml )

