#include <iostream>
#include "chessboard.hpp"
// #include <windows.h>
/*
N - конь
B - слон
K - король
Q - ферзь
P - пешка
R - ладья

1. Класс фигур(базовые фигуры) - наследникки все фигуры
 В классе фигур храниться :
 1. функция опрделения биитых
 2. функция достижимых(куда можжно пойти)
 3. char Name
2. Класс каждой фигуры
 1. функция переопределния битых полей
 2. Для пешки отдельная функкция достижимых
3. Поле (как одна клетка) (field)
 1.цвет поля
 2.цвет фигуры
 3.указатель на базовую фигуру
4. Класс доска (board)
 1.Массив массив(field board[8][8])
 2.проверка хода(
   1.Та ли фигура(цвет и введеное знач)
   2.Входит ли втроавя координата в функццию достижимых
   3.Есть ли на пути хода преграды? (для каждой сво проврека))
 3. Две будевых доски ждя белых и черных битые поля
 4. Функция хода(
   0. Уникальность хода
   1. вызов is_possible(Фигура, координаты 1, координаты 2)
   2.переставнока на field
   3. Обновление битых полей БЧ)
*/

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
