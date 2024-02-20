cmake_minimum_required(VERSION 3.27)
project(project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(project1 main.cpp)

# Fetch spartanhero-resources from GitHub
include(FetchContent)
FetchContent_Declare(
        spartanhero-resources
        GIT_REPOSITORY https://github.com/charles-owen/spartanhero-resources.git
        GIT_TAG origin/main
)

FetchContent_MakeAvailable(spartanhero-resources)

# Copy resources into output directory
file(COPY ${spartanhero-resources_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)