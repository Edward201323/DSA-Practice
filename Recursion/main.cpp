#include <cstring>
#include <iostream>
#include "part-a.hpp"
#include "part-b.hpp"
using namespace std;

/**
 * Figure out whether we should run Part A or Part B.
 * If they specified something from the command line, use that;
 * Otherwise, prompt them for a choice via stdin (cin).
 * 
 * Input:
 * The system "argc" and "argv" variables that specify command line input
 * 
 * Output:
 * A character: lowercase 'a' or 'b'
 */
char getMode(int argc, char *argv[]);

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    // find out whether we should run Part A or Part B
    char mode = getMode(argc, argv);

    // call the appropriate function
    switch (mode) {
    case 'a':
        Part_A();
        break;
    case 'b':
        Part_B();
        break;
    }

    // terminate
    return 0;
}

char getMode(int argc, char *argv[]) {
    char mode = ' '; // space will indicate no assigned value yet

    // if they passed exactly one argument to the command line,
    // we'll try to parse that into 'a' or 'b'
    // (if it's neither of those, we'll leave mode == ' ')
    if (argc == 2) {
        // see if it's an 'a' or 'b' (and allow uppercase)
        if (strcmp(argv[1], "a") == 0 || strcmp(argv[1], "A") == 0) {
            mode = 'a';
        } else if (strcmp(argv[1], "b") == 0 || strcmp(argv[1], "B") == 0) {
            mode = 'b';
        }
    }

    // if they passed something via the command line,
    // but we didn't succesfully get a mode from it,
    // we'll give them a warning
    if (argc >= 2 && mode == ' ') {
        cout << "Invalid command-line argument(s)" << endl;
    }

    // resort to asking for 'a' or 'b' via the command line, if necessary
    if (mode == ' ') {
        do {
            cout << "Select \'a\' or \'b\': ";
            cin >> mode;
            
            // if they entered uppercase, we'll convert for them
            switch (mode) {
            case 'A':
                mode = 'a';
                break;
            case 'B':
                mode = 'b';
                break;
            }
        } while (!(mode == 'a' || mode == 'b'));
    }

    return mode;
}