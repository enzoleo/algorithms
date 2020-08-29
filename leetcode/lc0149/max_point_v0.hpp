#ifndef _MAX_POINT_V0_HPP_
#define _MAX_POINT_V0_HPP_

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

/**
 * The Point struct.
 * In the problem specification, this definition is NOT allowed to change.
 *
 * For usage of this struct in STL data structure, especially orderd data
 * structure like std::set, std::map, etc., here we additionally overload
 * the operators ==, <, for this struct.
 */
struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

/**
 * Note the operator oveloading is outside the class definition.
 * The operator should not be a member function of class Point, as the
 * two arguments are actually symmetric. (Of course we are not allowed to
 * change the original definition of class Point.)
 */
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
  Line() = delete;
  Line(const Point& _p1, const Point& _p2)
      : point1(&_p1), point2(&_p2) {
    points.emplace(_p1);
    points.emplace(_p2);
  }
  const Point& p1() const { return *(this->point1); }
  const Point& p2() const { return *(this->point2); }
  
private:
  const Point *point1, *point2;
};

/**
 * This function is very important for us to determine the order of lines.
 * A line can be simply represented by its slope and bias (the slope is
 * not necessary to exist). The comparison we use here is that
 *
 * [1] If slope values of two lines both exist, compare (k1, b1) and
 *     (k2, b2) by dictionary order.
 * [2] If only one slope value exists, the line with existing slope should
 *     be smaller than the other one.
 * [3] If both do not exist, then both lines can be represented as a simple
 *     equality x = c, where c is a constant. Compare c1 and c2, where the
 *     lines can be represented by x = c1 and x = c2 respectively.
 *
 * @return LINE_SMALLER, if @lhs is smaller than @rhs.
 * @return LINE_EQUIV, if @lhs and @rhs are actually equivalent, or in
 *         other words, the same line.
 * @return LINE_LARGER, if @lhs is larger than @rhs.
 */
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

class Solution {
public:

  Solution() {    
    std::map<Point, std::size_t>().swap(this->pset);
  }
  
  int maxPoints(std::vector<Point>& points) {
    // Find the weight (number of occurrence) of each point in the vector.
    // Return zero if the input vector has no point.
    std::size_t size = points.size();
    if (size == 0) return 0;
    
    for (std::size_t i = 0; i < size; ++i) ++pset[points[i]];
    std::vector<Point> pts;
    pts.reserve(pset.size());
    for(auto it = pset.begin(), end = pset.end(); it != end; ++it)
      pts.emplace_back(it->first);

    size = pts.size();
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
        // Note the map::find() will return a const iterator, so we have to
        // cast the type to discard the qualifier before inserting.
        if (it == table.end()) table.emplace(line);
        else const_cast<std::set<Point>&>(it->points).emplace(point);
      }
    }
    int num = 0;
    // Also you can use other c++11 features to simplify this loop, but
    // probably you will lose efficiency.
    for (auto it = table.begin(), end = table.end(); it != end; ++it) {
      int tmp = total(*it);
      if (tmp > num) num = tmp;
    }
    return num;
  }

private:

  /**
   * For each line, compute the total weights of points on it.
   * The return value is std::size_t type.
   */
  std::size_t total(const Line& line) {
    std::size_t sum = 0;
    for (auto it = line.points.begin(), end = line.points.end();
         it != end; ++it) sum += pset[*it];
    return sum;
  }
  std::map<Point, std::size_t> pset;
};

#endif

