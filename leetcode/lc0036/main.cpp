#include <iostream>
#include <vector>
#include <set>

class Solution {
public:
  static bool isValidSudoku(const std::vector<std::vector<char> >& board) {
    std::set<char> row;
    std::set<char> patch[3];
    std::set<char> column[9];
    for (int i = 0; i != 9; ++i) {
      row.clear();
      if (i % 3 == 0) {
        patch[0].clear();
        patch[1].clear();
        patch[2].clear();
      }
      for (int j = 0; j != 9; ++j) {
        char ch = board[i][j];
        if (ch == '.') continue;
        if (row.find(ch) != row.end()) return false;
        row.insert(ch);
        std::set<char>& p = patch[j / 3];
        if (p.find(ch) != p.end()) return false;
        p.insert(ch);
        if (column[j].find(ch) != column[j].end()) return false;
        column[j].insert(ch);
      }
    }
    return true;
  }
};

int main()
{
  std::vector<std::vector<char> > board {
    { '8', '3', '.', '.', '7', '.', '.', '.', '.' }, 
    { '6', '.', '.', '1', '9', '5', '.', '.', '.' }, 
    { '.', '9', '8', '.', '.', '.', '.', '6', '.' }, 
    { '8', '.', '.', '.', '6', '.', '.', '.', '3' }, 
    { '4', '.', '.', '8', '.', '3', '.', '.', '1' }, 
    { '7', '.', '.', '.', '2', '.', '.', '.', '6' }, 
    { '.', '6', '.', '.', '.', '.', '2', '8', '.' }, 
    { '.', '.', '.', '4', '1', '9', '.', '.', '5' }, 
    { '.', '.', '.', '.', '8', '.', '.', '7', '9' }
  };
  std::cout << Solution::isValidSudoku(board) << std::endl;
  return 0;
}

