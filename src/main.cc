#include "lib/list.h"

int main() {
    list<int> myList;
    myList.push_back(1);
    myList.push_back(2);

    myList.erase(--myList.end());
}

