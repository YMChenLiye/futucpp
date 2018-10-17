file(GLOB_RECURSE SRCS *.cpp)

get_filename_component(SERVER ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TargetName "Client")

add_executable(${TargetName} ${SRCS})

target_link_libraries(${TargetName} ${LibAutoGen})