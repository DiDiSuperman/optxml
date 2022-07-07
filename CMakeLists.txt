cmake_minimum_required(VERSION 3.12)

project(optxml)

SET(CMAKE_CXX_COMPILER /usr/bin/g++)

# set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# set compile output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# find shared library
#if(UNIX)
#	find_package(kaanhbot REQUIRED PATHS /usr/kaanhbot)
#elseif(WIN32)
#	find_package(kaanhbot REQUIRED PATHS C:/kaanhbot)
#endif()
#message("kaanhbot dir: ${kaanhbot_DIR}")

# build kaanh executable
add_executable(optxml ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/tinyxml2.cpp ${PROJECT_SOURCE_DIR}/tinyxml2.h ${PROJECT_SOURCE_DIR}/encapsulation.cpp ${PROJECT_SOURCE_DIR}/encapsulation.h)
target_include_directories(optxml PUBLIC ${PROJECT_BINARY_DIR})
target_link_libraries(optxml PUBLIC ${kaanhbot_LIBRARIES})


