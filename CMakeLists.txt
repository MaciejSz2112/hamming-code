cmake_minimum_required(VERSION 3.15)
project(HammingCodec C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(matrix_generator tools/src/MatrixGenerator.c)
target_include_directories(matrix_generator PRIVATE
  tools/include
  common/include
)


add_executable(coder_module core/src/CoderModule.c)
target_include_directories(coder_module PRIVATE
  core/include
  common/include
)
