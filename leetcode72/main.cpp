#include <iostream>
#include <vector>
#include <string>
#include "edit_dist.hpp"

int main()
{
  std::string w1 = "dinirazine";
  std::string w2 = "acetylp";

  int res = Solution::minDistance(w1, w2);
  std::cout << res << std::endl;
  return 0;
}
