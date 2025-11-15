
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <limits>

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

// Class to represent a graph
class Graph {
private:
    vector <Connection> connections; // Connections in the graph
    vector <string> nodes; // Stores all existing nodes once
    vector <Connection> T; // Edges in the minimum spanning tree
    int V; // Number of vertices
    int mstCost; // Cost of the minimum spanning tree

public:
    // Default constructor
    Graph() {
        connections = vector<Connection>();
        nodes = vector<string>();
        V = 0;
        mstCost = 0;
    }

    // Add a connection to the graph
    void addConnection(string node1, string node2, int cost) {
        // Create a new connection with the data
        Connection connection(node1, node2, cost);
        connections.push_back(connection);

        // Check if the nodes already exist, if not, add them to nodes
        if (!nodeExists(node1)) nodes.push_back(node1);
        if (!nodeExists(node2)) nodes.push_back(node2);

        // Update the number of vertices
        V = nodes.size();
    }

    // Check if a node already exists in the graph
    bool nodeExists(string node) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == node) return true;
        }
        return false;
    }

    // Print all the connections of the graph
    void printConnections() {
        cout << "Connections:" << endl;
        for (int i = 0; i < connections.size(); i++) {
            connections[i].printData();
        }
    }

    // Primm algorithm to find the minimum spanning tree
    void primm(int first) {
        // If there are no nodes, return
        if (nodes.empty()) return;

        // Vector to mark visited nodes
        vector<bool> visited(V, false);
        int totalCost = 0; // Total cost of MST
        int edgesUsed = 0; // Counter for v-1 edges

        // Start from the first node
        visited[first] = true;

        // Repeat until we have V-1 edges in the MST
        while (edgesUsed < V - 1) {
            int minCost = INT_MAX; // Minimum cost found in this iteration
            int idx = -1; // Index of the chosen connection
            string actualNode;
            string nextNode;

            // For each connection, look for the minimum cost edge that connects a visited node to an unvisited node
            for (int i = 0; i < connections.size(); i++) {

                // Get connection data
                string n1 = connections[i].getNode1();
                string n2 = connections[i].getNode2();
                int cost = connections[i].getCost();
                int idx1 = getNodeIndex(n1);
                int idx2 = getNodeIndex(n2);

                // Check if the edge connects a visited node to an unvisited node
                if ((visited[idx1] && !visited[idx2]) || (visited[idx2] && !visited[idx1])) {
                    // If the cost is lower than the current minimum, update
                    if (cost < minCost) {
                        minCost = cost;
                        idx = i;

                        // If the first node is visited, go from n1 to n2
                        if (visited[idx1]) {
                            actualNode = n1;
                            nextNode = n2;
                        } else {
                            // Else go from n2 to n1
                            actualNode = n2;
                            nextNode = n1;
                        }
                    }
                }
            }

            // If a valid edge was found, add it to the MST
            if (idx != -1) {
                T.push_back(connections[idx]); // Add edge to MST
                totalCost += minCost; // Add cost
                visited[getNodeIndex(nextNode)] = true; // Mark the new node as visited
                edgesUsed++; // Increase edge count
            } else break; // If no edge was found, finish
        }
        // Update the total cost of the MST
        mstCost = totalCost;
    }

    int getNodeIndex(string node) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == node) return i;
        }
        return -1;
    }

    void printMST() {
        cout << "Edges in Minimum Spanning Tree (Prim): " << endl;
        for (int i = 0; i < T.size(); i++) {
            T[i].printData();
        }
        cout << "Total cost: " << mstCost << endl;
    }
};

int main() {
    // Create graph
    Graph graph;
    graph.addConnection("A", "B", 2);
    graph.addConnection("A", "C", 4);
    graph.addConnection("B", "C", 3);
    graph.addConnection("A", "D", 6);
    graph.addConnection("D", "C", 1);
    graph.addConnection("C", "E", 5);
    graph.addConnection("D", "E", 4);
    graph.addConnection("D", "F", 3);
    graph.addConnection("F", "G", 5);
    graph.addConnection("E", "G", 2);

    // Primm
    graph.primm(0);
    graph.printMST();

    return 0;
}