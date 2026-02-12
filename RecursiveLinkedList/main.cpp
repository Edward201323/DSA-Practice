#include <iostream>

#include "LinkedListR.hpp"
using namespace std;

int main() {
    LinkedListR<string> myList;
    myList.append("Hello");
    myList.append("World");
    myList.append("???");
    myList.print();

    myList.replace(2, "!!!");
    myList.print();

    myList.insert(0, "H");
    myList.insert(2, "W");
    myList.print();

    cout << myList.getElement(1) <<  myList.getElement(3) << endl;

    myList.remove(0);
    myList.remove(2);
    myList.remove(2);
    myList.print();

    myList.clear();
    myList.print();

    myList.append("Huh.");
    myList.print();

    return 0;
}
