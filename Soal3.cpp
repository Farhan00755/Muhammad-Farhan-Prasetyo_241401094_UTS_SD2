#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

class Graph {
private: 
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) {
        numVertices = V;
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    vector<string> lokasi = {
        "Warung Kopi Pak Harry",
        "Kedai Coding IKLC",
        "Caffe Alya",
        "Studio Fasilkom-TI",
        "Wi-Fi Gratis Sejagat"
    };

    vector<char> huruf = {
        'A',
        'B',
        'C',
        'D',
        'E',
    };

    void addEdge(int i, int j, int w) {
        i--;
        j--;
        if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
            adjMatrix[i][j] = w;
            adjMatrix[j][i] = w; 
        } else {
            cout << "Indeks simpul tidak valid." << endl;
        }
    }

    // ----- BAGIAN DFS -----
    void dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        cout << "PENJELAJAHAN PARUL (DFS dari "<< huruf[startVertex] << " ) :\n";

        dfsUtil(startVertex, visited);

        cout << endl;
    }

    void dfsUtil(int currentVertex, vector<bool>& visited) {
        visited[currentVertex] = true;

        cout << huruf[currentVertex];
        
        for (int i = numVertices - 1; i >= 0; i--) {
            if (adjMatrix[currentVertex][i] != 0 && !visited[i]) {
                cout << " -> ";
                dfsUtil(i, visited);
            }
        }
    }
    
    // ----- BAGIAN BFS -----
    void bfs(int startVertex, int endVertex) {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        // BFS standar
        while (!q.empty()) {
            int current = q.front(); q.pop();
            vector<pair<int,int>> neighbors; 
            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[current][i] != 0 && !visited[i]) {
                    neighbors.push_back({adjMatrix[current][i], i});
                }
            }
            sort(neighbors.begin(), neighbors.end()); 
            for (auto &p : neighbors) {
                int i = p.second;
                if (!visited[i]) {
                    visited[i] = true;
                    parent[i] = current;
                    q.push(i);
                    if (i == endVertex) break;
                }
            }
        }

        // Rekonstruksi jalur
        vector<int> path;
        for (int v = endVertex; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        // Cetak hasil
        cout << "JALUR TERCEPAT PARUL (BFS):\n";
        int totalJarak = 0;
        for (size_t i = 0; i < path.size(); i++) {
            cout << lokasi[path[i]] << " (" << huruf[path[i]] << ")\n";
            if (i < path.size() - 1) {
                int w = adjMatrix[path[i]][path[i+1]];
                cout << w << "m\n";
                totalJarak += w;
            }
        }

        cout << "\nJalur terpendek: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << huruf[path[i]];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal langkah: " << path.size() - 1 << " edge";
        cout << "\nTotal jarak: " << totalJarak << " meter\n";
    }
};

int main() {
    system("cls");
    Graph g(5);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 5);

    g.dfs(0); // Mulai DFS dari vertex 1 (indeks 0)
    cout << endl;
    g.bfs(0,4); // Mulai BFS dari vertex 1 (indeks 0) ke vertex 5 (E)

    return 0;
}