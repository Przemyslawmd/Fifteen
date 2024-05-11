project(Fifteen)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

aux_source_directory(. DIR_SRC)
aux_source_directory(./GraphicBoard GRAPHIC_BOARD)
aux_source_directory(./GUI GUI)
aux_source_directory(./FileBoard FILE_BOARD)
add_executable(Fifteen ${DIR_SRC} ${GRAPHIC_BOARD} ${GUI} ${FILE_BOARD})

target_include_directories(Fifteen PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(Fifteen Qt${QT_VERSION_MAJOR}::Widgets)
