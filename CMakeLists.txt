cmake_minimum_required(VERSION 2.8)
project(stock-market-simulator)

aux_source_directory(src SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
