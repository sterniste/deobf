cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11 -Wall)

project(deobf_guid CXX)

file(GLOB CC_FILES *.cc)

add_executable(deobf_guid ${CC_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "CYGWIN")
  target_link_libraries(deobf_guid libstdc++.a)
else ()
  target_link_libraries(deobf_guid -lltdl -ldl)
endif ()
