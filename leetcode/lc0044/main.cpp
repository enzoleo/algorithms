#include <iostream>
#include <string>
#include "wildcard.hpp"

int main()
{
  std::string s("aa");
  std::string t("a*");
  std::cout << Solution::isMatch(s, t) << std::endl;
  return 0;
}
