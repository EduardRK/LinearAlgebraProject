cmake_minimum_required(VERSION 3.27.6)
project(Main VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -ggdb)
#add_compile_options(-Wall -Ofast)

set(HDRS headers)
set(SRCS sources)

set(ARCH architecture)
set(LIBR libraries)
set(VRBL variables)

include_directories(${HDRS}/${ARCH})
include_directories(${HDRS}/${LIBR})
include_directories(${HDRS}/${VRBL})

set(ARCH_ ${HDRS}/${ARCH}/architecture.hpp ${SRCS}/${ARCH}/architecture.cpp)
set(WRITE_ ${HDRS}/${LIBR}/Writer.hpp ${SRCS}/${LIBR}/Writer.cpp)
set(READ_ ${HDRS}/${LIBR}/Reader.hpp ${SRCS}/${LIBR}/Reader.cpp)
set(PARSER_ ${HDRS}/${LIBR}/Parser.hpp ${SRCS}/${LIBR}/Parser.cpp)
set(VLDT_ ${HDRS}/${LIBR}/Validator.hpp ${SRCS}/${LIBR}/Validator.cpp)
set(VRBL_ ${HDRS}/${VRBL}/variables.hpp ${SRCS}/${VRBL}/variables.cpp)

add_library(arch_lib STATIC ${ARCH_})
add_library(write_lib STATIC ${WRITE_})
add_library(read_lib STATIC ${READ_})
add_library(parser_lib STATIC ${PARSER_})
add_library(validator_lib STATIC ${VLDT_})
add_library(vrbl_lib STATIC ${VRBL_})

add_executable(${PROJECT_NAME} main.cpp)

# .hpp -> INTERFACE, .cpp -> PRIVATE, .hpp & .cpp -> PUBLIC
target_link_libraries(arch_lib PUBLIC write_lib)
target_link_libraries(arch_lib PUBLIC read_lib)
target_link_libraries(arch_lib PUBLIC parser_lib)
target_link_libraries(arch_lib PUBLIC validator_lib)
target_link_libraries(arch_lib INTERFACE vrbl_lib)
target_link_libraries(vrbl_lib INTERFACE write_lib)
target_link_libraries(vrbl_lib INTERFACE read_lib)
target_link_libraries(vrbl_lib INTERFACE parser_lib)
target_link_libraries(vrbl_lib INTERFACE validator_lib)

target_link_libraries(${PROJECT_NAME} PRIVATE arch_lib)