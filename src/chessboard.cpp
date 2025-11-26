#include "chessboard.hpp"

bool Find(std::vector<Point> vec, Point p) {
  for (auto x : vec) {
    if (x == p) {
      return true;
    }
  }
  return false;
}

void Obnova(Board &b) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (Find(b.bit_field('w'), Point(i, j))) {
        b.white_threat[i][j] = true;
      } else {
        b.white_threat[i][j] = false;
      }
      if (Find(b.bit_field('b'), Point(i, j))) {
        b.black_threat[i][j] = true;
      } else {
        b.black_threat[i][j] = false;
      }
    }
  }
}

std::vector<Point> Board::dostig(Point p, bool mode) const {
  char this_name = board[p.x][p.y].f->name;
  std::vector<Point> answer;
  std::vector<Point> temp;

  if (this_name == 'N') {
    for (auto x : board[p.x][p.y].f->ach(p, board[p.x][p.y].col_of_figure)) {
      if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure) {
        answer.push_back(x);
      } else {
        temp.push_back(x);
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
                       (board[p.x][i + 1].col_of_figure == 'e' ||
                        i + 1 == p.y)) {
              answer.push_back(Point(p.x, i));
              break;
            } else if (board[p.x][i].col_of_figure ==
                           board[p.x][p.y].col_of_figure &&
                       (board[p.x][i + 1].col_of_figure == 'e' ||
                        i + 1 == p.y)) {
              temp.push_back(Point(p.x, i));
              break;
            } else {
              break;
            }
          }
        }

        if (p.y < x.y) {
          for (int i = p.y + 1; i <= x.y; ++i) {
            if (board[p.x][i].col_of_figure == 'e') {
              answer.push_back(Point(p.x, i));
            } else if (board[p.x][i].col_of_figure !=
                           board[p.x][p.y].col_of_figure &&
                       (board[p.x][i - 1].col_of_figure == 'e' ||
                        i - 1 == p.y)) {
              answer.push_back(Point(p.x, i));
              break;
            } else if (board[p.x][i].col_of_figure ==
                       board[p.x][p.y].col_of_figure) {
              temp.push_back(Point(p.x, i));
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
                       (board[i + 1][p.y].col_of_figure == 'e' ||
                        i + 1 == p.x)) {
              answer.push_back(Point(i, p.y));
              break;
            } else if (board[i][p.y].col_of_figure ==
                       board[p.x][p.y].col_of_figure) {
              temp.push_back(Point(i, p.y));
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
                       (board[i - 1][p.y].col_of_figure == 'e' ||
                        i - 1 == p.x)) {
              answer.push_back(Point(i, p.y));
              break;
            } else if (board[i][p.y].col_of_figure ==
                           board[p.x][p.y].col_of_figure &&
                       (board[i - 1][p.y].col_of_figure == 'e' ||
                        i - 1 == p.x)) {
              temp.push_back(Point(i, p.y));
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
                       (board[i + 1][j + 1].col_of_figure == 'e' ||
                        Point(i + 1, j + 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else if (board[i][j].col_of_figure ==
                           board[p.x][p.y].col_of_figure &&
                       (board[i + 1][j + 1].col_of_figure == 'e' ||
                        Point(i + 1, j + 1) == p)) {
              temp.push_back(Point(i, j));
              break;
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
                       (board[i - 1][j - 1].col_of_figure == 'e' ||
                        Point(i - 1, j - 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else if (board[i][j].col_of_figure ==
                           board[p.x][p.y].col_of_figure &&
                       (board[i - 1][j - 1].col_of_figure == 'e' ||
                        Point(i - 1, j - 1) == p)) {
              temp.push_back(Point(i, j));
              break;
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
              answer.push_back(Point(i, j));
            } else if (board[i][j].col_of_figure !=
                           board[p.x][p.y].col_of_figure &&
                       (board[i + 1][j - 1].col_of_figure == 'e' ||
                        Point(i + 1, j - 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else {
              temp.push_back(Point(i, j));
              break;
            }
          }
        }
        if (p.x < x.x) {
          for (int i = p.x + 1, j = p.y - 1; i <= x.x; ++i, --j) {
            if (board[i][j].col_of_figure == 'e') {
              answer.push_back(Point(i, j));
            } else if (board[i][j].col_of_figure !=
                           board[p.x][p.y].col_of_figure &&
                       (board[i - 1][j + 1].col_of_figure == 'e' ||
                        Point(i - 1, j + 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else {
              temp.push_back(Point(i, j));
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
                       (board[i + 1][j + 1].col_of_figure == 'e' ||
                        Point(i + 1, j + 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else {
              temp.push_back(Point(i, j));
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
                       (board[i - 1][j - 1].col_of_figure == 'e' ||
                        Point(i - 1, j - 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else {
              temp.push_back(Point(i, j));
              break;
            }
          }
        }
      }

      if ((p.x - x.x) == -(p.y - x.y)) {
        if (p.x > x.x) {
          for (int i = p.x - 1, j = p.y + 1; i >= x.x; --i, ++j) {
            if (board[i][j].col_of_figure == 'e') {
              answer.push_back(Point(i, j));
            } else if (board[i][j].col_of_figure !=
                           board[p.x][p.y].col_of_figure &&
                       (board[i + 1][j - 1].col_of_figure == 'e' ||
                        Point(i + 1, j - 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else {
              temp.push_back(Point(i, j));
              break;
            }
          }
        }
        if (p.x < x.x) {
          for (int i = p.x + 1, j = p.y - 1; i <= x.x; ++i, --j) {
            if (board[i][j].col_of_figure == 'e') {
              answer.push_back(Point(i, j));
            } else if (board[i][j].col_of_figure !=
                           board[p.x][p.y].col_of_figure &&
                       (board[i - 1][j + 1].col_of_figure == 'e' ||
                        Point(i - 1, j + 1) == p)) {
              answer.push_back(Point(i, j));
              break;
            } else {
              temp.push_back(Point(i, j));
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
                       (board[p.x][i + 1].col_of_figure == 'e' ||
                        i + 1 == p.y)) {
              answer.push_back(Point(p.x, i));
              break;
            } else {
              temp.push_back(Point(p.x, i));
              break;
            }
          }
        }

        if (p.y < x.y) {
          for (int i = p.y + 1; i <= x.y; ++i) {
            if (board[p.x][i].col_of_figure == 'e') {
              answer.push_back(Point(p.x, i));
            } else if (board[p.x][i].col_of_figure !=
                           board[p.x][p.y].col_of_figure &&
                       (board[p.x][i - 1].col_of_figure == 'e' ||
                        i - 1 == p.y)) {
              answer.push_back(Point(p.x, i));
              break;
            } else if (board[p.x][i].col_of_figure ==
                       board[p.x][p.y].col_of_figure) {
              temp.push_back(Point(p.x, i));
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
                       (board[i + 1][p.y].col_of_figure == 'e' ||
                        i + 1 == p.x)) {
              answer.push_back(Point(i, p.y));
              break;
            } else if (board[i][p.y].col_of_figure ==
                       board[p.x][p.y].col_of_figure) {
              temp.push_back(Point(i, p.y));
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
                       (board[i - 1][p.y].col_of_figure == 'e' ||
                        i - 1 == p.x)) {
              answer.push_back(Point(i, p.y));
              break;
            } else {
              temp.push_back(Point(i, p.y));
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
        if (board[p.x][p.y + 1].col_of_figure == 'e' &&
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
        if (board[p.x][p.y - 1].col_of_figure == 'e' &&
            board[p.x][p.y - 2].col_of_figure == 'e') {
          answer.push_back(Point(p.x, p.y - 2));
        }
      }
    }
    for (auto x : board[p.x][p.y].f->threat(p)) {
      // std::cout << x.x << ' ' << x.y << "\n";
      if (board[p.x][p.y].col_of_figure == 'w' &&
          board[x.x][x.y].col_of_figure == 'b' && x.y > p.y) {
        answer.push_back(x);
      } else if (board[p.x][p.y].col_of_figure == 'b' &&
                 board[x.x][x.y].col_of_figure == 'w' && x.y < p.y) {
        answer.push_back(x);
      }
    }
  }

  if (this_name == 'K') {
    for (auto x : board[p.x][p.y].f->threat(p)) {
      if (board[p.x][p.y].col_of_figure == 'w') {
        if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure &&
            black_threat[x.x][x.y] == false) {
          answer.push_back(x);
        }
      }
      if (board[p.x][p.y].col_of_figure == 'b') {
        if (board[x.x][x.y].col_of_figure != board[p.x][p.y].col_of_figure &&
            white_threat[x.x][x.y] == false) {
          answer.push_back(x);
        }
      }
    }
  }
  /*
  for (auto &x : answer) {
    if (x == p) {
      std::swap(x, answer[answer.size() - 1]);
      answer.pop_back();
    }
  }
  */
  if (mode) {
    return temp;
  }
  return answer;
}
