set(CMAKE_CXX_STANDARD 11)

add_library(wiringpp pins.cpp)

target_include_directories(wiringpp
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )
