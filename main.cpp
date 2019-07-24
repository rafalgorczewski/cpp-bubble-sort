#include <iostream>
#include <iterator>
#include <vector>

#include "bubble_sort.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  using std::begin, std::end;

  std::vector<int> foo = { 2, 1, 3, 7 };
  hqrp::bubble_sort(begin(foo), end(foo));
  
  for (auto x : foo) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}
