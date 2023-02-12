# CMake 笔记

```cmake
cmake_minimum_required(VERSION 3.20)
project(CPP_Practice)

set(CMAKE_CXX_STANDARD 14)
include_directories(third_party/ffmpeg)
link_directories(third_lib/win_x64)
file(GLOB_RECURSE SOURCES "Src/*.*")
add_executable(${PROJECT_NAME} ${SOURCES})
```

