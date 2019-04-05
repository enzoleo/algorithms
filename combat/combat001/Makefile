CXX := g++
CXXFLAGS := -g -fPIC -std=c++11 -O3 -Wall -DNDEBUG

# Modify the number if you want. This number is the upper bound of elements
# in the input array, and more importantly this number determines the size
# of array we use in the algorithm.
CXXFLAGS += -DMAX_NUMBER=100000

# Comment this line to use map in the algorithm.
CXXFLAGS += -DUSE_ARRAY

# Modify this line for random array generating with different size. Note if
# the macro USE_INPUT is defined at the same time, the user will be required
# to input @ARRAY_SIZE numbers without inputting the array size first.
CXXFLAGS += -DARRAY_SIZE=100000

# Uncomment this line to compare the result to the brute-force method.
# CXXFLAGS += -DUSE_BASELINE

# Uncomment this line to load array from user-input. If @ARRAY_SIZE is not
# defined, the user should input the array size first.
# CXXFLAGS += -DUSE_INPUT

exec := run
SRC := $(wildcard *.cpp)

all:$(exec)

$(exec):$(SRC)
	@ $(CXX) -o $@ $^ $(CXXFLAGS);

clean:
	@ rm -rf $(exec);

