#include <iostream>
#include <fstream>

using namespace std;

void readGraph(const string& filename, int& n, int& m, int**& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    inputFile >> n >> m;

    edges = new int* [m];
    for (int i = 0; i < m; ++i) {
        edges[i] = new int[2];
        inputFile >> edges[i][0] >> edges[i][1];
    }

    inputFile.close();
}

int** createAdjacencyMatrix(int n, int m, int** edges) {
    int** adjacencyMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        adjacencyMatrix[v][u] = 1;
    }

    return adjacencyMatrix;
}

int** createIncidenceMatrix(int n, int m, int** edges) {
    int** incidenceMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        incidenceMatrix[i] = new int[m]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        incidenceMatrix[v][i] = 1;  
        incidenceMatrix[u][i] = -1; 
    }

    return incidenceMatrix;
}

void printMatrix(int** matrix, int rows, int cols, const string& matrixName, const string& outputFile) {
    ofstream outFile(outputFile, ios::app);
    cout << matrixName << ":\n";
    outFile << matrixName << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
            outFile << matrix[i][j] << " ";
        }
        cout << endl;
        outFile << endl;
    }
    cout << endl;
    outFile << endl;
    outFile.close();
}

void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int n, m;
    int** edges = nullptr;
    string inputFile, outputFile;

    cout << "Enter input file: ";
    cin >> inputFile;
    cout << "Enter output file: ";
    cin >> outputFile;

    readGraph(inputFile, n, m, edges);

    int** adjacencyMatrix = createAdjacencyMatrix(n, m, edges);
    int** incidenceMatrix = createIncidenceMatrix(n, m, edges);

    printMatrix(adjacencyMatrix, n, n, "Matrix sumizhnosti", outputFile);
    printMatrix(incidenceMatrix, n, m, "Matrix incydentnosti", outputFile);

    deleteMatrix(adjacencyMatrix, n);
    deleteMatrix(incidenceMatrix, n);

    for (int i = 0; i < m; ++i) {
        delete[] edges[i];
    }
    delete[] edges;

    return 0;
}