# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (FutuClient C CXX)

set(CMAKE_CXX_STANDARD 11)

# 设置二进制和库文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include("${CMAKE_SOURCE_DIR}/FunctionDefs.cmake")
# 根据PB生成对应的C++文件, 并编译成AutoGen库
SetAutoGenVars()
AddAutoGenProto(${CMAKE_SOURCE_DIR}/proto ProtoGen)
add_library(${LibAutoGen} STATIC ${ProtoGen})
include_directories(SYSTEM "${AutoGenOutputDir}")
find_library(LIB_PROTOBUF "libprotobuf.a" "${PROTOBUF_ROOT}/lib" NO_DEFAULT_PATH)

add_compile_options(-Wno-deprecated)

set(TARS_ROOT 3rd/tars/util)
include_directories(SYSTEM ${TARS_ROOT}/include)
add_subdirectory(${TARS_ROOT})
set(LIB_TARSUTIL tarsutil)

set(LIBS ${LibAutoGen} ${LIB_PROTOBUF} -pthread ${LIB_TARSUTIL})

add_subdirectory(src EXCLUDE_FROM_ALL)
