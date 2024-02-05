#include "lib/list.h"
#include <iostream>
int main() {
  list<int> myList = {3, 1, 4, 3, 2};

  //  std::vector<int> expected = {1, 2, 3, 3, 4};
 std::cout << "{3, 1, 4, 3, 2}" << std::endl;

  std::cout << *--myList.end() << std::endl;
  std::cout << *myList.begin() << std::endl;

  myList.sort();
  int i = 0;
  for (const auto &elem : myList) {
    std::cout << elem << " ";
  }
}
