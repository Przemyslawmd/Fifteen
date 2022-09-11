cmake_minimum_required(VERSION 3.10)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


project(Fifteen)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

aux_source_directory(. DIR_SRC)
aux_source_directory(./GraphicBoard GRAPHIC_BOARD)
aux_source_directory(./GUI GUI)
aux_source_directory(./FileBoard FILE_BOARD)
add_executable(Fifteen ${DIR_SRC} ${GRAPHIC_BOARD} ${GUI} ${FILE_BOARD})

target_include_directories(Fifteen PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(Fifteen Qt5::Widgets)
