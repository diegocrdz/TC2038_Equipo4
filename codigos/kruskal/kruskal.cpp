#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

/*
Kruskal Algorithm in C++
Team:
- Aquiba Yudah Benarroch Bittán, A01783710
- Diego Córdova Rodríguez, A01781166
- Lorena Estefanía Chewtat Torres, A01785378
*/

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

// Class to detect cycles and connect nodes
class CycleDetector {
private:
    // Every node has a parent and rank
    map <string, string> parent;
    map <string, int> rank;
    
public:
    // Default contructor
    CycleDetector() {
        parent = map <string, string>();
        rank = map <string, int>();
    }

    // Contructor with parameters
    CycleDetector(vector <string> nodes) { // nodes in the graph
        // Set the initial size of the vectors to match n nodes
        int n = nodes.size();

        // Initially, every node is its own parent and has a rank of 1
        for (int i=0; i<n; i++) {
            parent[nodes[i]] = nodes[i];
            rank[nodes[i]] = 1;
        }
    }

    // Find the parent of a node
    string getParent(string n) {
        // If the node is its own parent, return it
        if (parent[n] == n) {
            return n;
        // Else, search the parent recursively
        } else {
            parent[n] = getParent(parent[n]);
            return parent[n];
        }
    }
    
    // Connect 2 nodes
    void connect(string n1, string n2) {
        // Find the parents of each node
        string p1 = getParent(n1);
        string p2 = getParent(n2);

        // If the parents are different, the nodes can be connected
        if(p1 != p2){
            // Compare ranks to assign a new common parent
            // If a node's rank is bigger, he becomes the parent of the other
            if(rank[p1] < rank[p2]) { // Parent 1 is bigger
                parent[p1] = p2;
                rank[p1]++;
            } else if(rank[p1] > rank[p2]) { // Parent 2 is bigger
                parent[p2] = p1;
                rank[p2]++;
            } else {
                // If both ranks are equal, assign one as parent and increase its rank
                parent[p2] = parent[p1];
                rank[p1]++;
            }
        }
    }
};

// Class to represent a graph
class Graph {

private:
    vector <Connection> connections; // Connections in the graph
    vector <string> nodes; // Stores all existing nodes once

    vector <Connection> aux; // Auxiliary vector for merge sort

    vector <Connection> T; // Edges in the minimum spanning tree
    int V; // Number of vertices
    int mstCost; // Cost of the minimum spanning tree

    bool ordered; // Flag to know if the graph has been ordered

public:
    // Default constructor
    Graph() {
        connections = vector <Connection>();
        aux = vector <Connection>();
        nodes = vector <string>();
        V = nodes.size();
        mstCost = 0;
        ordered = false;

    }

    // Getters
    int getVertices() { return V; }

    // Read a txt file and store the connections
    void readTxt(string filename) {
        // Create a file and read the txt
        ifstream file(filename);

        // Variables to read the data in the file
        string node1, node2;
        int cost;

        // Read the file line by line
        while (file >> node1 >> node2 >> cost) { 
            // Create a new connection with the data from the file
            Connection connection(node1, node2, cost);
            connections.push_back(connection);

            // Check if the nodes already exist, if not, add them to nodes
            if (nodeExists(node1) == false) nodes.push_back(node1);
            if (nodeExists(node2) == false) nodes.push_back(node2);
        }
        file.close();

        // Update the number of vertices
        V = nodes.size();
    }

    // Check if a node exists in the graph
    bool nodeExists(string node) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == node) {
                return true;
            }
        }
        return false;
    }

    // Merge the halves for the array
    void merge(int lo, int mid, int hi) {
        // Copy the elements from the original to the auxiliary array
        aux = connections;

        // Indexes for the array
        int i=lo, j=mid+1, k=lo;
        
        while (i<=mid && j<=hi) {
            if (aux[i].getCost() <= aux[j].getCost()) {
                connections[k] = aux[i];
                i++;
            }
            else {
                connections[k] = aux[j];
                j++;
            }
            k++;
        }

        // Merge the rest of the elements

        while (i<=mid) { // Left
            connections[k] = aux[i];
            i++;
            k++;
        }

        while (j<=hi) { // Right
            connections[k] = aux[j];
            j++;
            k++;
        }
    }

    // Divide the array into halves
    void sort(int lo, int hi) {
        if (hi <= lo) return;

        // Get the mid index of the array
        int mid = (lo + hi) / 2;

        // Sort left and right halves
        sort(lo, mid);
        sort(mid+1, hi);

        // Merge the halves
        merge(lo, mid, hi);
    }

    // Wrapper function for merge sort
    void mergeSort() {
        // If the graph is already ordered, skip sorting
        if (ordered) return;
        sort(0, connections.size()-1);
        ordered = true;
    }

    // Print all the connections of the graph
    void printConnections() {
        cout << "Connections:" << endl;
        for (int i = 0; i < connections.size(); i++) {
            connections[i].printData();
        }
    }

    // Kruskal's algorithm to find the minimum spanning tree
    void kruskal() {
        // Sort edges by cost
        mergeSort();

        // Check if a cycle is created
        CycleDetector cd(nodes);
        int totalCost = 0;
        int count = 0; // Counter for v-1 edges
        
        // For each connection
        for (int i=0; i<connections.size(); i++) {
            // Get the data from the connection
            string n1 = connections[i].getNode1();
            string n2 = connections[i].getNode2();
            int cost = connections[i].getCost();
            
            // If the nodes have different parents, they can be connected
            if (cd.getParent(n1) != cd.getParent(n2)) {
                if (count == V-1) break;
                else {
                    // Make a new connection
                    cd.connect(n1, n2);
                    totalCost += cost; 
                    count++;
                    // Store the connection in the mst
                    T.push_back(connections[i]);
                }
            }
        }
        mstCost = totalCost;
    }

    void printMST() {
        cout << "Edges in Minimum Spanning Tree: " << endl;
        for (int i=0; i < T.size(); i++) {
            T[i].printData();
        }
        cout << "Total cost: " << mstCost << endl;
    }
};

int main() {
    Graph graph;
    graph.readTxt("prueba.txt");
    graph.printConnections();
    graph.mergeSort();
    cout << "**Connections sorted with merge sort**" << endl;
    graph.printConnections();
    graph.kruskal();
    graph.printMST();

    return 0;
}