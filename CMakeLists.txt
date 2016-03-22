cmake_minimum_required(VERSION 3.4)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS program_options filesystem system REQUIRED)

set(SOURCES main.cpp replace.cpp options.cpp include/options.hpp include/replace.hpp)
include_directories("include")
add_executable(replace main.cpp replace.cpp options.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(replace ${Boost_LIBRARIES})
endif()
