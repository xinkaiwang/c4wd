cmake_minimum_required(VERSION 3.1.0)

project(C4wd VERSION 1.0)

option(USE_MYMATH "Use tutorial privided math implementation" ON)

configure_file(app_config.h.in app_config.h)


# add_subdirectory(MathFunctions)

if (USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
#  list(APPEND EXTRA_INCLUDES MathFunctions)
endif()

add_executable(C4wd hello_world.cpp)

target_link_libraries(C4wd PUBLIC ${EXTRA_LIBS})

target_include_directories(C4wd 
                           PUBLIC 
                           "${PROJECT_BINARY_DIR}"
#                           "${EXTRA_INCLUDES}"
                           )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

install(TARGETS C4wd DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/app_config.h"
    DESTINATION include)
