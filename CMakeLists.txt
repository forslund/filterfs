cmake_minimum_required(VERSION 3.7)

project(filterfs)

# add the executable
add_executable(filterfs src/filterfs.c src/filter.c)
add_definitions(-D_FILE_OFFSET_BITS=64)
target_link_libraries(filterfs fuse)
