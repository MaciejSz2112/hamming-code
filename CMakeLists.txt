cmake_minimum_required(VERSION 3.15)
project(HammingCodec C)

#
# GLOBAL SETTINGS
#
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
elseif(MSVC)
  add_compile_options(/W4 /WX)
endif()

#
# COMMON MODULES
#
add_library(common_types INTERFACE)
target_include_directories(common_types INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/common/include
)

add_library(file_io STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/common/src/FileIo.c
  ${CMAKE_CURRENT_SOURCE_DIR}/common/include/FileIo.h
)
target_include_directories(file_io PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/common/include
)
target_link_libraries(file_io PUBLIC
  common_types
)


#
# TOOLS MODULE
#
add_executable(matrix_generator
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/src/MatrixGenerator.c
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/include/MatrixGeneratorLib.h
)
target_include_directories(matrix_generator PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/include
)
target_link_libraries(matrix_generator PRIVATE
  file_io
)


#
# CORE MODULE
#
add_executable(coder_module
  ${CMAKE_CURRENT_SOURCE_DIR}/core/src/CoderModule.c
  ${CMAKE_CURRENT_SOURCE_DIR}/core/include/CoderModuleLib.h
)
target_include_directories(coder_module PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/core/include
)
target_link_libraries(coder_module PRIVATE
  file_io
)
