cmake_minimum_required(VERSION 2.8)
project(RhIODemo)

find_package(catkin REQUIRED COMPONENTS
    RhIOServer
  )

# What is published by the 'RhIOClient package'
catkin_package(
    CATKIN_DEPENDS RhIOServer
)

# Include sources directory
include_directories(src ${catkin_INCLUDE_DIRS})

# Sources files
set(SOURCES
    main.cpp
)

# Enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Enable compiler Warning
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall")

# Build Server and Client as shared library
add_executable(rhioDemo main.cpp)
target_link_libraries(rhioDemo ${catkin_LIBRARIES})
