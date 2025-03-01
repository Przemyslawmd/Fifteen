project(FifteenTests)

set(SRC "../src/")

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

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
  ${SRC}/UndoMove.cpp
  ${SRC}/GraphicBoard/GraphicBoard.cpp
  ${SRC}/GraphicBoard/ImageProvider.cpp
  ${SRC}/FileBoard/IOBoard.cpp
)

target_include_directories(
  FifteenTests
  PRIVATE
  ${SRC}
)

target_link_libraries(
  FifteenTests
  GTest::gtest_main
  Qt6::Core
  Qt6::Gui
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(FifteenTests)

