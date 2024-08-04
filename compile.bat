@echo off
mkdir o >nul 2>&1
clang -Wall -Wextra -Wpedantic -Werror src/*.c -o ./o/main.exe -lraylib -lgdi32 -lwinmm