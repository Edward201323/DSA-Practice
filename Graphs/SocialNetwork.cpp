#include "SocialNetwork.hpp"
using namespace std;

SocialNetwork::SocialNetwork(std::initializer_list<std::string> user_list) : 
    users(user_list),
    friendsGraph(user_list.size(), Graph::GType::UNDIRECTED)
{
    for (int i = 0; i < users.size(); i++) {
        userVertex[users[i]] = i;
    }
}

void SocialNetwork::makeFriends(std::string user1, std::string user2) {
    if (userVertex.find(user1) == userVertex.end() || userVertex.find(user2) == userVertex.end()) {
        cerr << "One or both users not found." << endl;
        return;
    }

    int v1 = userVertex[user1];
    int v2 = userVertex[user2];

    if (!friendsGraph.isEdge(v1, v2)) {
        friendsGraph.toggleEdge(v1, v2);
    }
}

void SocialNetwork::removeFriends(std::string user1, std::string user2) {
    if (userVertex.find(user1) == userVertex.end() || userVertex.find(user2) == userVertex.end()) {
        cerr << "One or both users not found." << endl;
        return;
    }

    int v1 = userVertex[user1];
    int v2 = userVertex[user2];

    if (friendsGraph.isEdge(v1, v2)) {
        friendsGraph.toggleEdge(v1, v2);
    }
}

void SocialNetwork::printFriendsList(std::string user) {
    if (userVertex.find(user) == userVertex.end()) {
        cerr << "User not found." << endl;
        return;
    }

    int v = userVertex[user];
    cout << user << "'s friends: ";

    for (int i = 0; i < friendsGraph.numVertices(); ++i) {
        if (friendsGraph.isEdge(v, i)) {
            cout << users[i] << ", ";
        }
    }
    cout << endl;
}