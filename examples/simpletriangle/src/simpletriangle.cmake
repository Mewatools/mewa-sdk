include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)

add_compile_definitions(MX_MODULE_HEADER="simpletriangle.h")
add_compile_definitions(MX_MODULE_CLASS=SimpleTriangle)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/simpletriangle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/triangleprogram.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/simpletriangle.h
    ${CMAKE_CURRENT_LIST_DIR}/triangleprogram.h

)
