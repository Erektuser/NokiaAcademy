cmake_minimum_required(VERSION 3.0.2)
project(Comunicator)

add_subdirectory(engine)
add_subdirectory(solution)
add_subdirectory(tests)

include_directories("${PROJECT_SOURCE_DIR}")

add_definitions("-std=c++14 -Ofast -fPIC")

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Engine Solution -pthread)
