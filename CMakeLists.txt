# CMakeList.txt : CMake project for JoNES, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("JoNES")

# Add source to this project's executable.
add_executable (JoNES "JoNES.cpp" "JoNES.h" "JoNES_6502_Core.cpp" "JoNES_PPU.cpp")

# TODO: Add tests and install targets if needed.
