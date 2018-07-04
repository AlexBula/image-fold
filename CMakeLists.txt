cmake_minimum_required(VERSION 2.8.12)
# Every project needs a name.  We call this the "examples" project.
project(tooploox-task)

add_subdirectory(../dlib dlib_build)



set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -pthread -ldlib -lpng")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_LINK_FLAGS "-ldlib -lpng -pthread")


set(default_build_type "Release")


add_executable(transform img-transform.cpp main.cpp)
target_link_libraries(transform dlib::dlib)

install(TARGETS DESTINATION .)


