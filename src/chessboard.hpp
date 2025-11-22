#include "figures.hpp"
#include <iostream>

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

struct Field {
  char col_of_field;
  char col_of_figure = 'e';
  BaseFigure* f = nullptr;
};

struct Board {
  Field board[8][8];
  bool white_threat[8][8];
  bool black_threat[8][8];
  char current_move;

  std::vector<Point> dostig(BaseFigure* f, Point p) {
    char this_name = board[p.x][p.y].f->name;
    std::vector<Point> answer;

    if (this_name == 'N'){
      for(auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)){
        if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure){
          answer.push_back(x);
        }
      }
    }

    if(this_name == 'R'){
      for(auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)){
        if (p.x == x.x){
          if (p.y > x.y){
            for (int i = p.y; i >= x.y; --i){
              if (board[p.x][i].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[p.x][i].col_of_figure != board[p.x][p.y].col_of_figure && board[p.x][i + 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }

          if (p.y < x.y){
            for (int i = p.y; i <= x.y; ++i){
              if (board[p.x][i].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[p.x][i].col_of_figure != board[p.x][p.y].col_of_figure && board[p.x][i - 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }

        if (p.y == x.y){
          if (p.x > x.x){
            for (int i = p.x; i >= x.x; --i){
              if (board[i][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][p.y].col_of_figure != board[p.x][p.y].col_of_figure && board[i + 1][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
          if (p.x < x.x){
            for (int i = p.x; i <= x.x; ++i){
              if (board[i][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][p.y].col_of_figure != board[p.x][p.y].col_of_figure && board[i - 1][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }
      }
    }

    if (this_name == 'B') {
      for(auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)){
        if ((p.x - x.x) == (p.y - x.y)){
          if (p.y > x.y){
            for (int i = p.x, j = p.y; i >= x.x; --i, --j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i + 1][j + 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }

          if (p.y < x.y){
            for (int i = p.x, j = p.y; i <= x.x; ++i, ++j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i - 1][j - 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }

        if ((p.x - x.x) == -(p.y - x.y)){
          if (p.x > x.x){
            for (int i = p.x, j = p.y; i >= x.x; --i, ++j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i + 1][j - 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
          if (p.x < x.x){
            for (int i = p.x, j = p.y; i <= x.x; ++i, --j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i - 1][j + 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }
      }
    }

    if (this_name == 'Q') {
      for(auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)){
        if ((p.x - x.x) == (p.y - x.y)){
          if (p.y > x.y){
            for (int i = p.x, j = p.y; i >= x.x; --i, --j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i + 1][j + 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }

          if (p.y < x.y){
            for (int i = p.x, j = p.y; i <= x.x; ++i, ++j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i - 1][j - 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }

        if ((p.x - x.x) == -(p.y - x.y)){
          if (p.x > x.x){
            for (int i = p.x, j = p.y; i >= x.x; --i, ++j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i + 1][j - 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
          if (p.x < x.x){
            for (int i = p.x, j = p.y; i <= x.x; ++i, --j){
              if (board[i][j].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][j].col_of_figure != board[p.x][p.y].col_of_figure && board[i - 1][j + 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }
      }
      for(auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)){
        if (p.x == x.x){
          if (p.y > x.y){
            for (int i = p.y; i >= x.y; --i){
              if (board[p.x][i].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[p.x][i].col_of_figure != board[p.x][p.y].col_of_figure && board[p.x][i + 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }

          if (p.y < x.y){
            for (int i = p.y; i <= x.y; ++i){
              if (board[p.x][i].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[p.x][i].col_of_figure != board[p.x][p.y].col_of_figure && board[p.x][i - 1].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }

        if (p.y == x.y){
          if (p.x > x.x){
            for (int i = p.x; i >= x.x; --i){
              if (board[i][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][p.y].col_of_figure != board[p.x][p.y].col_of_figure && board[i + 1][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
          if (p.x < x.x){
            for (int i = p.x; i <= x.x; ++i){
              if (board[i][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              } else if (board[i][p.y].col_of_figure != board[p.x][p.y].col_of_figure && board[i - 1][p.y].col_of_figure == 'e'){
                answer.push_back(x);
              }
            }
          }
        }
      }
    }

    if (this_name == 'P') {
      if (board[p.x][p.y].col_of_figure == 'w') {
        if (board[p.x][p.y + 1].col_of_figure == 'e') {
          answer.push_back(Point(p.x, p.y + 1));
        }
        if (p.y == 1) {
          if (board[p.x][p.y + 1].col_of_figure == 'e' and board[p.x][p.y + 2].col_of_figure == 'e') {
            answer.push_back(Point(p.x, p.y + 2));
          }
        }
      }
      if (board[p.x][p.y].col_of_figure == 'b') {
        if (board[p.x][p.y - 1].col_of_figure == 'e') {
          answer.push_back(Point(p.x, p.y + 1));
        }
        if (p.y == 6) {
          if (board[p.x][p.y + 1].col_of_figure == 'e' and board[p.x][p.y + 2].col_of_figure == 'e') {
            answer.push_back(Point(p.x, p.y - 2));
          }
        }
      }
      for (auto x : board[p.x][p.y].f->threat(p)) {
        if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure && board[x.x][x.y].col_of_figure != 'e') {
          answer.push_back(x);
        }
      }
    }

    if (this_name == 'K') {
      for (auto x : board[p.x][p.y].f->threat(p)) {
        if (board[p.x][p.y].col_of_figure == 'w') {
          if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure and black_threat[x.x][x.y] == false) {
            answer.push_back(x);
          }
        }
        if (board[p.x][p.y].col_of_figure == 'w') {
          if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure and white_threat[x.x][x.y] == false) {
            answer.push_back(x);
          }
        }
      }
    }
    for (auto x : answer) {
      if (x == p) {
        std::swap(x, answer[answer.size() - 1]);
        answer.pop_back();
      }
    }
    return answer;
  }
  
  void StartPosition() {
    Clear();
    current_move = 'w';
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (j == 1 or j == 6) {
          board[i][j].f = new Pawn;
          board[i][j].f->name = 'P';
        }
        if (j == 0 or j == 7) {
          if (i == 0 or i == 7) {
            board[i][j].f = new Rook;
            board[i][j].f->name = 'R';
          }
          if (i == 1 or i == 6) {
            board[i][j].f = new Knight;
            board[i][j].f->name = 'N';
          }
          if (i == 2 or i == 5) {
            board[i][j].f = new Bishop;
            board[i][j].f->name = 'B';
          }
          if (i == 3) {
            board[i][j].f = new Queen;
            board[i][j].f->name = 'Q';
          }
          if (i == 4) {
            board[i][j].f = new King;
            board[i][j].f->name = 'K';
          }
        }
        if (j <= 1) {
          board[i][j].col_of_figure = 'w';
        }
        if (j >= 6) {
          board[i][j].col_of_figure = 'b';
        }
        if (i % 2 == j % 2) {
          board[i][j].col_of_field = 'b';
        } else {
          board[i][j].col_of_field = 'w';
        }
      }
    }

    Print();
  }

  void Clear() {
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (board[i][j].f != nullptr) {
          delete board[i][j].f;
          board[i][j].f = nullptr;
          board[i][j].col_of_field = 'e';
        }
      }
    }
  }

  void Print() {
    char picture[26][26];
    bool color[26][26];
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (i == 0 or i == 25) {
          picture[i][j] = '*';
        }
        if (j == 0 or j == 25) {
          picture[i][j] = '*';
        }
        if ((i == 0 or i == 25) and (j == 0 or j == 25)) {
          picture[i][j] = '*';
        }
      }
    }
    for (int i = 1; i < 25; ++i) {
      for (int j = 1; j < 25; ++j) {
        int x = i - 1, y = j - 1;
        if (board[x / 3][y / 3].col_of_field == 'w') {
          picture[i][j] = '#';
        } else {
          picture[i][j] = ' ';
        }
      }
    }
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (board[i][j].f != nullptr) {
          picture[i * 3 + 2][j * 3 + 2] = board[i][j].f->name;
          color[i * 3 + 2][j * 3 + 2] = board[i][j].col_of_figure == 'w';
        }
      }
    }
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        char ch = picture[j][25 - i];
        /*
        if (ch == 'N' or ch == 'B' or ch == 'R' or ch == 'Q' or ch == 'K' or ch == 'P') {
          if (color[j][25 - i]) std::cout << "\x1b[33m" << ch  << "\x1b[0m" << "  ";
          else std::cout << "\x1b[34m" << ch  << "\x1b[0m" << "  ";
        } else if (ch != ' ' and ch != '#') {
          std::cout << "\x1b[31m" << ch  << "\x1b[0m" << "  ";
        } else {
          std::cout << ch << "  ";
        }
        */
        std::cout << ch << "  ";
      }
      std::cout << "\n";
    }
  }

  bool Is_possible(char name, Point first, Point second) {
    if (board[first.x][first.y].f->name != name) {
      return false;
    }
    bool flag = false;
    for (auto x : (board[first.x][first.y].f->ach(first, current_move))){
      if (first == x) {
        flag = true;
        break;
      }
    }
    if (flag == false) {
      return false;
    }
    
    return true;
  }
};
