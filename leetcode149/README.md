# Leetcode 149 - Max Points on a Line

看起来并不是一个容易的问题。尝试了两个版本的写法，第一种写法是最初的想法，但是从时间和内存上讲都很低效率，改进为第二种写法以后大幅提升了效率。有时候追求精简和可读性会导致效率的降低，要做到兼顾相当困难。

## Algorithm
首先一个必要的操作是对输入的点集去重，因为输入的点集有可能有多个点是重合的，但是它们都要被考虑在内。去重可以考虑`set`，`map`等数据结构，对应的需要重载`Point`类的`<, ==`运算符，或者`unordered_set`和`unordered_map`，可以不用重载`<`运算符，但要重载`Hash`。可以把每一个点在点集中出现的次数作为一个点的权重，因此`map`是一个可以考虑的选择，以点作为`Key`，以权重作为`Value`。

另外定义`Line`直线类，每一条直线都有一个点集，其中的点都坐落在这条直线上。
```
class Line {
public:
  std::set<Point> points;
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
```
这样一来，最简单的想法就是对去重后的点集，两两相连把直线依次加入到一个直线的`set`里面，并且在遍历过程中把点插入到经过它的每一条直线的`points`集合中。最后一步找到直线里点集合的`size`的最大值即可。这个想法的实现还有一个前提，`set`需要重载直线类的操作符，也就是说要定义两条直线的排序。直线可以表示成斜率和截距的组合，虽然不一定存在。一个比较直观的定义是用`(k,b)`的字典序来作为排序，如果两条直线其中之一的`k`不存在，那么定义`k`不存在的那条较大，如果两条直线的`k`都不存在，那么两条直线可以表示成`x=c`的形式，常数`C`大的直线更大。这个想法比较复杂，但是也依然可以实现。

之后的步骤就很平凡了，可以验证这个代码能够AC，但是时间和空间上的表现都太差。
```
int maxPoints(std::vector<Point>& points) {
  std::size_t size = points.size();
  if (size == 0) return 0;
    
  for (std::size_t i = 0; i < size; ++i) ++pset[points[i]];
  std::vector<Point> pts;
  pts.reserve(pset.size());
  for(auto it = pset.begin(), end = pset.end(); it != end; ++it)
    pts.emplace_back(it->first);

  size = pts.size();
  if (size == 1) return pset[pts[0]];
  std::set<Line> table;
  for (std::size_t i = 0; i < size; ++i) {
    Point& point = pts[i];
    for (std::size_t j = 0; j < i; ++j) {
      Line line(point, pts[j]);
      auto it = table.find(line);
      if (it == table.end()) table.emplace(line);
      else const_cast<std::set<Point>&>(it->points).emplace(point);
    }
  }
  int num = 0;
  for (auto it = table.begin(), end = table.end(); it != end; ++it) {
    int tmp = total(*it);
    if (tmp > num) num = tmp;
  }
  return num;
}
```
