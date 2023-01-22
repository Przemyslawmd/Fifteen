
cmake_minimum_required(VERSION 3.14)
project(FifteenTests)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(SRC "../src/")

find_package(Qt5 REQUIRED Core)
find_package(Qt5 REQUIRED COMPONENTS Gui) 

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

add_executable(
  FifteenTests
  TestErrorRestore.cpp
  TestGraphicBoard.cpp
  TestInitialBoard.cpp
  TestRandomBoard.cpp
  TestChangeBoard.cpp
  TestMoves.cpp
  TestSaveNumericBoard.cpp
  ${SRC}/Board.cpp
  ${SRC}/Controller.cpp
  ${SRC}/MappedValues.cpp
  ${SRC}/Message.cpp
  ${SRC}/Options.cpp
  ${SRC}/GraphicBoard/GraphicBoard.cpp
  ${SRC}/GraphicBoard/ImageProvider.cpp
  ${SRC}/FileBoard/IOBoard.cpp
)

target_link_libraries(
  FifteenTests
  GTest::gtest_main
  Qt5::Core
  Qt5::Gui
)

include(GoogleTest)
gtest_discover_tests(FifteenTests)

