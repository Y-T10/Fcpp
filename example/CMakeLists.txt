## findFont.cpp
add_executable(findFont)
target_sources(findFont PRIVATE findFont.cpp)
target_include_directories(findFont PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(findFont PRIVATE Fcpp::Fcpp)