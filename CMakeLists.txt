cmake_minimum_required(VERSION 3.8)

# set the project name and version
project(crayon_rt)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# library -- stb
add_library(stb_lib INTERFACE)
target_include_directories(stb_lib INTERFACE include/stb)

# library -- core
set(CORE_SRC
    src/core/image.cpp
)
add_library(core_lib SHARED ${CORE_SRC})
target_include_directories(core_lib PUBLIC include)
target_link_libraries(core_lib PRIVATE stb_lib)

# executable
add_executable(crayon_rt 
    src/main/main.cpp
)

target_link_libraries(crayon_rt
    stb_lib
    core_lib
)
