cmake_minimum_required(VERSION 2.8)

project(DisplayImage)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -D OS_UNIX")

message("Working directory: ${CMAKE_SOURCE_DIR}")

#########################################
#### Project sources & includes #########
#########################################

file(GLOB_RECURSE DisplayImage_SRC
      "*.h"
      "*.cpp"
      )
list(REMOVE_ITEM DisplayImage_SRC src/Main.cpp)

#########################################
#### Executable and linked libraries ####
#########################################
add_executable(DisplayImage Main.cpp)
add_library(displayImageLib ${DisplayImage_SRC})
target_link_libraries(DisplayImage displayImageLib)
find_package(OpenCV REQUIRED)
target_link_libraries(DisplayImage ${OpenCV_LIBS})

#########################################
##### Tests #############################
#########################################
# Find test files
  file(GLOB_RECURSE Tests_SRC
      "../unitTests/*.h"
      "../unitTests/*.cpp"
      )

## Create the executable and link it with project libs
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Threads)

add_executable(runTests ${Tests_SRC})
target_link_libraries(runTests ${OpenCV_LIBS})
target_link_libraries(runTests displayImageLib)
target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES})
target_link_libraries(runTests ${CMAKE_THREAD_LIBS_INIT})

# Add the make test option
add_test(UnitTests runTests)
