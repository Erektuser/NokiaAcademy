cmake_minimum_required(VERSION 2.8.11)
PROJECT(Tests)
add_definitions("-std=c++14 -Ofast -fPIC")
add_subdirectory(googletest)

AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}" Tests_SOURCES)
AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/engine" EngineTest_SOURCES)
AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/solution" SolutionTest_SOURCES)

ADD_EXECUTABLE("${PROJECT_NAME}" ${Tests_SOURCES} ${EngineTest_SOURCES} ${SolutionTest_SOURCES})

target_link_libraries("${PROJECT_NAME}" PRIVATE gmock gmock_main) 
target_link_libraries("${PROJECT_NAME}" LINK_PUBLIC Solution)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}" "${gmock_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}/include")

add_definitions(-DENABLE_CFUNC_MOCKING_SUPPORT -DGTEST_DONT_DEFINE_TEST -DDEBUG_TESTS -Wno-virtual-move-assign)

add_custom_target(test
    COMMAND "${PROJECT_NAME}"
    DEPENDS "${PROJECT_NAME}"
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
