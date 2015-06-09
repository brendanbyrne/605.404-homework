cmake_minimum_required(VERSION 2.8)
project(hw2)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_files)
message("CMAKE_MODULE_PATH: \"${CMAKE_MODULE_PATH}\"")
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
#find_package(Boost)
#include_directories(${Boost_INCLUDE_DIRS})

find_package(libConfig)
#########################################
# build
#########################################
add_executable(ranker src/HandRank.cc)
target_link_libraries(ranker ${LIBCONFIGPP_LIBRARIES})
#target_link_libraries(tictactoe ${Boost_LIBRARIES})


#########################################
# installation
#########################################
#install(TARGETS tictactoe DESTINATION bin)
