function(PrintVar Var)
    message(STATUS "${Var}: ${${Var}}")
endfunction()

function(SetAutoGenVars)
    set(AutoGenOutputDir "${CMAKE_BINARY_DIR}/AutoGen"
        CACHE STRING "Auto Generated File Output Dir")

    set(LibAutoGen "AutoGen"
        CACHE STRING "Auto Generated Library Name")

    set(PROTOBUF_ROOT "${CMAKE_SOURCE_DIR}/3rd/protobuf"
        CACHE STRING "protobuf root")
    include_directories(SYSTEM "${PROTOBUF_ROOT}/include")
    find_program(Protoc "protoc" NO_DEFAULT_PATH
        PATHS "${PROTOBUF_ROOT}/bin")

    file(MAKE_DIRECTORY ${AutoGenOutputDir})
endfunction()

function(CheckAutoGenFile FilePath)
    if (EXISTS ${FilePath})
        message(FATAL_ERROR
        "Auto generated file ${FilePath} Exists, Delete it and try again!!!")
    endif()
endfunction()

function(AddAutoGenProto Dir SrcVar)
    set(Srcs "${${SrcVar}}")
    file(GLOB ProtoFiles "${Dir}/*.proto")
    foreach(ProtoFile ${ProtoFiles})
      get_filename_component(ProtoName ${ProtoFile} NAME_WE)
      CheckAutoGenFile(${Dir}/${ProtoName}.pb.h)
      CheckAutoGenFile(${Dir}/${ProtoName}.pb.cc)
      CheckAutoGenFile(${Dir}/${ProtoName}.pb.cpp)
      set (CurrentProtoGen ${AutoGenOutputDir}/${ProtoName}.pb.h
                           ${AutoGenOutputDir}/${ProtoName}.pb.cc)
      list(APPEND Srcs ${CurrentProtoGen})
      set (PROTO_GEN ${PROTO_GEN} ${CURRENT_PROTO_GEN})
      add_custom_command(OUTPUT ${CurrentProtoGen}
          COMMAND ${Protoc} ${ProtoFile} --cpp_out=${AutoGenOutputDir} -I${Dir}
        DEPENDS ${Protoc} ${ProtoFile}
        WORKING_DIRECTORY ${Dir})
    set(${SrcVar} ${Srcs} PARENT_SCOPE)
    endforeach()
endfunction()
