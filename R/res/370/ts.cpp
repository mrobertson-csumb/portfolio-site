/*
 * Title: ts.cpp
 * Abstract: an implementation of the topological sorting algorithm
 * based on the source-removal algorithm
 *     the program:
 *         reads a user-input filename
 *         determines the best assignment arrangement
 *         display topological ordering of a directed acyclic graph
 *         (in asc order)
 *
 * Author: Matthew Robertson
 * ID: 1618
 * Date: 02/11/2020
 */

#include <iostream>
#include <fstream>


using namespace std; // bad practice, but requested

class Graph {
private:
    int **_matrix;
    int _node_count;
    int *_in_degrees;
    bool *_is_visited;

    void init(int **matrix, int node_count) {
        this->_matrix = matrix;
        this->_node_count = node_count;
        this->_in_degrees = new int[node_count];
        this->_is_visited = new bool[node_count];

        for (int i = 0; i < node_count; i++) {
            _is_visited[i] = false;
            _in_degrees[i] = 0;
        }

        for (int r = 0; r < node_count; r++) {
            for (int c = 0; c < node_count; c++) {
                _in_degrees[c] += _matrix[r][c];
            }
        }

    }

public:
    Graph(const string &filename) {
        int node_count;
        int **matrix;
        ifstream file;
        file.open(filename);

        if (file.is_open()) {
            file >> node_count;

            matrix = new int *[node_count];
            for (int i = 0; i < node_count; ++i) {
                matrix[i] = new int[node_count];
            }

            int r = 0, c = 0; // init row & column indices
            // printf("nodes: %d\n", node_count);
            while (!file.eof()) {
                int item;
                file >> item;
                matrix[r][c] = item;

                // printf("[%d][%d]: %d, ", r, c, item);
                c++;
                if (c == node_count) {
                    c = 0;
                    r++;
                }
            }
            file.close();
        } else {
            cerr << "Could not open: " << filename;
            exit(1);
        }

        init(matrix, node_count);
    }

    void print_matrix() {
        printf("\n");
        for (int c = 0; c < _node_count; c++) {
            if (c == 0) {
                printf(" ");

            }
            printf(" %d", c);
        }
        printf("\n");
        for (int r = 0; r < _node_count; r++) {
            printf("%d|", r);
            for (int c = 0; c < _node_count; c++) {
                if (c != 0) {
                    printf(" ");
                }
                printf("%d", _matrix[r][c]);
                if (c == _node_count - 1) {
                    printf("\n");
                }
            }
        }
    }

    void print_in_degrees() {
        for (int i = 0; i < _node_count; i++) {
            printf("id[%d]: %d\n", i, _in_degrees[i]);
        }
    }

    void print_sorted_by_topology() {
        bool is_first = true;
        int visit_count = 0;
        while (visit_count < _node_count) {
            for (int source = 0; source < _node_count; source++) {
                for (int to_n = 0; to_n < _node_count; to_n++) {

                    // if no incoming edges and not visited yet
                    if (_in_degrees[source] == 0 && !_is_visited[source]) {
                        visit_count++;

                        // record the visit
                        _is_visited[source] = true;
                        if (is_first) {
                            printf("Topological sort: %d", source);
                            is_first = false;
                        } else {
                            printf(" -> %d", source);
                        }

                        // remove the source node
                        for (int edge = 0; edge < _node_count; edge++) {
                            auto before = _matrix[source][edge];
                            if (_matrix[source][edge] != 0) {
                                _matrix[source][edge] = 0;
                                _in_degrees[edge] -= 1;
                            }
                        }
                        // print_matrix();
                        // print_in_degrees();
                        break;
                    }
                }
            }
        }
    }
};


int main() {
    string file_name;
    cout << "Enter filename: ";
    cin >> file_name;
    // auto file_name = "../t4.txt";
    auto g = new Graph(file_name);
    // g->print_matrix();
    // g->print_in_degrees();
    g->print_sorted_by_topology();

    printf("\n");

    return 0;
}
