#include <iostream>
#include <vector>
#include <windows.h>
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
struct Point {
  int x;
  int y;
  Point(int i, int j) : x(i), y(j){}

  bool operator==(const Point& p) {
    return x == p.x and y == p.y;
  }

  bool operator!=(const Point& p) {
    return !(*this == p);
  }
};

struct BaseFigure {
  char name;
  virtual std::vector<Point> threat(const Point& p) {};
  virtual std::vector<Point> ach(const Point& p, char col) {
    return threat(p);
  }
};

struct Knight : BaseFigure {
  std::vector<Point> threat(const Point& p) {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == 1 and std::abs(p.y - j) == 2 or std::abs(p.x - i) == 2 and std::abs(p.y - j) == 1) {
          answer.push_back(Point(i , j));
        }
      }
    }
    return answer;
  }
};

struct Bishop : BaseFigure {
  std::vector<Point> threat(const Point& p) {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == std::abs(p.y - j) and i != p.x) {
          answer.push_back(Point(i , j));
        }
      }
    }
    return answer;
  }
};

struct King : BaseFigure {
  std::vector<Point> threat(const Point& p) {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) <= 1 and std::abs(p.y - j) <= 1 and Point(i, j) != p) {
          answer.push_back(Point(i , j));
        }
      }
    }
    return answer;
  }
};

struct Rook : BaseFigure {
  std::vector<Point> threat(const Point& p) {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (p.x == i and p.y != j or p.x != i and p.y == j) {
          answer.push_back(Point(i , j));
        }
      }
    }
    return answer;
  }
};

struct Pawn : BaseFigure {
  std::vector<Point> threat(const Point& p) {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == 1 and p.y == j + 1) {
          answer.push_back(Point(i , j));
        }
      }
    }
    return answer;
  }

  std::vector<Point> ach(const Point& p, char col) {
    std::vector<Point> answer;
    if (col == 'w') {
      answer.push_back(Point(p.x, p.y + 1));
      if (p.y == 1) {
        answer.push_back(Point(p.x, p.y + 2));
      }
    }
    if (col == 'b') {
      answer.push_back(Point(p.x, p.y - 1));
      if (p.y == 6) {
        answer.push_back(Point(p.x, p.y - 2));
      }
    }
    return answer;
  }
};

struct Queen : BaseFigure {
  std::vector<Point> threat(const Point& p) {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == std::abs(p.y - j) and i != p.x) {
          answer.push_back(Point(i , j));
        }
        if (p.x == i and p.y != j or p.x != i and p.y == j) {
          answer.push_back(Point(i , j));
        }
      }
    }
    return answer;
  }
};

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
  std::vector<Point> dostig(Board current_positiion, Base) {

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
        if (ch == 'N' or ch == 'B' or ch == 'R' or ch == 'Q' or ch == 'K' or ch == 'P') {
          if (color[j][25 - i]) std::cout << "\x1b[33m" << ch  << "\x1b[0m" << "  ";
          else std::cout << "\x1b[34m" << ch  << "\x1b[0m" << "  ";
        } else if (ch != ' ' and ch != '#') {
          std::cout << "\x1b[31m" << ch  << "\x1b[0m" << "  ";
        } else {
          std::cout << ch << "  ";
        }

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
        flag == true;
      }
    }
    if (flag == false) {
      return false;
    }

  }
};

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

  return 0;
}
