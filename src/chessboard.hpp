#include "figures.hpp"
#include <iostream>
#include <string>

bool Find(std::vector<Point> vec, Point p);

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
  std::vector<std::string> history;

  std::vector<Point> dostig(Point p, bool mode) const;
  std::vector<Point> Self_def(Point p) const;

  void StartPosition() {
    Clear();
    current_move = 'w';
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (j == 1 || j == 6) {
          board[i][j].f = new Pawn;
          board[i][j].f->name = 'P';
        }
        if (j == 0 || j == 7) {
          if (i == 0 || i == 7) {
            board[i][j].f = new Rook;
            board[i][j].f->name = 'R';
          }
          if (i == 1 || i == 6) {
            board[i][j].f = new Knight;
            board[i][j].f->name = 'N';
          }
          if (i == 2 || i == 5) {
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
          board[i][j].col_of_figure = 'e';
        }
      }
    }
  }

  void Print() {
    // std::cout << "\x1B[2J\x1B[H";
    system("clear");
    char picture[26][26];
    bool color[26][26];
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (i == 0 || i == 25) {
          picture[i][j] = '*';
        }
        if (j == 0 || j == 25) {
          picture[i][j] = '*';
        }
        if ((i == 0 || i == 25) && (j == 0 || j == 25)) {
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
        if (ch == 'N' || ch == 'B' || ch == 'R' || ch == 'Q' || ch == 'K' || ch
        == 'P') { if (color[j][25 - i]) std::cout << "\x1b[33m" << ch  <<
        "\x1b[0m" << "  "; else std::cout << "\x1b[34m" << ch  << "\x1b[0m" << "
        "; } else if (ch != ' ' && ch != '#') { std::cout << "\x1b[31m" << ch <<
        "\x1b[0m" << "  "; } else { std::cout << ch << "  ";}
        */
        std::cout << ch << "  ";
      }
      std::cout << "\n";
    }
  }

  std::vector<Point> bit_field(char color) {
    std::vector<Point> bit;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (board[i][j].col_of_figure == color && board[i][j].f->name != 'K' &&
            board[i][j].f->name != 'P') {
          for (auto x : dostig(Point(i, j), false)) {
            bit.push_back(x);
          }
          for (auto x : dostig(Point(i, j), true)) {
            bit.push_back(x);
          }
        } else if (board[i][j].col_of_figure == color &&
                   board[i][j].f->name == 'K') {
          for (auto x : board[i][j].f->ach(Point(i, j), color)) {
            bit.push_back(x);
          }
          for (auto x : dostig(Point(i, j), true)) {
            bit.push_back(x);
          }
        } else if (board[i][j].col_of_figure == color &&
                   board[i][j].f->name == 'P') {
          for (auto x : board[i][j].f->threat(Point(i, j))) {
            if (color == 'w' && x.y > j) {
              bit.push_back(x);
            } else if (color == 'b' && x.y < j) {
              bit.push_back(x);
            }
          }
        }
      }
    }
    return bit;
  }

  inline bool Is_possible(char name, Point first, Point second) const;
  inline bool Premove(Point first, Point second) const;
  inline int Make_move(std::string move);
};

void Obnova(Board &b);

bool Board::Is_possible(char name, Point first, Point second) const {
  if (board[first.x][first.y].f == nullptr ||
      board[first.x][first.y].f->name != name || first == second) {
    return false;
  }
  if (board[first.x][first.y].col_of_figure != current_move) {
    return false;
  }

  bool flag = false;
  auto a = board[first.x][first.y].f->ach(first, current_move);
  for (auto x : a) {
    if (second == x) {
      flag = true;
      break;
    }
  }
  if (flag == false) {
    return false;
  }

  auto achiev = dostig(first, false);
  for (auto x : achiev) {
    if (x == second && Premove(first, second)) {
      return true;
    }
  }
  return false;
}

bool Board::Premove(Point first, Point second) const {
  Board copy = *this;
  if (copy.board[second.x][second.y].f != nullptr) {
    // delete copy.board[second.x][second.y].f;
    copy.board[second.x][second.y].f = nullptr;
    copy.board[second.x][second.y].col_of_figure = 'e';
  }
  copy.board[second.x][second.y].f = copy.board[first.x][first.y].f;
  copy.board[second.x][second.y].col_of_figure =
      copy.board[first.x][first.y].col_of_figure;
  copy.board[first.x][first.y].f = nullptr;
  copy.board[first.x][first.y].col_of_figure = 'e';
  Obnova(copy);

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (current_move == 'w' && copy.board[i][j].col_of_figure == 'w' &&
          copy.board[i][j].f->name == 'K' && copy.black_threat[i][j] == false) {
        return true;
      }
      if (current_move == 'w' && copy.board[i][j].col_of_figure == 'w' &&
          copy.board[i][j].f->name == 'K' && copy.black_threat[i][j] == true) {
        return false;
      }
      if (current_move == 'b' && copy.board[i][j].col_of_figure == 'b' &&
          copy.board[i][j].f->name == 'K' && copy.white_threat[i][j] == false) {
        return true;
      }
      if (current_move == 'b' && copy.board[i][j].col_of_figure == 'b' &&
          copy.board[i][j].f->name == 'K' && copy.white_threat[i][j] == true) {
        return false;
      }
    }
  }
  return true;
}

