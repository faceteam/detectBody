project(detectBody)
cmake_minimum_required(VERSION 3.0)
find_package(OpenCV REQUIRED)

file(GLOB HEADERS *.h*)
file(GLOB SOURCES *.c*)
set(ALL_FILES ${HEADERS} ${SOURCES})

add_executable(${PROJECT_NAME} ${ALL_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
