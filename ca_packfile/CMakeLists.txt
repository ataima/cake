# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)



project (ca_qxmlc)

include_directories(./inc)


 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")

ADD_EXECUTABLE(ca_packfile ${SOURCES})

install ( TARGETS ca_packfile DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")



add_custom_command (
    TARGET ca_packfile
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target( pack_files
    DEPENDS  ca_packfile
    COMMAND  ${CMAKE_INSTALL_PREFIX}/ca_packfile  --out ca_libxmlca/src/capackedfiles.cpp ca_libxmlca/src/caminiXml.cpp ca_libxmlca/inc/caminiXml.h 
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    COMMENT "run packfile on minixml "
)

