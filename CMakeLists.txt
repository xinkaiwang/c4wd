cmake_minimum_required(VERSION 3.1.0)

project(C4wd VERSION 1.0)

option(USE_MYMATH "Use tutorial privided math implementation" ON)

configure_file(app_config.h.in app_config.h)


add_subdirectory(wiringpp)
list(APPEND EXTRA_LIBS wiringpp)
#list(APPEND EXTRA_INCLUDES wiringpp)

if (USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
#  list(APPEND EXTRA_INCLUDES MathFunctions)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(C4wd hello_world.cpp)

set_target_properties(C4wd PROPERTIES
            CXX_STANDARD 14
            CXX_EXTENSIONS OFF
            )

add_executable(blink blink.c)
target_link_libraries(blink PUBLIC wiringPi)
add_executable(blink2 blink2.cpp)
target_link_libraries(blink2 PUBLIC wiringPi wiringpp)
list(APPEND EXTRA_INCLUDES wiringpp)
target_include_directories(blink2 
                           PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${EXTRA_INCLUDES}"
                           )

target_link_libraries(C4wd PUBLIC ${EXTRA_LIBS})

target_include_directories(C4wd 
                           PUBLIC 
                           "${PROJECT_BINARY_DIR}"
#                           "${EXTRA_INCLUDES}"
                           )

install(TARGETS C4wd DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/app_config.h"
    DESTINATION include)

enable_testing()
add_test(NAME Runs COMMAND C4wd 25)

add_test(NAME Usage COMMAND C4wd)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* number")

function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

do_test(C4wd 4 "=4, squart=2")
do_test(C4wd 9 "=9, squart=3")
do_test(C4wd 5 "=5, squart=2.236")

