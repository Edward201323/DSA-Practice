#include <iostream>
#include "ArrayStack.hpp"

using std::cout;
using std::endl;

int main(){
    ArrayStack<int> nums(2);

    nums.push(5);
    nums.push(10);
    nums.push(15);
    nums.clear();
    nums.push(69);
    nums.pop();
    nums.push(50);
    nums.push(70);
    nums.push(10);

    cout << nums << endl;

    ArrayStack<int> idk(nums);
    nums.push(69);
    idk.push(42);

    cout << idk << endl;
    cout << nums << endl;





    return 0;
}