#include "GraphMatrix.hpp"
#include "interactive.hpp"
#include "SocialNetwork.hpp"
#include <iostream>
using namespace std;

void pretendSN();

int main() {
    int choice;
    do {
        cout << "1 - Run interactive graph tests" << endl;
        cout << "2 - Run the pretend social network" << endl;
        cout << "Choose 1 or 2: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    switch (choice) {
    case 1:
        interactiveTester();
        break;
    case 2:
        pretendSN();
        break;
    }

    return 0;
}

void pretendSN() {
    const string ALICE = "Alice";
    const string BOB = "Bob";
    const string EVE = "Eve";
    const string MALLORY = "Mallory";
    const string TRENT = "Trent";
    const string names[5] = {ALICE, BOB, EVE, MALLORY, TRENT};
    SocialNetwork network({ALICE, BOB, EVE, MALLORY, TRENT});

    // To start off with, we have two groups of friends
    network.makeFriends(ALICE, BOB);
    network.makeFriends(BOB, EVE);
    network.makeFriends(EVE, ALICE);
    network.makeFriends(MALLORY, TRENT);

    cout << "Initial:" << endl;
    for (const string &name : names) {
        network.printFriendsList(name);
    }

    // Then, Alice meets Mallory, and they become best friends
    network.makeFriends(ALICE, MALLORY);

    // But drama ensues: Mallory convinces Alice and Bob that Eve shares too many memes
    network.makeFriends(BOB, MALLORY);
    network.removeFriends(ALICE, EVE);
    network.removeFriends(BOB, EVE);

    // Trent hears about this but thinks the memes are really funny, so he reaches out
    network.makeFriends(TRENT, EVE);
    // also, he decides MALLORY is kind of mean and only ever friended her because they had homeroom together in high school
    network.removeFriends(TRENT, MALLORY);

    cout << endl << "Final:" << endl;
    for (const string &name : names) {
        network.printFriendsList(name);
    }
}