cmake_minimum_required(VERSION 3.22)
project("MaestroControl")
# Find python and Boost - both are required dependencies
find_package(PythonLibs 3.9 REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

# Without this, any build libraries automatically have names "lib{x}.so"
add_library(MaestroControl MODULE lib.cpp)

# Set up the libraries and header search paths for this target
target_link_libraries(MaestroControl ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(MaestroControl PRIVATE ${PYTHON_INCLUDE_DIRS})
