cmake_minimum_required(VERSION 3.31)

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
