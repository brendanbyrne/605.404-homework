cmake_minimum_required(VERSION 2.8)
project(hw6)

#########################################
# include C++11 support
#########################################

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#########################################
# Find dependacies
#########################################

find_package(Boost)

include_directories(include
  ${Boost_INCLUDE_DIRS})

#########################################
# build
#########################################

set(SOURCE_FILES
        src/main.cpp
        src/Passenger.cpp
        src/TimelineParser.cpp
        src/Floor.cpp
        src/Elevator.cpp
	#src/Controller.cpp
	src/Building.cpp
        src/Simulator.cpp)

add_executable(sim ${SOURCE_FILES})

target_link_libraries(sim
        ${Boost_LIBRARIES})

#########################################
# installation
#########################################
#install(TARGETS sim DESTINATION bin)
