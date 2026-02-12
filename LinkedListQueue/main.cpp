#include <iostream>
#include "LinkedQueue.hpp"

using std::cout;
using std::endl;

int main(){
    LinkedQueue<int> queue;

    queue.enqueue(5);
    queue.enqueue(10);
    queue.enqueue(15);
    queue.enqueue(20);
    queue.enqueue(25);

    LinkedQueue<int> queueCopy(queue);

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    queue = queueCopy;


    cout << queue.front() << " " << queue.back() << endl;
    queue.dequeue();
    cout << queue.front() << " " << queue.back() << endl;
    queue.dequeue();
    cout << queue.front() << " " << queue.back() << endl;
    queue.dequeue();
    cout << queue.front() << " " << queue.back() << endl;
    queue.dequeue();
    cout << queue.front() << " " << queue.back() << endl;
    queue.dequeue();
    cout << queue.isEmpty() << endl;

    cout << endl;

    return 0;
}