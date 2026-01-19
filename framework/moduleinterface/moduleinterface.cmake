
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)


list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/mxcompositor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/appabstraction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxcontrol.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxcontrolpanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mxmodule.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/mxcompositor.h
    ${CMAKE_CURRENT_LIST_DIR}/appabstraction.h
    ${CMAKE_CURRENT_LIST_DIR}/mxcontrol.h
    ${CMAKE_CURRENT_LIST_DIR}/mxcontrolpanel.h
    ${CMAKE_CURRENT_LIST_DIR}/mxmodule.h
)
