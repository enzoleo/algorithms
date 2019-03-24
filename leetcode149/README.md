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

# Improvement
显而易见上面的算法太慢了，虽然很多操作看起来让结构变得完整，但就这道题目来讲实际上是不必要的，比如说`Line`这个类没有太大的存在意义，并且重载它的`<`运算符太耗时了。在改进的版本中`set`和`map`的使用都被彻底删掉了，我们只需要对`vector<Point>`的数据进行去重，记录每一个点的权重就可以了。
```
using PointWeight = std::pair<Point*, std::size_t>;
std::vector<PointWeight> weights;
```
定义点的权重由它在内存中的地址和一个非负整数权重的`pair`组成。遍历每一个点，寻找当前`weights`中是否已经有点和这个点是等价的，如果找到了，就在其权重上加一，表示它的出现次数多了一次；如果没有找到，那么将这个点加入到`weights`当中，权重为1。出于效率上的原因，用C++11的`emplace_back`替代`push_back`。
```
for (auto &point : points) {
  auto it = weights.begin(), end = weights.end();
  for (; it != end; ++it)
    if (*(it->first) == point) {
      ++(it->second);
      break;
    }
  if (it == end) weights.emplace_back(&point, 1);
}
```
现在完成了去重的步骤。与上面的办法不同的是，不再另外定义`Line`类，因为狭义地讲，这里每一条直线都可以用两个weights中的点的索引表示，因此两个非负整表示一条直线就足够了。
```
using Line = std::pair<std::size_t, std::size_t>;
std::vector<std::pair<Line, std::size_t> > lines;
```
上面这个`lines`的每一个条目都是一条直线和它经过的点的总权重。和上面类似地，遍历去重后的`weights`中的每一个点`p`，检查它是否坐落在当前`lines`的某一条直线上，也就是遍历`lines`的每一条直线`line`，判断决定它的两个点`p1,p2`以及当前点`p`是否三点共线。
```
Point& p1 = *(weights[line.first].first);
Point& p2 = *(weights[line.second].first);
locate = ((long)(p.x - p1.x) * (p.y - p2.y) ==
          (long)(p.x - p2.x) * (p.y - p1.y));
```
注意这里要转换成`long`类型，因为`int`类型对于表达两个整数的乘积是不够用的。变量`locate`为`true`时，表示点`p`坐落在直线`lines`上，这时就要把`p`记录在`weights`中的权重加入到经过它的直线`line`的总权重中。如果没有找到这样的直线，表示点`p`和之前遍历过的每一点决定的直线，都是一条新的直线，需要被加入到`lines`中：
```
for (int j = 0; j != i; ++j) {
  int w = weights[j].second + weight;
  lines.emplace_back(std::make_pair(j, i), w);
}
```
最后循环结束后选出总权重最大的即可。当然，这个最大权重可以在上面的遍历步骤中同时完成。

一个问题是为什么这样做可以极大地改进效率？它避免了排序的操作，根本没有必要去定义如何给点或者直线排序，只需要判定什么样的情况下两个点或者两条直线等价。应该说这是最大的一个改进。实现的时候C++的代码有很多可以深挖的地方，比如指针和引用的使用，比如向数据结构插入新元素时使用`emplace`，一个小细节可以也可以很大程度地影响效率。
