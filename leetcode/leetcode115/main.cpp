#include <iostream>
#include <string>
#include "distinct_subseq.hpp"

int main()
{
  std::string s("babgbag");
  std::string t("bag");
  std::cout << Solution::numDistinct(s, t) << std::endl;
  return 0;
}





