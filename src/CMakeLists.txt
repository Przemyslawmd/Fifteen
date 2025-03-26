
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(
    FifteenApp 
    "Board.cpp" 
    "Controller.cpp" 
    "Entry.cpp" 
    "Fifteen.cpp" 
    "MappedValues.cpp" 
    "Message.cpp" 
    "Options.cpp" 
    "UndoMove.cpp" 
    "./GraphicBoard/GraphicBoard.cpp" 
    "./GraphicBoard/ImageProvider.cpp"
    "./GUI/GUIAbout.cpp"
    "./GUI/GUISetting.cpp"
    "./GUI/MenuBar.cpp"
    "./GUI/Panel.cpp"
    "./GUI/TilesBoard.cpp"
    "./FileBoard/IOBoard.cpp")

target_include_directories(FifteenApp PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(FifteenApp Qt6::Widgets)
