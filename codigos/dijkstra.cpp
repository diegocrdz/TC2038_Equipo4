#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Connection {
private:
    string n1, n2;
    int cost;

public:
    Connection(string n1, string n2, int cost) : n1(n1), n2(n2), cost(cost) {}
    friend class Graph;
};

class Graph {
private:
    vector<Connection> connections;
    map<string, vector<Connection>> list;

public:
    // Method to add connections to the graph
    void addConnection(Connection conn) {
        connections.push_back(conn);
    }

    void buildList() {
        for (int i = 0; i < connections.size(); i++) {
            string node1 = connections[i].n1;
            string node2 = connections[i].n2;
            int cost = connections[i].cost;

            list[node1].push_back(Connection(node1, node2, cost));
            list[node2].push_back(Connection(node2, node1, cost));
        }
    }

    void dijkstra(string start) {

        // Build adjacency list
        buildList();

        // Distance map to store the shortest distance from start to each node
        map<string, int> distances;
        for (int i = 0; i < connections.size(); i++) {
            distances[connections[i].n1] = INT_MAX;
            distances[connections[i].n2] = INT_MAX;
        }
        distances[start] = 0;

        // Priority queue to select the node with the smallest distance
        vector<pair<int, string>> queue;
        queue.push_back({0, start});

        while (!queue.empty()) {
            // Get the node with the smallest distance
            int currentDist = queue.front().first;
            string currentNode = queue.front().second;
            queue.erase(queue.begin());

            // Explore neighbors
            for (int i = 0; i < list[currentNode].size(); i++) {
                string neighbor = list[currentNode][i].n2;
                int newDist = currentDist + list[currentNode][i].cost;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    queue.push_back({newDist, neighbor});
                }
            }
        }

        // Print shortest distances
        cout << "Shortest distances " << start << endl;
        for (const auto& pair : distances) {
            cout << start << "-" << pair.first << " : " << pair.second << endl;
        }
    }
};

int main() {

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
    graph.dijkstra("0");

    return 0;
}