cmake_minimum_required(VERSION 3.5.0)
project(hcex)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HCEX_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/hcex/source/")
file(GLOB_RECURSE HCEX_C_SOURCE_FILES "hcex/source/*.c")
file(GLOB_RECURSE HCEX_CXX_SOURCE_FILES "hcex/source/*.cpp")

add_library(hcex ${HCEX_C_SOURCE_FILES} ${HCEX_CXX_SOURCE_FILES})

set_property(TARGET hcex PROPERTY C_STANDARD 23)
set_property(TARGET hcex PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET hcex PROPERTY C_EXTENSIONS OFF)

set_property(TARGET hcex PROPERTY CXX_STANDARD 23)
set_property(TARGET hcex PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET hcex PROPERTY CXX_EXTENSIONS OFF)

set(HCEX_WARNINGS -Wall -Wextra -Wpedantic -pedantic-errors -Wno-keyword-macro -Wno-missing-braces -Wno-gnu-zero-variadic-macro-arguments)

set(HCEX_DEFINITIONS $<$<CONFIG:DEBUG>:-DDEBUG>)

target_compile_options(hcex PRIVATE ${HCEX_WARNINGS} ${HCEX_DEFINITIONS})
target_include_directories(hcex PRIVATE ${HCEX_INCLUDE_DIRS})
