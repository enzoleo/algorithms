#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <limits>

class BlackBox {
public:  
  // Explicit constructor.
  // Width and height must be specified to correctly instantiate a blackbox
  // object. More specifically, the two arguments should be postive integers.
  explicit BlackBox(unsigned n, unsigned m)
      : w(m), h(n), status(2 * (m + n), false) { }

  // Open the aperture, or activate the function of reflection.
  // Note that the validity of input argument @index will not been checked.
  // The return value is the final index of output aperture.
  unsigned open(int index, int direction) {
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

  // Clear the status cache.
  void clear() {
    std::fill(status.begin(), status.end(), false);
  }

  // Resize the box with a new geometry pair of size.
  // The status will also be resized to a specific size.
  void resize(unsigned n, unsigned m) {
    this->w = m;
    this->h = n;
    this->status.resize(2 * n * m, 0);
  }

  // Read specifications from a given file.
  std::vector<unsigned> parse(const char* filename);

private:
  // Blackbox geometry.
  unsigned w = 0, h = 0;
  std::vector<bool> status;
};

// Parse the external file.
std::vector<unsigned> BlackBox::parse(const char* filename) {  
  // Use C functions to open the text file.
  FILE* fp = std::fopen(filename, "r");
  if(!fp) { // Exit the program if file reading failed/
    std::cerr << "File opening failed.\n";
    exit(EXIT_FAILURE);
  }
  // Parse the actions about to be executed.
  char status[5], delimiter;
  std::vector<bool> action;
  std::fscanf(fp, "[\"BlackBox\" %c", &delimiter);
  while (delimiter == ',') {
    std::fscanf(fp, " \"%[^\"]s", status);
    std::fscanf(fp, "\" %c", &delimiter);
    // Compare the action string with the two allowed options.
    if (std::strcmp(status, "open") == 0) action.emplace_back(true);
    else if (std::strcmp(status, "close") == 0) action.emplace_back(false);
    else { // The action name is invalid.
      std::cerr << "Recognizing action failed.\n";
      exit(EXIT_FAILURE);
    }
  }
  // Parse the index of apertures and corresponding direction of the light.
  unsigned index; int direction, i = 0;
  std::vector<unsigned> res;
  std::fscanf(fp, "\n[[ %u , %u ] %c", &h, &w, &delimiter);
  this->status.resize(2 * h * w);
  while (delimiter == ',') {
    if (action[i++]) {
      // In this case, we are going to open an aperture.
      int ret = std::fscanf(fp, " [ %u , %d ] %c",
                            &index, &direction, &delimiter);
      if (ret != 3) { // Not enough arguments are parsed.
        std::cerr << "Arguments do not match.\n";
        exit(EXIT_FAILURE);
      }
      // Compare the direction string with the two allowed options.
      // Note that we do not check the validity of @index, so make sure that
      // arguments of the input are not out of range.
      if (direction == 1 || direction == -1)
        res.emplace_back(this->open(index, direction));
      else { // The action name is invalid.
        std::cerr << "Recognizing direction failed.\n";
        exit(EXIT_FAILURE);
      }
    } else {
      // In this case, we are goint to close an aperture.
      int ret = std::fscanf(fp, " [ %u ] %c", &index, &delimiter);
      if (ret != 2) { // Not enough arguments are parsed.
        std::cerr << "Arguments do not match.\n";
        exit(EXIT_FAILURE);
      }
      this->close(index);
      res.emplace_back(std::numeric_limits<unsigned>::max());
    }
  }
  std::fclose(fp);
  return std::move(res);
}

int main(int argc, char** argv) {
  // Usage clarification.
  if (argc != 2) {
    const char usage[] = "Usage: \n"
        "    ./reflect testcase.dat\n"
        "Note: the text filename is allowed to be modified.\n"
        "Sample input text file `testcase.dat`: \n"
        "    [\"BlackBox\",\"open\",\"open\",\"open\",\"close\",\"open\"]\n"
        "    [[2,3],[6,-1],[4,-1],[0,-1],[6],[0,-1]]";
    std::cout << usage << std::endl;
    exit(EXIT_FAILURE);
  }
  BlackBox box(1, 1);
  auto res = box.parse(argv[1]);

  // Output the indices we obtain.
  // Note that some action returns no value, so the corresponding return
  // values are replaced with std::numerical_limits<unsigned>::max().
  for (auto index : res)
    std::cout << index << std::endl;
  return 0;
}

