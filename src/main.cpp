#include "chessboard.hpp"
#include <iostream>
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
  std::string move;

  while (true) {
    std::cout << (b.current_move == 'w' ? "white" : "black")
              << " enter your move: ";
    std::getline(std::cin, move);
    int result = b.Make_move(move);
    if (result == 1) {
      b.Print();
      if (b.current_move == 'b') {
        b.current_move = 'w';
      } else {
        b.current_move = 'b';
      }
      std::cout << b.current_move << "\n";
    } else if (result == -1) {
      b.Print();
    } else {
      std::cout << "Invalid move" << "\n";
    }
  }
  return 0;
}
