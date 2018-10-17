# CMake ��Ͱ汾��Ҫ��
cmake_minimum_required (VERSION 2.8)

# ��Ŀ��Ϣ
project (FutuClient C CXX)

# ���ö����ƺͿ��ļ����·��
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include("${CMAKE_SOURCE_DIR}/FunctionDefs.cmake")
# ����PB���ɶ�Ӧ��C++�ļ�, �������AutoGen��
SetAutoGenVars()
AddAutoGenProto(${CMAKE_SOURCE_DIR}/proto ProtoGen)
add_library(${LibAutoGen} STATIC ${ProtoGen})
include_directories(SYSTEM "${AutoGenOutputDir}")

add_subdirectory(src EXCLUDE_FROM_ALL)