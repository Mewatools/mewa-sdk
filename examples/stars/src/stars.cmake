
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)

add_compile_definitions(MX_PLUGIN_HEADER="starsmodule.h")
add_compile_definitions(MX_PLUGIN_CLASS=StarsModule)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/starsmodule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/starsprogram.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/starsmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/starsprogram.h

)
