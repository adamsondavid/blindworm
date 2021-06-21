cmake_minimum_required(VERSION 3.19)
project(blindworm_compiler)
set(CMAKE_CXX_STANDARD 14)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(llvm_libs support core irreader)

set(SOURCES
    src/lexer/handwrittenlexer.cpp
    src/lexer/flexlexer.cpp
    src/lexer/token.cpp
    src/parser/handwrittenparser.cpp
    src/parser/bisonparser.cpp
)

add_library(${PROJECT_NAME}_lib ${SOURCES})
target_link_libraries(${PROJECT_NAME}_lib ${llvm_libs})

add_executable(bwc src/main.cpp)
target_link_libraries(bwc ${PROJECT_NAME}_lib ${llvm_libs})

add_subdirectory(test)
