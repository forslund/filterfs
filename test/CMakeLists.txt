cmake_minimum_required(VERSION 3.7)

project(filterfs-test)

# add the executable
add_executable(test-filterfs tests.c ../src/filter.c)

add_test(test test-filterfs)
