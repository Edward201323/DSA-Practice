#include <iostream>
#include "ArrayQueue.hpp"
using namespace std;

/**
 * Function prototypes
*/

// A couple auxiliary methods to help run tests
void printHeader(const string &name);
bool passOrFail(bool condition, string message = "");

// The actual tests
bool testEnqueue1();
bool testEnqueue2();
bool testDequeue1();
bool testDequeue2();
bool testDequeue3();
bool testFullAndEmpty();
bool testLooping();
bool testClear1();
bool testClear2();
bool testCopy1();
bool testCopy2();
bool testCopy3();

// run all tests
bool testAll();


/**
 * Main function: run all the tests
 */

int main() {
    ArrayQueue<int> q;
    // bool success = testAll();
    // if (success)
    //     cout << "All tests passed!" << endl;
    // else
    //     cout << "Oh no! A test failed!" << endl;
    // return 0;
}

bool testAll() {
    if (!testEnqueue1()) return false;
    if (!testEnqueue2()) return false;
    if (!testDequeue1()) return false;
    if (!testDequeue2()) return false;
    if (!testDequeue3()) return false;
    if (!testFullAndEmpty()) return false;
    if (!testLooping()) return false;
    if (!testClear1()) return false;
    if (!testClear2()) return false;
    if (!testCopy1()) return false;
    if (!testCopy2()) return false;
    if (!testCopy3()) return false;
    // if we reached this point, everything passed
    return true;
}


/**
 * Auxiliary methods to help run tests at all
 */

void printHeader(const string &name) {
    cout << name << ": running... " << std::flush;
}

// if the given condition is true, print "passed", otherwise "FAILED"
// Further, you can supply an optional message to give more info about failures
// (this is useful if there is more than one place in a test where you might call failure)
bool passOrFail(bool condition, string message) {
    if (condition) {
        cout << "passed" << endl;
    } else {
        cout << "FAILED";
        if (message != "") {
            cout << " (" << message << ")";
        }
        cout << endl;
    }
    return condition;
}


/**
 * Individual tests
 */

// Add one thing to the queue and make sure it looks good so far
bool testEnqueue1() {
    ArrayQueue<char> q(10);
    const char TEST = 'A';
    printHeader("testEnqueue1");
    q.enqueue(TEST);
    return passOrFail(q.getLength() == 1 && q.front() == TEST && q.back() == TEST);
}

// Add three things to the queue and make sure it looks good so far
bool testEnqueue2() {
    ArrayQueue<char> q(10);
    printHeader("testEnqueue2");
    q.enqueue('A');
    q.enqueue('B');
    q.enqueue('C');
    return passOrFail(q.getLength() == 3 && q.front() == 'A' && q.back() == 'C');
}

// Add and remove one thing from a queue and make sure it looks ok
bool testDequeue1() {
    ArrayQueue<char> q(10);
    printHeader("testDequeue1");
    q.enqueue('A');
    // I'm assuming enqueue works correctly so far, here, because we already tested it
    // so we can move on to the other parts of the test
    q.dequeue();
    return passOrFail(q.isEmpty());
}

// Add and then remove many things from a queue and make sure it seems to work
bool testDequeue2() {
    ArrayQueue<int> q(10);
    const int N = 5;
    int arr[N] = {1, 2, 3, 4, 5};
    bool success = true;
    printHeader("testDequeue2");
    for (int i = 0; i < N; i++)
        q.enqueue(arr[i]);
    // make sure those all get dequeued in the correct order
    for (int i = 0; i < N; i++) {
        // if any individual test fails, `success` will become false
        success = success && (q.front() == arr[i]) && (q.getLength() == N - i);
        q.dequeue();
    }
    return passOrFail(success && q.isEmpty());
}

// Dequeue down to 0 elements and ensure it still seems to work
bool testDequeue3() {
    ArrayQueue<char> q(6);
    printHeader("testDequeue3");
    // for variety, we'll begin by getting to a state that looks like [?, B, C, D, ?, ?]
    q.enqueue('A');
    q.enqueue('B');
    q.enqueue('C');
    q.dequeue();
    q.enqueue('D');
    while (!q.isEmpty()) {
        q.dequeue();
    }
    q.enqueue('E');
    q.enqueue('F');
    return passOrFail(q.getLength() == 2 && q.front() == 'E' && q.back() == 'F');
}

