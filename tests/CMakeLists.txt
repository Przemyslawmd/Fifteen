
cmake_minimum_required(VERSION 3.14)
project(FifteenTests)

set(CMAKE_CXX_STANDARD 17)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(SRC "../Project/")

find_package(Qt5 REQUIRED Core)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  FifteenTests
  InitialBoard.cpp
  ${SRC}/Board.cpp
  ${SRC}/MappedValues.cpp
  
)
target_link_libraries(
  FifteenTests
  GTest::gtest_main
  Qt5::Core
)

include(GoogleTest)
gtest_discover_tests(FifteenTests)

