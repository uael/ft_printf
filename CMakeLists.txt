cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(ftprintf C)

set(BUILD_SHARED_LIBS OFF)
set(ftprintf_ENABLE_TEST ON)

set(ftprintf_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(ftprintf_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(ftprintf_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

option(COVERAGE "Turn on COVERAGE support" OFF)
if (COVERAGE AND NOT MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif ()

set(ftprintf_HDR ${ftprintf_INC_DIR}/libft.h)
file(GLOB_RECURSE ftprintf_HDRS ${ftprintf_HDRS}
  ${ftprintf_INC_DIR}/libft/*.h)
file(GLOB_RECURSE ftprintf_SRCS ${ftprintf_SRCS}
  ${ftprintf_SRC_DIR}/*.c)
file(GLOB_RECURSE ftprintf_SRCS ${ftprintf_SRCS}
  ${ftprintf_SRC_DIR}/*.h)

add_library(ftprintf ${ftprintf_HDR} ${ftprintf_HDRS} ${ftprintf_SRCS})
set_property(TARGET ftprintf PROPERTY C_STANDARD 90)
target_include_directories(ftprintf PUBLIC ${ftprintf_INC_DIR})
target_compile_definitions(ftprintf PRIVATE U_COMPILE)

target_compile_definitions(ftprintf
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
  PRIVATE API_COMPILE)
if (MSVC)
  target_compile_options(ftprintf
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(ftprintf
    PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
    PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

if (ftprintf_ENABLE_TEST)
  enable_testing()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
  file(GLOB ftprintf_TEST_SRCS ${ftprintf_TEST_SRCS}
    ${ftprintf_TEST_DIR}/*.c)
  foreach (ftprintf_TEST_SRC ${ftprintf_TEST_SRCS})
    get_filename_component(ftprintf_TEST_NAME ${ftprintf_TEST_SRC} NAME_WE)
    set(test test_ftprintf_${ftprintf_TEST_NAME})
    add_executable(${test} ${ftprintf_TEST_SRC})
    set_property(TARGET ${test}
      PROPERTY C_STANDARD 90)
    add_dependencies(${test} ftprintf)
    add_dependencies(check ${test})
    target_include_directories(${test} PUBLIC
      ${ftprintf_TEST_DIR})
    target_link_libraries(${test} ftprintf)
    target_compile_definitions(${test}
      PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
    add_test(ftprintf_${ftprintf_TEST_NAME} ${test}
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
