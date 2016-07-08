cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11 -Wall)

project(deobf CXX)

file(GLOB CC_FILES *.cc)

add_executable(deobf ${CC_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "CYGWIN")
  target_link_libraries(deobf libstdc++.a)
else ()
  target_link_libraries(deobf -lltdl -ldl)
endif ()
