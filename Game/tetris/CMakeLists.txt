add_executable(tetris main.cpp)

target_include_directories(tetris PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(tetris PUBLIC cxx_std_17)
target_compile_definitions(tetris PRIVATE SFML_STATIC)

target_link_libraries(tetris ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})