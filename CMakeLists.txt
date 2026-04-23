
cmake_minimum_required(VERSION 3.10)
project(FileStorage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags for optimization
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wpedantic")

# Add executable
add_executable(code main.cpp)

# Copy the executable to the source directory after building
add_custom_command(TARGET code POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:code> ${CMAKE_SOURCE_DIR}/code
    COMMENT "Copying executable to source directory"
)
