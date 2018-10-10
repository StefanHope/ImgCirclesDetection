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
add_library(displayImageLib ${DisplayImage_SRC})
add_executable(DisplayImage Main.cpp)
target_link_libraries(DisplayImage displayImageLib)
find_package(OpenCV REQUIRED)
target_link_libraries(DisplayImage ${OpenCV_LIBS})

#########################################
##### Tests #############################
#########################################
enable_testing()

# Find test files
  file(GLOB_RECURSE Tests_SRC
      "../unitTests/*.h"
      "../unitTests/*.cpp"
      )

## Create the executable and link it with project libs
add_executable(runTests ${Tests_SRC})
target_link_libraries(runTests gtest pthread)
target_link_libraries(runTests displayImageLib)
target_link_libraries(runTests ${OpenCV_LIBS})

# Add the make test option
add_test(UnitTests runTests)
