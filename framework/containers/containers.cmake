

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/mxbuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxbytearrayref.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxgenericstring.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxrefcounter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxstring.cpp
)
