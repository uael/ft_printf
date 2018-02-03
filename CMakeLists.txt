cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(ft_printf C)

set(BUILD_SHARED_LIBS OFF)
set(ft_printf_ENABLE_TEST ON)

set(ft_printf_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(ft_printf_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(ft_printf_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

option(COVERAGE "Turn on COVERAGE support" OFF)
if (COVERAGE AND NOT MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif ()

set(ft_printf_HDR ${ft_printf_INC_DIR}/ft_printf.h)
file(GLOB_RECURSE ft_printf_HDRS ${ft_printf_HDRS}
  ${ft_printf_INC_DIR}/ft_printf/*.h)
file(GLOB_RECURSE ft_printf_SRCS ${ft_printf_SRCS}
  ${ft_printf_SRC_DIR}/*.c)
file(GLOB_RECURSE ft_printf_SRCS ${ft_printf_SRCS}
  ${ft_printf_SRC_DIR}/*.h)

add_library(ft_printf ${ft_printf_HDR} ${ft_printf_HDRS} ${ft_printf_SRCS})
set_property(TARGET ft_printf PROPERTY C_STANDARD 90)
target_include_directories(ft_printf PUBLIC ${ft_printf_INC_DIR})
target_compile_definitions(ft_printf PRIVATE U_COMPILE)

target_compile_definitions(ft_printf
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
  PRIVATE API_COMPILE)
if (MSVC)
  target_compile_options(ft_printf
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(ft_printf
    PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
    PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

if (ft_printf_ENABLE_TEST)
  enable_testing()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
  file(GLOB ft_printf_TEST_SRCS ${ft_printf_TEST_SRCS}
    ${ft_printf_TEST_DIR}/*.c)
  foreach (ft_printf_TEST_SRC ${ft_printf_TEST_SRCS})
    get_filename_component(ft_printf_TEST_NAME ${ft_printf_TEST_SRC} NAME_WE)
    set(test test_ft_printf_${ft_printf_TEST_NAME})
    add_executable(${test} test/test.h ${ft_printf_TEST_SRC} test/lib/cli.c)
    set_property(TARGET ${test}
      PROPERTY C_STANDARD 90)
    add_dependencies(${test} ft_printf)
    add_dependencies(check ${test})
    target_include_directories(${test} PUBLIC
      ${ft_printf_TEST_DIR})
    target_link_libraries(${test} ft_printf)
    target_compile_definitions(${test}
      PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
    add_test(ft_printf_${ft_printf_TEST_NAME} ${test}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
    if (MSVC)
      target_compile_options(${test}
        PRIVATE /MTd /Oy /W3
        PRIVATE /D_CRT_SECURE_NO_WARNINGS
        PRIVATE /Od)
    else ()
      target_compile_options(${test}
        PRIVATE -fomit-frame-pointer -ansi
        PRIVATE -O0 -g3)
    endif ()
  endforeach ()
endif ()
