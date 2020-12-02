cmake_minimum_required(VERSION 3.10)

project(filterfs)

# add the executable
add_executable(filterfs src/filterfs.c)
add_definitions(-D_FILE_OFFSET_BITS=64)
target_link_libraries(filterfs fuse)