int Board::Make_move(std::string move) {
  if (move == "/start" || move == "/s") {
    std::cout << "Starting new game..." << std::endl;
    StartPosition();
    return -1;
  }
  if (move == "/quit" || move == "/q" || move == "/exit") {
    std::cout << "Quitting..." << std::endl;
    Clear();
    exit(0);
    return false;
  }
  if (move == "/history" || move == "/h") {
    std::cout << (history.size() == 0 ? "No moves yet" : "History:") << "\n";
    for (int i = 1; i < history.size(); i += 2) {
      std::cout << (i + 1) / 2 << ". " << history[i - 1] << " " << history[i]
                << "\n";
    }
    if (history.size() % 2 == 1) {
      std::cout << (history.size() + 1) / 2 << ". " << history.back() << "\n";
    }
    std::cout << "\nMake your move: \n";
    std::getline(std::cin, move);
    return Make_move(move);
  }
  if (move == "0-0-0") {
    if (current_move == 'w') {
      if (move_number[0] != 0 || move_number[2] != 0)
        return false;
      if (board[1][0].col_of_figure != 'e' ||
          board[2][0].col_of_figure != 'e' || board[3][0].col_of_figure != 'e')
        return false;
      if (black_threat[2][0] || black_threat[3][0] || black_threat[4][0])
        return false;
      move_number[0] = 1;
      move_number[2] = 1;
      board[2][0] = board[4][0];
      board[4][0].f = nullptr;
      board[4][0].col_of_figure = 'e';
      board[3][0].f = board[0][0].f;
      board[3][0].col_of_figure = 'w';
      board[0][0].f = nullptr;
      board[0][0].col_of_figure = 'e';
      history.push_back("0-0-0");
      return true;
    }
    if (current_move == 'b') {
      if (move_number[1] != 0 || move_number[4] != 0)
        return false;
      if (board[1][7].col_of_figure != 'e' ||
          board[2][7].col_of_figure != 'e' || board[3][7].col_of_figure != 'e')
        return false;
      if (white_threat[2][7] || white_threat[3][7] || white_threat[4][7])
        return false;
      move_number[1] = 1;
      move_number[4] = 1;
      board[2][7] = board[4][7];
      board[4][7].f = nullptr;
      board[4][7].col_of_figure = 'e';
      board[3][7].f = board[0][7].f;
      board[3][7].col_of_figure = 'b';
      board[0][7].f = nullptr;
      board[0][7].col_of_figure = 'e';
      history.push_back("0-0-0");
      return true;
    }
  }
  if (move == "0-0") {
    if (current_move == 'w') {
      if (move_number[0] != 0 || move_number[3] != 0)
        return false;
      if (board[5][0].col_of_figure != 'e' || board[6][0].col_of_figure != 'e')
        return false;
      if (black_threat[4][0] || black_threat[5][0] || black_threat[6][0])
        return false;
      move_number[0] = 1;
      move_number[3] = 1;
      board[6][0] = board[4][0];
      board[4][0].f = nullptr;
      board[4][0].col_of_figure = 'e';
      board[5][0].f = board[7][0].f;
      board[5][0].col_of_figure = 'w';
      board[7][0].f = nullptr;
      board[7][0].col_of_figure = 'e';
      history.push_back("0-0");
      return true;
    }
    if (current_move == 'b') {
      if (move_number[1] != 0 || move_number[5] != 0)
        return false;
      if (board[5][7].col_of_figure != 'e' || board[6][7].col_of_figure != 'e')
        return false;
      if (white_threat[4][7] || white_threat[5][7] || white_threat[6][7])
        return false;
      move_number[1] = 1;
      move_number[5] = 1;
      board[6][7] = board[4][7];
      board[4][7].f = nullptr;
      board[4][7].col_of_figure = 'e';
      board[5][7].f = board[7][7].f;
      board[5][7].col_of_figure = 'b';
      board[7][7].f = nullptr;
      board[7][7].col_of_figure = 'e';
      history.push_back("0-0");
      return true;
    }
  }

  if (move.size() != 6)
    return false;
  if (move[3] != '-' && move[3] != 'x' && move[3] != ' ')
    return false;
  if (move[1] < 'a' || move[1] > 'h')
    return false;
  if (move[4] < 'a' || move[4] > 'h')
    return false;
  if (move[2] < '1' || move[2] > '8')
    return false;
  if (move[5] < '1' || move[5] > '8')
    return false;
  char name = move[0];
  Point first(move[1] - 'a', move[2] - '1');
  Point second(move[4] - 'a', move[5] - '1');

  if (Is_possible(name, first, second)) {
    if (first.x == 0 && first.y == 0) {
      move_number[2] = 1;
    } else if (first.x == 7 && first.y == 0) {
      move_number[3] = 1;
    } else if (first.x == 0 && first.y == 7) {
      move_number[4] = 1;
    } else if (first.x == 7 && first.y == 7) {
      move_number[5] = 1;
    } else if (first.x == 4 && first.y == 0) {
      move_number[0] = 1;
    } else if (first.x == 4 && first.y == 7) {
      move_number[1] = 1;
    }
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
    move[3] = '-';
    history.push_back(move);
    return true;
  }
  return false;
}