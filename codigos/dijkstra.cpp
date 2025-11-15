#include <map>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

// Class to represent a connection between two nodes
class Connection {
private:
    string node1, node2;
    int cost;

public:
    // Default constructor
    Connection() : node1(""), node2(""), cost(0) {}

    // Constructor with parameters
    Connection(string node1, string node2, int cost) {
        this->node1 = node1;
        this->node2 = node2;
        this->cost  = cost;
    }

    // Getters
    string getNode1() { return node1; }
    string getNode2() { return node2; }
    int getCost() { return cost; }
    
    // Print the connection data
    void printData() {
        cout << node1 << " -> " << node2 << " : " << cost << endl;
    }
};

/*
Class to represent a graph
The objective of this class is to implement Dijkstra's algorithm
By being able to represent the nodes by names (strings)
*/ 
class Graph {
private:
    vector<Connection> connections; // List of all connections

    // Adjacency list
    // A map is needed to map node names to their connections
    map<string, vector<Connection>> list;

public:
    // Method to add connections to the graph
    void addConnection(Connection conn) {
        connections.push_back(conn);
    }

    void buildList() {
        for (int i = 0; i < connections.size(); i++) {
            // Get connection details
            string node1 = connections[i].getNode1();
            string node2 = connections[i].getNode2();
            int cost = connections[i].getCost();

            // Add to adjacecncy list
            list[node1].push_back(Connection(node1, node2, cost));
            list[node2].push_back(Connection(node2, node1, cost));
        }
    }

    void dijkstra(string start) {

        // Build adjacency list
        buildList();

        // Distance map to store the shortest distance from start to each node
        map<string, int> distances;

        // Initialize distances to infinity
        for (int i = 0; i < connections.size(); i++) {
            distances[connections[i].getNode1()] = INT_MAX;
            distances[connections[i].getNode2()] = INT_MAX;
        }

        // Distance to the start node is 0
        distances[start] = 0;

        // Priority queue to select the node with the smallest distance
        vector<pair<int, string>> queue; // distance, node
        queue.push_back({0, start}); // Initialize queue with start node

        // While there are nodes to process
        while (!queue.empty()) {
            // Get the node with the smallest distance
            int currentDist = queue.front().first;
            string currentNode = queue.front().second;
            queue.erase(queue.begin());

            // Explore neighbors
            for (int i = 0; i < list[currentNode].size(); i++) {

                // Get neighbor and cost
                string neighbor = list[currentNode][i].getNode2();
                int newDist = currentDist + list[currentNode][i].getCost();
                
                // If new distance is shorter, update and add to queue
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    queue.push_back({newDist, neighbor});
                }
            }
        }

        // Print shortest distances
        // To iterate over the map, we need to use const auto&
        // Which makes a reference to each pair in the distances map
        // Ref: https://en.cppreference.com/w/cpp/container/map.html
        cout << "Shortest distances:" << endl;
        for (const auto& pair : distances) {
            cout << start << " -> " << pair.first << ": " << pair.second << endl;
        }
    }
};

int main() {
    // Create graph and add connections
    Graph graph;
    graph.addConnection(Connection("0", "1", 8));
    graph.addConnection(Connection("0", "2", 12));
    graph.addConnection(Connection("1", "2", 13));
    graph.addConnection(Connection("1", "4", 9));
    graph.addConnection(Connection("1", "3", 25));
    graph.addConnection(Connection("2", "6", 21));
    graph.addConnection(Connection("2", "3", 14));
    graph.addConnection(Connection("4", "3", 20));
    graph.addConnection(Connection("4", "5", 19));
    graph.addConnection(Connection("3", "6", 12));
    graph.addConnection(Connection("3", "8", 16));
    graph.addConnection(Connection("3", "7", 12));
    graph.addConnection(Connection("3", "5", 8));
    graph.addConnection(Connection("4", "5", 19));
    graph.addConnection(Connection("5", "7", 11));
    graph.addConnection(Connection("6", "8", 11));
    graph.addConnection(Connection("7", "8", 9));

    // Dijkstra
    graph.dijkstra("0");

    return 0;
}