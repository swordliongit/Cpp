cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

# find_package(pybind11 REQUIRED)
# add_compile_definitions(MS_WIN64)
# file(GLOB SOURCES "*.cpp")
set(SOURCE_FILES src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# find_package(HDF5 REQUIRED COMPONENTS C)

# add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

