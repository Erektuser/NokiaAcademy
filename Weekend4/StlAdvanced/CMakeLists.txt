cmake_minimum_required(VERSION 2.8.11)

macro (DefineProject Slide)

project(${Slide})
ADD_EXECUTABLE("${PROJECT_NAME}" ${Slide}.cpp)
target_link_libraries(${PROJECT_NAME} -pthread)

endmacro (DefineProject)

macro (DefineProjectNoMain Slide)

project(${Slide})
ADD_EXECUTABLE("${PROJECT_NAME}" ${Slide}.cpp main.cpp)
target_link_libraries(${PROJECT_NAME} -pthread)

endmacro (DefineProjectNoMain)



DefineProject(slide73)
DefineProject(slide75)
DefineProject(slide84)
DefineProject(slide90)
