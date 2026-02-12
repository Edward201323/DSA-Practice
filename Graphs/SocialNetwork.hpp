#pragma once

#include "GraphMatrix.hpp"
#include <initializer_list>
#include <map>
#include <string>
#include <vector>

class SocialNetwork {
private:
    // A list of the users of our social network
    std::vector<std::string> users;

    // A graph:
    // Each vertex i corresponds to users[i], in the vector above, and
    // an edge between two users indicates those two users are friends
    GraphMatrix friendsGraph;

    // A Dictionary that lets us go from the name of a user
    // to their index in the users vector, or equivalently,
    // to their vertex number in the graph
    std::map<std::string, int> userVertex;

public:
    // Constructor, which takes a list of the usernames as an argument
    SocialNetwork(std::initializer_list<std::string> users);

    // Update the friend graph to make the two given users friends.
    // If they are already friends, do nothing.
    void makeFriends(std::string user1, std::string user2);

    // Update the friend graph so that the two given users are not friends.
    // If they were not friends to begin with, do nothing.
    void removeFriends(std::string user1, std::string user2);

    // cout each of the friends of the given user in a single line
    void printFriendsList(std::string user);
};