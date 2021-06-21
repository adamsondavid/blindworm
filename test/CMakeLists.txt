add_subdirectory(vendor/googletest)

add_executable(${PROJECT_NAME}_test lexer_test.cpp parser_test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib gtest gtest_main)
