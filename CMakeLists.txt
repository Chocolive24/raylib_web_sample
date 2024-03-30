cmake_minimum_required(VERSION 3.22)
project(raylib_sample)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_WEB "build for web platform" OFF)

if (BUILD_WEB)
    add_compile_definitions(PLATFORM_WEB)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

find_package(raylib REQUIRED)

set(data_dir "${CMAKE_SOURCE_DIR}/data")

set(data_files)
file(GLOB_RECURSE DATA_FILES
            "data/*.json"
            "data/*.png"
            "data/*.jpg"
            "data/*.wav"
            )
list(APPEND data_files ${DATA_FILES})

add_executable(main main.cpp)
target_link_libraries(main PRIVATE raylib)

if (BUILD_WEB)
        # The local resources path needs to be mapped to /data virtual path
        string(APPEND data_dir "@data")
        set_target_properties(main PROPERTIES LINK_FLAGS "--preload-file ${data_dir}")
endif ()

# Copy all of the resource files to the destination
file(COPY ${data_files} DESTINATION "data/")