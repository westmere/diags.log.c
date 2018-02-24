cmake_minimum_required(VERSION 2.8)

option(USE_STATIC_DIAGS_LOG_LIBRARY "Build json_jsmn static library." OFF)
option(USE_OBJECT_DIAGS_LOG_LIBRARY "Build json_jsmn object library." ON)

if(USE_OBJECT_DIAGS_LOG_LIBRARY)
    add_library(diags-log-object OBJECT log.c)
endif(USE_OBJECT_DIAGS_LOG_LIBRARY)

if(USE_STATIC_DIAGS_LOG_LIBRARY)
    add_library(diags-log-static STATIC log.c)

    target_include_directories(diags-log-static PUBLIC ${CMAKE_CURRENT_LIST_DIR})
endif(USE_STATIC_DIAGS_LOG_LIBRARY)
