
include(${CMAKE_CURRENT_LIST_DIR}/extensions/mxopenglfunctions.cmake)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/mxgpuarray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxgpuprogram.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxrenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxtexture.cpp
)
