cmake_minimum_required(VERSION 2.8)
project(leakprof)


SET (CMAKE_C_COMPILER "gcc")
SET (CMAKE_C_FLAGS "-Wall -ggdb3 -std=gnu99 -O3 -march=corei7")

include_directories("./include/")

SET (BT_SOURCES
    src/backtrace.c
    src/timespec_diff_ns.c
    src/x86_64-bt.c
    src/linuxRtGetProc.c
)

ADD_LIBRARY(bt SHARED ${BT_SOURCES})
TARGET_LINK_LIBRARIES(bt rt pthread unwind-x86_64 unwind)
