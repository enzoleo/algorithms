#ifndef _MAX_POINT_FAST_HPP_
#define _MAX_POINT_FAST_HPP_

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstring>

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

class Solution {
public:

  Solution() { }
  
  int maxPoints(std::vector<Point>& points) {
    // Return zero if the input vector has no point. (use `int' here
    // instead of `size_t' as the vector size is not large)
    int size = points.size();
    if (size == 0) return 0;

    // Type renaming for code simplicity. The line can be determined by
    // two points represented as indices respectively.
    using PointWeight = std::pair<Point*, std::size_t>;
    using Line = std::pair<std::size_t, std::size_t>;
    
    // Every point is possible to appear multiple times, so we define the
    // occurrence of one point as its weight.
    std::vector<PointWeight> weights;
    for (auto &point : points) {
      auto it = weights.begin(), end = weights.end();
      for (; it != end; ++it)
        // Note the overloading of operator== here.
        if (*(it->first) == point) {
          ++(it->second);
          break;
        }
      // If no point in the map in found to be the same as the current
      // one, then insert the current point to the vector.
      if (it == end) weights.emplace_back(&point, 1);
    }
    // If only one point is in the vector after removing duplication.
    if (weights.size() == 1) return weights[0].second;
    
    // This is our target: the max number of points on a line.
    int num = 0;
    
    // Vector of each line and its corresponding number of points on it.
    std::vector<std::pair<Line, std::size_t> > lines;
    for (int i = 0, size = weights.size(); i != size; ++i) {
      // The @flag determines whether a point is found to locate on at
      // least one line in the current lines vector.
      // @locate determines whether one given point is exactly located on a
      // given line.
      bool flag = false, locate = false;
      std::size_t weight = weights[i].second;
      Point& p = *(weights[i].first);
      auto it = lines.begin(), end = lines.end();

      // For each point, check whether there is a line in the current
      // lines vector that goes through the point.
      for (; it != end; ++it) {
        Point& p1 = *(weights[it->first.first].first);
        Point& p2 = *(weights[it->first.second].first);
        locate = ((long)(p.x - p1.x) * (p.y - p2.y) ==
                  (long)(p.x - p2.x) * (p.y - p1.y));
        if (locate) {
          int w = (it->second += weight);
          if (num < w) num = w;
          flag = true;
        }
      }
      if (flag) continue;
      for (int j = 0; j != i; ++j) {
        // A new line should be added to the lines vector.
        int w = weights[j].second + weight;
        lines.emplace_back(std::make_pair(j, i), w);
        if (num < w) num = w;
      }
    }
    return num;
  }

};

#endif


