#include "point.hpp"
#include <vector>

struct BaseFigure {
  char name;
  virtual std::vector<Point> threat(const Point &p) = 0;
  virtual std::vector<Point> ach(const Point &p, char col) { return threat(p); }
  virtual ~BaseFigure() = default;
};

struct Knight : BaseFigure {
  std::vector<Point> threat(const Point &p) override {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == 1 and std::abs(p.y - j) == 2 or
            std::abs(p.x - i) == 2 and std::abs(p.y - j) == 1) {
          answer.push_back(Point(i, j));
        }
      }
    }
    return answer;
  }
};

struct Bishop : BaseFigure {
  std::vector<Point> threat(const Point &p) override {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == std::abs(p.y - j) and i != p.x) {
          answer.push_back(Point(i, j));
        }
      }
    }
    return answer;
  }
};

struct King : BaseFigure {
  std::vector<Point> threat(const Point &p) override {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) <= 1 and std::abs(p.y - j) <= 1 and
            Point(i, j) != p) {
          answer.push_back(Point(i, j));
        }
      }
    }
    return answer;
  }
};

struct Rook : BaseFigure {
  std::vector<Point> threat(const Point &p) override {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (p.x == i and p.y != j or p.x != i and p.y == j) {
          answer.push_back(Point(i, j));
        }
      }
    }
    return answer;
  }
};

struct Pawn : BaseFigure {
  std::vector<Point> threat(const Point &p) override {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == 1 and (p.y + 1 == j || p.y - 1 == j)) {
          answer.push_back(Point(i, j));
        }
      }
    }
    return answer;
  }

  std::vector<Point> ach(const Point &p, char col) override {
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
    for (auto x : threat(p)) {
      answer.push_back(x);
    }
    return answer;
  }
};

struct Queen : BaseFigure {
  std::vector<Point> threat(const Point &p) override {
    std::vector<Point> answer;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (std::abs(p.x - i) == std::abs(p.y - j) and i != p.x) {
          answer.push_back(Point(i, j));
        }
        if (p.x == i and p.y != j or p.x != i and p.y == j) {
          answer.push_back(Point(i, j));
        }
      }
    }
    return answer;
  }
};