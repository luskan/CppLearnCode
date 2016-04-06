cmake_minimum_required(VERSION 3.3)
project(TestCpp1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -pedantic -pthread")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
#set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib/)
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/local/boost_1_60_0/boost")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/local/boost_1_60_0/stage/lib")
find_package(Boost 1.60.0 COMPONENTS regex system filesystem REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(SOURCE_FILES main.cpp cppprimer_ch8.cpp cppprimer_ch9.cpp cppprimer_ch9.h
        cppprimer_ch11.cpp cppprimer_ch11.h
        cppprimer_ch12.cpp cppprimer_ch12.h)
add_executable(TestCpp1 ${SOURCE_FILES})

if(Boost_FOUND)
    target_link_libraries(TestCpp1 ${Boost_LIBRARIES})
endif()