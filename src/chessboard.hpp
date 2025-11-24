#include "figures.hpp"
#include <iostream>
#include <string>


bool Find(std::vector<Point> f, Point p) {
  for (auto x : f) {
    if (x == p) {
      return true;
    }
  }
  return false;
}
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
  BaseFigure *f = nullptr;
};

struct Board {
  Field board[8][8];
  bool white_threat[8][8];
  bool black_threat[8][8];
  char current_move = 'w';
  // 0 - white king, 1 - black king, 2 - white left rook, 3 - white right rook,
  // 4 - black left rook, 5 - black right rook
  int move_number[6];

  std::vector<Point> dostig(BaseFigure *f, Point p) {
    char this_name = board[p.x][p.y].f->name;
    std::vector<Point> answer;

    if (this_name == 'N') {
      for (auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)) {
        if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure) {
          answer.push_back(x);
        }
      }
    }

    if (this_name == 'R') {
      for (auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)) {
        if (p.x == x.x) {
          if (p.y > x.y) {
            for (int i = p.y - 1; i >= x.y; --i) {
              if (board[p.x][i].col_of_figure == 'e') {
                answer.push_back(Point(p.x, i));
              } else if (board[p.x][i].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[p.x][i + 1].col_of_figure == 'e' or i + 1 == p.y)) {
                answer.push_back(Point(p.x, i));
                break;
              } else {
                break;
              }
            }
          }

          if (p.y < x.y) {
            for (int i = p.y + 1; i <= x.y; ++i) {
              if (board[p.x][i].col_of_figure == 'e') {
                answer.push_back(Point(p.x,i));
              } else if (board[p.x][i].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[p.x][i - 1].col_of_figure == 'e' or i - 1 == p.y)) {
                answer.push_back(Point(p.x,i));
                break;
              } else if (board[p.x][i].col_of_figure ==
                             board[p.x][p.y].col_of_figure) {
                break;
              }
            }
          }
        }

        if (p.y == x.y) {
          if (p.x > x.x) {
            for (int i = p.x - 1; i >= x.x; --i) {
              if (board[i][p.y].col_of_figure == 'e') {
                answer.push_back(Point(i, p.y));
              } else if (board[i][p.y].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i + 1][p.y].col_of_figure == 'e' or i + 1 == p.x)) {
                answer.push_back(Point(i, p.y));
                break;
              } else if (board[i][p.y].col_of_figure ==
                             board[p.x][p.y].col_of_figure) {
                break;
              }
            }
          }
          if (p.x < x.x) {
            for (int i = p.x + 1; i <= x.x; ++i) {
              if (board[i][p.y].col_of_figure == 'e') {
                answer.push_back(Point(i, p.y));
              } else if (board[i][p.y].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i - 1][p.y].col_of_figure == 'e' or i - 1 == p.x)) {
                answer.push_back(Point(i, p.y));
                break;
              } else {
                break;
              }
            }
          }
        }
      }
    }

    if (this_name == 'B') {
      for (auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)) {
        if ((p.x - x.x) == (p.y - x.y)) {
          if (p.y > x.y) {
            for (int i = p.x - 1, j = p.y - 1; i >= x.x; --i, --j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(Point(i, j));
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i + 1][j + 1].col_of_figure == 'e' or Point(i + 1, j + 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }

          if (p.y < x.y) {
            for (int i = p.x + 1, j = p.y + 1; i <= x.x; ++i, ++j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(Point(i, j));
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i - 1][j - 1].col_of_figure == 'e' or Point(i - 1, j - 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }
        }

        if ((p.x - x.x) == -(p.y - x.y)) {
          if (p.x > x.x) {
            for (int i = p.x - 1, j = p.y + 1; i >= x.x; --i, ++j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(x);
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i + 1][j - 1].col_of_figure == 'e' or Point(i + 1, j - 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }
          if (p.x < x.x) {
            for (int i = p.x + 1, j = p.y - 1; i <= x.x; ++i, --j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(x);
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i - 1][j + 1].col_of_figure == 'e' or Point(i - 1, j + 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }
        }
      }
    }

    if (this_name == 'Q') {
      for (auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)) {
        if ((p.x - x.x) == (p.y - x.y)) {
          if (p.y > x.y) {
            for (int i = p.x - 1, j = p.y - 1; i >= x.x; --i, --j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(Point(i, j));
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i + 1][j + 1].col_of_figure == 'e' or Point(i + 1, j + 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }

          if (p.y < x.y) {
            for (int i = p.x + 1, j = p.y + 1; i <= x.x; ++i, ++j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(Point(i, j));
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i - 1][j - 1].col_of_figure == 'e' or Point(i - 1, j - 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }
        }

        if ((p.x - x.x) == -(p.y - x.y)) {
          if (p.x > x.x) {
            for (int i = p.x - 1, j = p.y + 1; i >= x.x; --i, ++j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(x);
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i + 1][j - 1].col_of_figure == 'e' or Point(i + 1, j - 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }
          if (p.x < x.x) {
            for (int i = p.x + 1, j = p.y - 1; i <= x.x; ++i, --j) {
              if (board[i][j].col_of_figure == 'e') {
                answer.push_back(x);
              } else if (board[i][j].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i - 1][j + 1].col_of_figure == 'e' or Point(i - 1, j + 1) == p)) {
                answer.push_back(Point(i, j));
              } else {
                break;
              }
            }
          }
        }
      }
      for (auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)) {
        if (p.x == x.x) {
          if (p.y > x.y) {
            for (int i = p.y - 1; i >= x.y; --i) {
              if (board[p.x][i].col_of_figure == 'e') {
                answer.push_back(Point(p.x, i));
              } else if (board[p.x][i].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[p.x][i + 1].col_of_figure == 'e' or i + 1 == p.y)) {
                answer.push_back(Point(p.x, i));
                break;
              } else {
                break;
              }
            }
          }

          if (p.y < x.y) {
            for (int i = p.y + 1; i <= x.y; ++i) {
              if (board[p.x][i].col_of_figure == 'e') {
                answer.push_back(Point(p.x,i));
              } else if (board[p.x][i].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[p.x][i - 1].col_of_figure == 'e' or i - 1 == p.y)) {
                answer.push_back(Point(p.x,i));
                break;
              } else if (board[p.x][i].col_of_figure ==
                             board[p.x][p.y].col_of_figure) {
                break;
              }
            }
          }
        }

        if (p.y == x.y) {
          if (p.x > x.x) {
            for (int i = p.x - 1; i >= x.x; --i) {
              if (board[i][p.y].col_of_figure == 'e') {
                answer.push_back(Point(i, p.y));
              } else if (board[i][p.y].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i + 1][p.y].col_of_figure == 'e' or i + 1 == p.x)) {
                answer.push_back(Point(i, p.y));
                break;
              } else if (board[i][p.y].col_of_figure ==
                             board[p.x][p.y].col_of_figure) {
                break;
              }
            }
          }
          if (p.x < x.x) {
            for (int i = p.x + 1; i <= x.x; ++i) {
              if (board[i][p.y].col_of_figure == 'e') {
                answer.push_back(Point(i, p.y));
              } else if (board[i][p.y].col_of_figure !=
                             board[p.x][p.y].col_of_figure &&
                         (board[i - 1][p.y].col_of_figure == 'e' or i - 1 == p.x)) {
                answer.push_back(Point(i, p.y));
                break;
              } else {
                break;
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
          if (board[p.x][p.y + 1].col_of_figure == 'e' and
              board[p.x][p.y + 2].col_of_figure == 'e') {
            answer.push_back(Point(p.x, p.y + 2));
          }
        }
      }
      if (board[p.x][p.y].col_of_figure == 'b') {
        if (board[p.x][p.y - 1].col_of_figure == 'e') {
          answer.push_back(Point(p.x, p.y - 1));
        }
        if (p.y == 6) {
          if (board[p.x][p.y - 1].col_of_figure == 'e' and
              board[p.x][p.y - 2].col_of_figure == 'e') {
            answer.push_back(Point(p.x, p.y - 2));
          }
        }
      }
      for (auto x : board[p.x][p.y].f->threat(p)) {
        // std::cout << x.x << ' ' << x.y << "\n";
        if (board[p.x][p.y].col_of_figure == 'w' && board[x.x][x.y].col_of_figure == 'b' and x.y > p.y) {
          answer.push_back(x);
        } else if (board[p.x][p.y].col_of_figure == 'b' && board[x.x][x.y].col_of_figure == 'w' and x.y < p.y) {
          answer.push_back(x);
        }
      }
    }

    if (this_name == 'K') {
      for (auto x : board[p.x][p.y].f->threat(p)) {
        if (board[p.x][p.y].col_of_figure == 'w') {
          if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure and
              black_threat[x.x][x.y] == false) {
            answer.push_back(x);
          }
        }
        if (board[p.x][p.y].col_of_figure == 'b') {
          if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure and
              white_threat[x.x][x.y] == false) {
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
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        white_threat[i][j] = false;
        black_threat[i][j] = false;
      }
    }

    move_number[0] = 0;
    move_number[1] = 0;
    move_number[2] = 0;
    move_number[3] = 0;
    move_number[4] = 0;
    move_number[5] = 0;

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
    //std::cout << "\x1B[2J\x1B[H";
    system("cls");
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
          std::cout << "\x1b[31m" << ch << "\x1b[0m" << "  ";
        } else { std::cout << ch << "  ";}

        //std::cout << ch << "  ";
      }
      std::cout << "\n";
    }
  }

  std::vector<Point> bit_field(char color) {
    std::vector<Point> bit;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (board[i][j].col_of_figure == color && board[i][j].f->name != 'K') {
          for (auto x : dostig(board[i][j].f, Point(i, j))) {
            bit.push_back(x);
          }
        } else if (board[i][j].col_of_figure == color && board[i][j].f->name == 'K') {
          for (auto x : board[i][j].f->ach(Point(i , j), color)) {
            bit.push_back(x);
          }
        }
      }
    }
  }

  bool Is_possible(char name, Point first, Point second) {
    if (board[first.x][first.y].f == nullptr or board[first.x][first.y].f->name != name or first == second) {
      return false;
    }
    bool flag = false;
    auto a = board[first.x][first.y].f->ach(first, current_move);

    for (auto x : (a)) {
      if (second == x) {
        flag = true;
        break;
      }
    }
    if (flag == false) {
      return false;
    }
    // for (auto x : dostig(board[first.x][first.y].f, first)) {
    //   // std::cout << x.x << " " << x.y << "\n";
    // }
    auto achiev = dostig(board[first.x][first.y].f, first);
    for (auto x : achiev) {
      if (x == second) {
        return true;
      }
    }
    return false;
  }

  bool Make_move(std::string move) {
    if (move == "/start" or move == "/s") {
      std::cout << "Starting new game..." << std::endl;
      StartPosition();
      return true;
    }
    if (move == "/quit" or move == "/q" or move == "/exit") {
      std::cout << "Quitting..." << std::endl;
      Clear();
      exit(0);
      return false;
    }
    if (move == "0-0-0") {
      if (current_move == 'w') {
        if (move_number[0] != 0 or move_number[2] != 0)
          return false;
        if (board[0][1].col_of_figure != 'e' or
            board[0][2].col_of_figure != 'e' or
            board[0][3].col_of_figure != 'e')
          return false;
        if (black_threat[0][2] or black_threat[0][3] or black_threat[0][4])
          return false;
        move_number[0] = 1;
        move_number[2] = 1;
        board[0][2] = board[0][4];
        board[0][4].f = nullptr;
        board[0][4].col_of_figure = 'e';
        board[0][3].f = board[0][0].f;
        board[0][3].col_of_figure = 'w';
        board[0][0].f = nullptr;
        board[0][0].col_of_figure = 'e';
        return true;
      }
      if (current_move == 'b') {
        if (move_number[1] != 0 or move_number[4] != 0)
          return false;
        if (board[7][1].col_of_figure != 'e' or
            board[7][2].col_of_figure != 'e' or
            board[7][3].col_of_figure != 'e')
          return false;
        if (white_threat[7][2] or white_threat[7][3] or white_threat[7][4])
          return false;
        move_number[1] = 1;
        move_number[4] = 1;
        board[7][2] = board[7][4];
        board[7][4].f = nullptr;
        board[7][4].col_of_figure = 'e';
        board[7][3].f = board[7][0].f;
        board[7][3].col_of_figure = 'b';
        board[7][0].f = nullptr;
        board[7][0].col_of_figure = 'e';
        return true;
      }
    }
    if (move == "0-0") {
      if (current_move == 'w') {
        if (move_number[0] != 0 or move_number[3] != 0)
          return false;
        if (board[0][5].col_of_figure != 'e' or
            board[0][6].col_of_figure != 'e')
          return false;
        if (black_threat[0][4] or black_threat[0][5] or black_threat[0][6])
          return false;
        move_number[0] = 1;
        move_number[3] = 1;
        board[0][6] = board[0][4];
        board[0][4].f = nullptr;
        board[0][4].col_of_figure = 'e';
        board[0][5].f = board[0][7].f;
        board[0][5].col_of_figure = 'w';
        board[0][7].f = nullptr;
        board[0][7].col_of_figure = 'e';
        return true;
      }
      if (current_move == 'b') {
        if (move_number[1] != 0 or move_number[5] != 0)
          return false;
        if (board[7][5].col_of_figure != 'e' or
            board[7][6].col_of_figure != 'e')
          return false;
        if (white_threat[7][4] or white_threat[7][5] or white_threat[7][6])
          return false;
        move_number[1] = 1;
        move_number[5] = 1;
        board[7][6] = board[7][4];
        board[7][4].f = nullptr;
        board[7][4].col_of_figure = 'e';
        board[7][5].f = board[7][7].f;
        board[7][5].col_of_figure = 'b';
        board[7][7].f = nullptr;
        board[7][7].col_of_figure = 'e';
        return true;
      }
    }
    if (move.size() != 6)
      return false;
    if (move[3] != '-' and move[3] != 'x' and move[3] != ' ')
      return false;
    if (move[1] < 'a' or move[1] > 'h')
      return false;
    if (move[4] < 'a' or move[4] > 'h')
      return false;
    if (move[2] < '1' or move[2] > '8')
      return false;
    if (move[5] < '1' or move[5] > '8')
      return false;
    char name = move[0];
    Point first(move[1] - 'a', move[2] - '1');
    Point second(move[4] - 'a', move[5] - '1');
    if (Is_possible(name, first, second)) {
      if (board[second.x][second.y].f != nullptr) {
        delete board[second.x][second.y].f;
        board[second.x][second.y].f = nullptr;
        board[second.x][second.y].col_of_figure = 'e';
      }
      board[second.x][second.y].f = board[first.x][first.y].f;
      board[second.x][second.y].col_of_figure =
          board[first.x][first.y].col_of_figure;
      board[first.x][first.y].f = nullptr;
      board[first.x][first.y].col_of_figure = 'e';


      for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
          if (current_move == 'w') {
            if (Find(bit_field('w'), Point(i , j))) {
              white_threat[i][j] = true;
            } else {
              white_threat[i][j] = false;
            }
          } else {
            if (Find(bit_field('b'), Point(i , j))) {
              white_threat[i][j] = true;
            } else {
              white_threat[i][j] = false;
            }
          }

        }
      }

      return true;
    }
    return false;
  }
};
