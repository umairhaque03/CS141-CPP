/**------------------------------------------
  Program 6: Graphs
  Course: CS 141, Spring 2023
  System: macOs Ventura 13.0.1
  Author: Umair Haque, starter code provided by George Maratos and David Hayes
---------------------------------------------**/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Struct to represent node in the graph
struct Node {
    int id;
    Node* next;
};

//Will take in an input file to read from and an output file to write the statistics in
void run(const string& src_path, const string& dst_path)
{

    // Input file for reading, output file for writing
    ofstream output(dst_path);
    ifstream input(src_path);

    // Creates a vector to hold the head of each node in the graph
    vector<Node*> nodeHeads;

    // Will read each line of input file to create an adjacency list
    string line;
    while (getline(input, line)) {
        int src;
        int destination;
        stringstream s(line);
        s >> src >> destination;

        // Resizing the vectors to account for new nodes
        if (src >= nodeHeads.size()) {
            nodeHeads.resize(src + 1, nullptr);
        }

        if (destination >= nodeHeads.size()) {
            nodeHeads.resize(destination + 1, nullptr);
        }

        // Will check if the edge exists in the graph
        bool existsEdge = false;
        Node* currentNode = nodeHeads[src];
        while (currentNode != nullptr) {
            if (currentNode->id == destination) {
                existsEdge = true;
                break;
            }
            currentNode = currentNode->next;
        }

        // If the edge doesn't exist, add it to the graph
        if (existsEdge == false) {
            Node* newNode = new Node{ destination, nodeHeads[src] };
            nodeHeads[src] = newNode;
            newNode = new Node{ src, nodeHeads[destination] };
            nodeHeads[destination] = newNode;
        }
    }

    // Make variables that will hold the statistics of the graph
    int max_degree = 0;
    int num_edges = 0;
    int num_nodes = 0;

    // Output the adjacency list and calculate the graph statistics
    for (int i = 0; i < nodeHeads.size(); i++) {
        int degrees = 0;
        Node* currentNode = nodeHeads[i];
        vector<int> neighbor;
        while (currentNode != nullptr) {
            neighbor.push_back(currentNode->id);
            currentNode = currentNode->next;
            degrees++;
        }
        if (degrees > max_degree) {
            max_degree = degrees;
        }

        if (degrees > 0) {
            num_edges += degrees;
            sort(neighbor.begin(), neighbor.end());
            output << i << ": ";

            for (int j = 0; j < neighbor.size(); j++) {

                output << neighbor[j];

                if (j != neighbor.size() - 1) {
                    output << " ";
                }
            }
            output << endl;
        }
    }

    // Calculate the amount of nodes in the graph
    for (Node* node : nodeHeads) {
        if (node != nullptr) {
            num_nodes++;
        }
    }

    // Calculate the number of edges in the graph (divide by 2 to count each edge
    // only once)
    num_edges /= 2;

    output.close();

    // Output information to console
    cout << "Number of nodes: " << num_nodes << endl;
    cout << "Number of edges: " << num_edges << endl;
    cout << "Maximum degree: " << max_degree << endl;
}

// Running and testing program
int main()
{
    string src_file = "roadNet-CA.txt";
    string dst_file = "roadnetlist.txt";
    run(src_file, dst_file);
    return 0;
}