// Make sure I get errors when I try to dequeue etc when empty
// and enqueue when full
bool testFullAndEmpty() {
    ArrayQueue<int> q(3);
    printHeader("testFullAndEmpty");

    // On an empty queue, lots of things should throw an exception
    // if they don't, we'll return a failure
    try {
        q.dequeue();
        return passOrFail(false, "1");
    } catch (...) {}
    try {
        q.front();
        return passOrFail(false, "2");
    } catch (...) {}
    try {
        q.back();
        return passOrFail(false, "3");
    } catch (...) {}

    // on a full queue, further enqueue should break
    try {
        // none of these should have an issue
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
    } catch (...) {
        // if they did throw an exception, oh no
        return passOrFail(false, "4");
    }
    // the queue should be full now
    try {
        q.enqueue(4);
        // if we get this far, the class didn't throw an exception when it should have
        return passOrFail(false, "5");
    } catch (...) {}
    
    return passOrFail(true);
}

// make sure the circular behavior seems to work
bool testLooping() {
    ArrayQueue<char> q(3);
    printHeader("testLooping");
    q.enqueue('A');
    q.enqueue('B');
    q.enqueue('C');
    q.dequeue();
    q.dequeue();
    // now the array should look like [?, ?, C] where front and back are both C
    // and the next thing we enqueue should go at index 0
    // If we believe in our other tests, everything up to here should have worked correctly.
    q.enqueue('D');
    q.enqueue('E');
    q.dequeue();
    // we should have looped back around to look like [D, E, ?]
    return passOrFail(q.front() == 'D' && q.back() == 'E' && q.getLength() == 2);
}

// Make sure the queue looks empty after a clear
bool testClear1() {
    ArrayQueue<int> q(10);
    printHeader("testClear1");
    q.enqueue(1);
    q.enqueue(2);
    q.dequeue();
    q.clear();
    return passOrFail(q.getLength() == 0);
}

// Test the circular behavior after a clear
// as a litmus test for whether full functionality seems to be intact
bool testClear2() {
    ArrayQueue<int> q(3);
    printHeader("testClear2");
    q.enqueue(1);
    q.enqueue(2);
    q.dequeue();
    q.clear();
    // can we still use the queue after we've cleared it?
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.dequeue();
    q.enqueue(6);
    return passOrFail(q.getLength() == 3 && q.front() == 4 && q.back() == 6);
}

// Test the copy constructor in a "normal" situation
bool testCopy1() {
    const int N = 3;
    string arr[N] = {"hello", "world", ":)"};
    ArrayQueue<string> source(10);

    printHeader("testCopy1");
    for (int i = 0; i < N; i++)
        source.enqueue(arr[i]);
    // make a copy
    ArrayQueue<string> destination(source);
    // make sure it sort of looks the same
    bool check = destination.getMaxSize() == source.getMaxSize()
            && destination.getLength() == source.getLength()
            && destination.front() == source.front()
            && destination.back() == source.back();
    if (!check) {
        return passOrFail(check, "1");
    }

    // ensure we can modify one without altering the other
    source.clear();
    source.enqueue("garbage");
    for (int i = 0; i < N; i++) {
        if (destination.front() != arr[i])
            return passOrFail(false, "2");
        destination.dequeue();
    }
    return passOrFail(true);
}

// Test the copy constructor when the looping has happened
bool testCopy2() {
    const int N = 4;
    char arr[N] = {'A', 'B', 'C', 'D'};
    ArrayQueue<char> source(6);
    printHeader("testCopy2");

    // get to a state that looks like [C, D, ?, ?, A, B]
    source.enqueue('Z');
    source.enqueue('Z');
    for (int i = 0; i < N; i++)
        source.enqueue(arr[i]);
    source.dequeue();
    source.dequeue();

    // make the copy
    ArrayQueue<char> destination(source);
    // make sure it sort of looks the same
    bool check = destination.getMaxSize() == source.getMaxSize()
            && destination.getLength() == source.getLength()
            && destination.front() == source.front()
            && destination.back() == source.back();
    if (!check)
        return passOrFail(false, "1");

    // actually check that it had all the correct elements
    for (int i = 0; i < N; i++) {
        if (destination.front() != arr[i])
            return passOrFail(false, "2");
        destination.dequeue();
    }
    return passOrFail(true);
}

// lightly test the assignment operator
bool testCopy3() {
    // we'll give them different initial max sizes for fun
    ArrayQueue<int> source(5);
    ArrayQueue<int> destination(1);
    printHeader("testCopy3");
    source.enqueue(1);
    source.enqueue(2);
    destination = source;
    return passOrFail(destination.getLength() == 2 && destination.front() == 1 && destination.back() == 2);
}