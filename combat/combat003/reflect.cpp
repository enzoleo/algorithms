#include <iostream>
#include <vector>

class BlackBox {
public:  
  // Explicit constructor.
  // The width and height must be specified to correctly instantiate a blackbox
  // object. More specifically, the two arguments should be postive integers.
  explicit BlackBox(unsigned n, unsigned m)
      : w(m), h(n), status(2 * (m + n), false) { }

  // Open the aperture, or activate the function of reflection.
  // Note that the validity of input argument @index will not been checked.
  // The return value is the final index of output aperture.
  int open(int index, int direction) {
    this->status[index] = true;
    do {
      // Find the next point on the border.
      index = this->next(index, direction);

      // Reflected by the corner points.
      if (index == 0 || index == w + h) direction = -1;
      else if (index == w || index == 2 * w + h) direction = 1;
      else direction = -direction;
    } while (!status[index]);
    return index;
  }

  // Close the aperture, or deactivate the function of reflection.
  // Note that we do not check the validity of input argument.
  void close(unsigned index) {
    this->status[index] = false;
  }

  // Find the next point on the border the light will meet.
  unsigned next(unsigned index, int direction) const {
    // Light comes out along direction of y = -x.
    if (direction < 0) {
      if (index > 2 * w) return 4 * w + 2 * h - index;
      else return 2 * w - index;
    }
    // Light comes out along direction of y = x.
    if (index == 0) return 0;
    return 2 * w + 2 * h - index;    
  }

private:
  // Blackbox geometry.
  unsigned w = 0, h = 0;
  std::vector<bool> status;
};

int main() {
  BlackBox box(2, 3);
  std::cout << box.open(6, -1) << std::endl;
  std::cout << box.open(4, -1) << std::endl;
  std::cout << box.open(0, -1) << std::endl;
  box.close(6);
  std::cout << box.open(0, -1) << std::endl;
  return 0;
}

