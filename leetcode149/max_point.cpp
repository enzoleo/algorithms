#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>

enum LineEquiv { LINE_SMALLER, LINE_EQUIV, LINE_LARGER };

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
bool operator<(const Point& lhs, const Point& rhs) {
  return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}

class Line {
public:
  /**
   * There are multiple different points on a line.
   */
  std::vector<Point> points;

  /**
   * At least two different points should be specified to construct a line.
   * It is a common sense that two different points determine a line exactly
   * and uniquely.
   */
  Line(Point _p1, Point _p2) : point1(_p1), point2(_p2) {
    points.push_back(_p1);
    points.push_back(_p2);
  }

  const Point& p1() const { return this->point1; }
  const Point& p2() const { return this->point2; }
  
private:

  /**
   * The two points which exactly and uniquely determine the line.
   * Once a line is constructed, the two points are actually automatically
   * registered. Additionally, the two points should remain unchanged
   * unless the geometric information of the line changes.
   */
  Point point1, point2;
};

LineEquiv diff(const Line& lhs, const Line& rhs) {
  // Get the four relavant points on the two lines.
  const Point &p1 = lhs.p1(), &p2 = lhs.p2();
  const Point &p3 = rhs.p1(), &p4 = rhs.p2();
  int ldx = p2.x - p1.x, rdx = p4.x - p3.x;

  // The case id of 4 possible cases.
  int id = (ldx == 0) + 2 * (rdx == 0);
  switch (id) {
    case 0: {
      int flag = (((ldx > 0) && (rdx > 0)) ||
                  ((ldx < 0) && (rdx < 0))) * 2 - 1;
      // Carefully handle the types because for large integers, their
      // multiplication result is possible to be larger than maximum
      // integer that can be represented by computer.
      long ldy = static_cast<long>(p2.y - p1.y);
      long rdy = static_cast<long>(p4.y - p3.y);
      long ldxy = static_cast<long>(p1.y) * p2.x -
          static_cast<long>(p1.x) * p2.y;
      long rdxy = static_cast<long>(p3.y) * p4.x -
          static_cast<long>(p3.x) * p4.y;
      long diff1 = (ldy * rdx - rdy * ldx) * flag;
      long diff2 = (ldxy * rdx - rdxy * ldx) * flag;
      if (diff1 < 0 || (diff1 == 0 && diff2 < 0)) return LINE_SMALLER;
      else if (diff1 == 0 && diff2 == 0) return LINE_EQUIV;
      else return LINE_LARGER;
    }
    case 1: return LINE_LARGER;
    case 2: return LINE_SMALLER;
    case 3:
      if (p1.x < p3.x) return LINE_SMALLER;
      else if (p1.x == p3.x) return LINE_EQUIV;
      else return LINE_LARGER;
  }
  return LINE_EQUIV;
}

bool operator==(const Line& lhs, const Line& rhs) {
  return diff(lhs, rhs) == LINE_EQUIV;
}
bool operator<(const Line& lhs, const Line& rhs) {
  return diff(lhs, rhs) == LINE_SMALLER;
}
bool operator>(const Line& lhs, const Line& rhs) {
  return diff(lhs, rhs) == LINE_LARGER;
}

class Solution {
public:
  int maxPoints(std::vector<Point>& points) {
    // Return zero if the input vector has less than 2 points.
    std::size_t size = points.size();
    if (size < 3) return size;
    
    // We define a map (this map is ordered, so we must define how to sort
    // the line objects) to represent the number of points located on each
    // line. The equivalence among lines will be used.
    std::map<Line, std::size_t> table;
    for (std::size_t i = 0; i < size; ++i) {
      Point& point = points[i];
      for (std::size_t j = 0; j < i; ++j) {
        // For each point, draw a line between it and every previous point,
        // then try to find such line in the map, if found, insert the
        // current point and plus 1 to the corresponding value field.
        Line line(point, points[j]);
        auto it = table.find(line);
        if (it == table.end()) table.insert(std::make_pair(line, 1));
        // Note the map::find() will return a const iterator, so we have to
        // cast the type to discard the qualifier before inserting.
        else {
          auto vec = const_cast<std::vector<Point>&>(it->first.points);
          vec.push_back(points[i]);
          ++(it->second);
        }
      }
    }
    // Now find the maximum number of points on a line. If we denote the
    // optimal value as @n, the @num here is actually n*(n-1)/2.
    std::size_t num = std::max_element(
        table.begin(), table.end(),
        [&](const std::pair<Line, std::size_t>& item1,
            const std::pair<Line, std::size_t>& item2)
        { return item1.second < item2.second; }) -> second;
    int maxNum = (1 + static_cast<int>(std::sqrt(1 + 8 * num))) / 2;
    return maxNum;
  }
};

int main() {
  std::vector<Point> points;
  points.push_back(Point(0, 0));
  points.push_back(Point(1, 1));
  points.push_back(Point(0, 0));
  /*points.push_back(Point(5, 3));
  points.push_back(Point(4, 1));
  points.push_back(Point(2, 3));
  points.push_back(Point(1, 4));*/
  Solution sol;
  int maxNum = sol.maxPoints(points);
  std::cout << maxNum << std::endl;
  return 0;
}

