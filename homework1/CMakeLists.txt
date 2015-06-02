cmake_minimum_required(VERSION 2.8)
project(homework1)

add_executable(tictactoe src/main.cc src/tictactoe_gamestate.cc)

install(TARGETS tictactoe DESTINATION bin)