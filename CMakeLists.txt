cmake_minimum_required(VERSION 3.31)

project(Fcpp
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "Fontconfig c++ wrapper."
)

include(CMakeDependentOption)
cmake_dependent_option(
    FCPP_BUILD_EXAMPLE "Build example"
    ON [[CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR]] OFF
)

find_package(Fontconfig 2.14.0 REQUIRED)
find_package(Boost 1.74.0 REQUIRED)

add_library(${PROJECT_NAME})
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS ON)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Fcpp.cpp
)

# ヘッダファイルのディレクトリを追加
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# プログラムが利用するターゲットを追加
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    Fontconfig::Fontconfig
    Boost::boost
)

if(NOT (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR))
    return()
endif()

## サンプルコードのコンパイル
if(${FCPP_BUILD_EXAMPLE})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif()
