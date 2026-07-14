cmake_minimum_required(VERSION 3.15)
project(HammingCodec C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_library(common_types INTERFACE)
target_include_directories(common_types INTERFACE
  common/include
)


add_library(file_io STATIC
  common/src/FileIo.c
)
target_include_directories(file_io PUBLIC
  common/include
)
target_link_libraries(file_io PUBLIC
  common_types
)


add_executable(matrix_generator tools/src/MatrixGenerator.c)
target_include_directories(matrix_generator PRIVATE
  tools/include
)
target_link_libraries(matrix_generator PRIVATE
  file_io
)


add_executable(coder_module core/src/CoderModule.c)
target_include_directories(coder_module PRIVATE
  core/include
)
target_link_libraries(coder_module PRIVATE
  file_io
)
