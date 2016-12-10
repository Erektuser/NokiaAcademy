cmake_minimum_required(VERSION 2.8.11)
project(Engine)
add_subdirectory(framework)
add_subdirectory(gui)
add_definitions("-std=c++14 -Ofast -fPIC")

add_library(${PROJECT_NAME} SHARED "Engine.cpp" $<TARGET_OBJECTS:Framework> $<TARGET_OBJECTS:Gui>)
include_directories("${PROJECT_SOURCE_DIR}/framework/include" "${PROJECT_SOURCE_DIR}/gui/include" ${GTKMM_INCLUDE_DIRS})
target_link_libraries("${PROJECT_NAME}" LINK_PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/public")






