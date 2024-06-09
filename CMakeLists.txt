cmake_minimum_required(VERSION 3.25)
cmake_policy(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

option(CMAKE_BUILD_TYPE "Build type. (Debug, Release)" Release)
option(BUILD_SHARED_LIBS "Create shared libraries." OFF)

# "compile_commands.json"を生成するかを設定する
find_program(CLANGD "clangd")
if (NOT (DEFINED CLANGD-NOTFOUND))
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
elseif ((NOT (DEFINED $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})) AND (DEFINED CMAKE_EXPORT_COMPILE_COMMANDS))
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
endif()

project(Fcpp
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "Fontconfig c++ wrapper."
)

## 親プロジェクトを持つかを調べる
if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(FCPP_SUBPROJECT OFF)
else()
    set(FCPP_SUBPROJECT ON)
endif()

include(CMakeDependentOption)
cmake_dependent_option(FCPP_EXAMPLE "Build example programs." ON "NOT FCPP_SUBPROJECT" OFF)

find_package(Fontconfig 2.14.0 REQUIRED)
find_package(Boost 1.74.0 REQUIRED)

add_library(${PROJECT_NAME})
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS ON)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Fcpp.cpp
)

# ヘッダファイルのディレクトリを追加
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# プログラムが利用するターゲットを追加
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    Fontconfig::Fontconfig
    Boost::boost
)

## サンプルコードのコンパイル
if (${FCPP_EXAMPLE})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif()
