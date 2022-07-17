# thank you to cristeigabriel for helping me with this!
cmake_minimum_required(VERSION 3.21)
project(hotwheels_csgo_external)

set(CMAKE_CXX_STANDARD 23)

# we probably dont need this many, only 1 should be fine. this looks funni
file(GLOB_RECURSE SRC
        "project/*.h" ,
        "project/*.hpp" ,
        "project/*.c" ,
        "project/*.cpp" ,
        "project/*.inl" ,
        "project/**/*.h" ,
        "project/**/*.hpp" ,
        "project/**/*.c" ,
        "project/**/*.cc" ,
        "project/**/*.cpp" ,
        "project/**/*.inl" ,
        )


add_library(${PROJECT_NAME} SHARED ${SRC})

find_library(D3D11_LIB d3d11.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/directx")
find_library(DXGI_LIB dxgi.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/directx")
find_library(FREETYPE_LIB freetype.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/freetype")
find_library(THEMIDA_LIB SecureEngineSDK64.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/themida/lib")
find_library(LIBLZMA_LIB liblzma.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/liblzma")

target_link_libraries(${PROJECT_NAME} "${D3D11_LIB}" "${DXGI_LIB}")
target_link_libraries(${PROJECT_NAME} "${FREETYPE_LIB}")
target_link_libraries(${PROJECT_NAME} "${THEMIDA_LIB}")
target_link_libraries(${PROJECT_NAME} "${LIBLZMA_LIB}")

target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/freetype")

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/freetype/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/bsp")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/liblzma/include")