#include <algorithm>
#include "chessboard.hpp"
#include <iostream>
#include <windows.h>

void enable_ansi_colors() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE) return;

  DWORD mode = 0;
  if (!GetConsoleMode(hOut, &mode)) return;

  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, mode);
}

int main() {
  enable_ansi_colors();

  Board b;
  b.StartPosition();
  std::string move;
  while (true) {
    std::getline(std::cin, move);
    if (b.Make_move(move)) {

      b.Print();
      if (b.current_move == 'b') {
        b.current_move = 'w';
      } else {
        b.current_move = 'b';
      }
      std::cout << b.current_move << "\n";
    } else {
      std::cout << "Invalid move" << std::endl;
    }
  }
  return 0;
}
