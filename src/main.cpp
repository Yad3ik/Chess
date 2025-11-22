#include <iostream>
#include "chessboard.hpp"
// #include <windows.h>

/*
void enable_ansi_colors() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE) return;

  DWORD mode = 0;
  if (!GetConsoleMode(hOut, &mode)) return;

  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, mode);
}
*/

int main() {
  // enable_ansi_colors();
  
  Board b;
  b.StartPosition();

  return 0;
}
