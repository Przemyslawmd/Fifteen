project(FifteenApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

aux_source_directory(. DIR_SRC)
aux_source_directory(./GraphicBoard GRAPHIC_BOARD)
aux_source_directory(./GUI GUI)
aux_source_directory(./FileBoard FILE_BOARD)
add_executable(FifteenApp ${DIR_SRC} ${GRAPHIC_BOARD} ${GUI} ${FILE_BOARD})

target_include_directories(FifteenApp PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(FifteenApp Qt6::Widgets)
