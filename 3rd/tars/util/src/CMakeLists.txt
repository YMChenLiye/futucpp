#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

aux_source_directory(. DIR_SRCS)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND DIR_SRCS "tc_jump_x86_64_sysv_elf_gas.s")
    list(APPEND DIR_SRCS "tc_make_x86_64_sysv_elf_gas.s")
else ()
    list(APPEND DIR_SRCS "tc_jump_i386_sysv_elf_gas.s")
    list(APPEND DIR_SRCS "tc_make_i386_sysv_elf_gas.s")
endif ()

add_library(tarsutil ${DIR_SRCS})

install(TARGETS tarsutil
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
