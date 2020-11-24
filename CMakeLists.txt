cmake_minimum_required(VERSION 3.5)

project(HLOH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(LibFruit)

add_library(HLOH SHARED
    Mod.cpp
    )

target_include_directories(HLOH PUBLIC SYSTEM
    .
    LibFruit
    metamod-source/core
    metamod-source/core/sourcehook
    hl2sdk/public
    hl2sdk/public/game/server
    hl2sdk/game/server
    hl2sdk/public/tier0
    hl2sdk/public/tier1
    )

target_link_directories(HLOH PUBLIC hl2sdk/lib/public)
target_link_libraries(HLOH PUBLIC tier0 tier1 legacy_stdio_definitions LibFruit)
target_compile_definitions(HLOH PUBLIC SOURCE_ENGINE=1)
