cmake_minimum_required(VERSION 2.8)
project(homework1)

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

include_directories(include ${Boost_INCLUDE_DIRS})
#########################################
# build
#########################################
add_executable(tictactoe src/TicTacToe.cc src/Tile.cc src/Gameboard.cc src/GameState.cc src/Opponent.cc)
target_link_libraries(tictactoe ${Boost_LIBRARIES})

#########################################
# installation
#########################################
install(TARGETS tictactoe DESTINATION bin)
