#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstring>

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
  std::set<Point> points;

  /**
   * At least two different points should be specified to construct a line.
   * It is a common sense that two different points determine a line exactly
   * and uniquely.
   */
  Line(Point _p1, Point _p2) : point1(_p1), point2(_p2) {
    points.insert(_p1);
    points.insert(_p2);
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
      long ldxy =
          static_cast<long>(p1.y) * p2.x -
          static_cast<long>(p1.x) * p2.y;
      long rdxy =
          static_cast<long>(p3.y) * p4.x -
          static_cast<long>(p3.x) * p4.y;
      // Here we use a complicated method to check whether two lines are
      // equivalent, because the given coordinates are all integers and thus
      // we can avoid floating points comparison.
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
    // Find the weight (number of occurrence) of each point in the vector.
    std::size_t size = points.size();
    std::map<Point, std::size_t> pset;
    for (std::size_t i = 0; i < size; ++i) ++pset[points[i]];
    std::vector<Point> pts;
    std::transform(pset.begin(), pset.end(), std::back_inserter(pts),
                   [&](const std::pair<Point, std::size_t>& item)
                   { return item.first; });

    // Return zero if the input vector has less than 2 points.
    size = pts.size();
    if (size == 0) return 0;
    if (size == 1) return pset[pts[0]];
    
    // We define a set (this set is ordered, so we must define how to sort
    // the line objects) of lines here.
    std::set<Line> table;
    for (std::size_t i = 0; i < size; ++i) {
      Point& point = pts[i];
      for (std::size_t j = 0; j < i; ++j) {
        // For each point, draw a line between it and every previous point,
        // then try to find such line in the map, if found, insert the
        // current point and plus 1 to the corresponding value field.
        Line line(point, pts[j]);
        auto it = table.find(line);
        if (it == table.end())
          table.insert(line);
        // Note the map::find() will return a const iterator, so we have to
        // cast the type to discard the qualifier before inserting.
        else
          const_cast<std::set<Point>&>(it->points).insert(point);
      }
    }
    auto total =
        [&](const Line& line) {
          return std::accumulate(line.points.begin(), line.points.end(), 0,
                                 [&](std::size_t w, const Point& p)
                                 { return w + pset[p]; });
        };
    // Now find the maximum number of points on a line.
    const Line& target = *std::max_element(
        table.begin(), table.end(),
        [&](const Line& line1, const Line& line2)
        { return total(line1) < total(line2); });
    int num = total(target);
    return num;
  }

};

void fromString(std::vector<Point>& points, char* str) {
    char *token = std::strtok(str, " [,]");
    while (token != NULL) {
      int x = strtol(token, NULL, 10);
      token = std::strtok(NULL, " [,]");
      int y = strtol(token, NULL, 10);
      token = std::strtok(NULL, " [,]");
      points.push_back(Point(x, y));
    }
}

int main() {
  char str[] = "[[40,-23],[9,138],[429,115],[50,-17],[-3,80],[-10,33],[5,-21],[-3,80],[-6,-65],[-18,26],[-6,-65],[5,72],[0,77],[-9,86],[10,-2],[-8,85],[21,130],[18,-6],[-18,26],[-1,-15],[10,-2],[8,69],[-4,63],[0,3],[-4,40],[-7,84],[-8,7],[30,154],[16,-5],[6,90],[18,-6],[5,77],[-4,77],[7,-13],[-1,-45],[16,-5],[-9,86],[-16,11],[-7,84],[1,76],[3,77],[10,67],[1,-37],[-10,-81],[4,-11],[-20,13],[-10,77],[6,-17],[-27,2],[-10,-81],[10,-1],[-9,1],[-8,43],[2,2],[2,-21],[3,82],[8,-1],[10,-1],[-9,1],[-12,42],[16,-5],[-5,-61],[20,-7],[9,-35],[10,6],[12,106],[5,-21],[-5,82],[6,71],[-15,34],[-10,87],[-14,-12],[12,106],[-5,82],[-46,-45],[-4,63],[16,-5],[4,1],[-3,-53],[0,-17],[9,98],[-18,26],[-9,86],[2,77],[-2,-49],[1,76],[-3,-38],[-8,7],[-17,-37],[5,72],[10,-37],[-4,-57],[-3,-53],[3,74],[-3,-11],[-8,7],[1,88],[-12,42],[1,-37],[2,77],[-6,77],[5,72],[-4,-57],[-18,-33],[-12,42],[-9,86],[2,77],[-8,77],[-3,77],[9,-42],[16,41],[-29,-37],[0,-41],[-21,18],[-27,-34],[0,77],[3,74],[-7,-69],[-21,18],[27,146],[-20,13],[21,130],[-6,-65],[14,-4],[0,3],[9,-5],[6,-29],[-2,73],[-1,-15],[1,76],[-4,77],[6,-29]]";
  std::vector<Point> points;
  fromString(points, str);
  Solution sol;
  int maxNum = sol.maxPoints(points);
  std::cout << maxNum << std::endl;
  return 0;
}

