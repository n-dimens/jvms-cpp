cmake_minimum_required(VERSION 3.19)
project(jvms)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.67.0 COMPONENTS filesystem program_options)

set(SOURCE_FILES
        main.cpp ClassFileReader.h ClassFileReader.cpp)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif ()