#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
using namespace std;
vector<vector<int>> convertMatrixToList(const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Can not open the input file.";
        return {};
    }
    string line;
    int n;
    ifs >> n;
    int a[1000][1000];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ifs >> a[i][j];
        }
    }
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    ifs.close();
    return adjList;
}

vector<vector<int>> convertListToMatrix (const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Can not open the input file.";
        return {};
    }
    vector<vector<int>> adjList;
    int n;
    ifs >> n;
    for (int i = 0; i < n; i++) {
        string line;
        getline(ifs, line);
        istringstream iss (line);
        int token;
        vector<int> currentLine;
        while (iss >> token) {
            currentLine.push_back(token);
        }
        adjList.push_back(currentLine);
    }
    vector<vector<int>> adjMatrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (find(adjList.begin(), adjList.end(), j) == adjList.end()) {
                adjMatrix[i][j] = 0;
            } else {
                adjMatrix[i][j] = 1;
            }
        }
    }
    ifs.close();
    return adjMatrix;
}
bool isDirected(const vector<vector<int>> &adjMatrix) {
    int size = adjMatrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                return true;
            }
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>> &adjMatrix) {
    int size = adjMatrix.size();
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjMatrix[i][j] == 1) {
                count++;
            }
        }
    }
    if (!isDirected(adjMatrix)) {
        count /= 2;
    }
    return count;
}

vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix) {
    vector<int> ans;
    int size = adjMatrix.size();
    for (int i = 0; i < size; i++) {
        bool hasEdgeOut = find(adjMatrix[i].begin(), adjMatrix[i].end(), 1) != adjMatrix[i].end();
        bool hasEdgeIn = false;
        for (int j = 0; j < size; j++) {
            if (adjMatrix[j][i] == 1) {
                hasEdgeIn = true;
                break;
            }
        }
        if (!hasEdgeOut && !hasEdgeIn) {
            ans.push_back(i);
        }
    }
    return ans;
}

bool isCompleteGraph(const vector<vector<int>> &adjMatrix) {
    int size = adjMatrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == j && adjMatrix[i][j] != 0) || (i != j && adjMatrix[i][j] != 1)) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite (const std:: vector<std:: vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color (n, -1);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] == 1) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite (const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color (n, -1);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] == 1) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    vector<int> color0;
    vector<int>color1;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            color0.push_back(i);
        } else {
            color1.push_back(i);
        }
    }
    for (int i: color0) {
        for (int j: color1) {
            if (adjMatrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph (const vector<vector<int>> &adjMatrix) {
    int size = adjMatrix.size();
    vector<vector<int>> ans = adjMatrix;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjMatrix[i][j] == 1) {
                ans[j][i] = 1;
            }
        }
    }
    return ans;
}

vector<vector<int>> getComplementGraph (const vector<vector<int>> &adjMatrix) {
    int size = adjMatrix.size();
    vector<vector<int>> ans(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j && adjMatrix[i][j] == 0) {
                ans[i][j] = 1;
            } else {
                ans[i][j] = 0;
            }
        }
    }
    return ans;
}

void countInOutDegrees(const vector<vector<int>>& adjMatrix, vector<pair<int, int>> &inOutDegrees) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] == 1) {
                inOutDegrees[i].second++; // out-degree
                inOutDegrees[j].first++;  // in-degree
            }
        }
    }
}

bool graphHasEulerianPath(const vector<vector<int>>& adjMatrix, const vector<pair<int, int>>& inOutDegrees) {
    int startNodes = 0, endNodes = 0;
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        int diff = inOutDegrees[i].first - inOutDegrees[i].second;
        if (diff < -1 || diff > 1) {
            return false;
        }
        else if (diff == 1) {
            startNodes++;
        }
        else if (diff == -1) {
            endNodes++;
        }
    }
    return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
}

int findStartNode(const vector<vector<int>>& adjMatrix, const vector<pair<int, int>>& inOutDegrees) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        if (inOutDegrees[i].first - inOutDegrees[i].second == 1) {
            return i; // start node has in-degree = out-degree + 1
        }
    }
    for (int i = 0; i < n; i++) {
        if (inOutDegrees[i].second > 0) {
            return i; // fallback: any node with outgoing edges
        }
    }
    return 0;
}

void dfs(int at, vector<pair<int, int>> &inOutDegrees, vector<int>& path, vector<vector<int>> &copy) {
    int n = copy.size();
    for (int i = 0; i < n; i++) {
        while (copy[at][i] > 0) {
            copy[at][i]--;
            inOutDegrees[at].second--;
            inOutDegrees[i].first--;
            dfs(i, inOutDegrees, path, copy);
        }
    }
    path.push_back(at);
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            edgeCount += adjMatrix[i][j];
        }
    }
    vector<pair<int,int>> inOutDegrees(n, {0, 0});
    countInOutDegrees(adjMatrix, inOutDegrees);
    if (!graphHasEulerianPath(adjMatrix, inOutDegrees)) {
        return {};
    }
    vector<vector<int>> copy = adjMatrix;
    vector<int> path;
    dfs(findStartNode(adjMatrix, inOutDegrees), inOutDegrees, path, copy);
    if ((int)path.size() == edgeCount + 1) {
        reverse(path.begin(), path.end());
        return path;
    }
    return {};
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    stack<int> st;
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> ans(n, vector<int>(n, 0));
    st.push(start);
    visited[start] = true;
    while (!st.empty()) {
        int i = st.top();
        st.pop();
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] == 1 && !visited[j]) {
                st.push(j);
                visited[j] = true;
                ans[i][j] = 1;
                ans[j][i] = 1;
            }
        }
    }
    return ans;
}

vector<vector<int>> bfsSpanningTree (const vector<vector<int>> &adjMatrix, int start) {
    queue<int> q;
    int n = adjMatrix.size();
    vector<bool> visited (n, false);
    vector<vector<int>> ans (n, vector<int> (n, 0));
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] == 1 && !visited[j]) {
                q.push(j);
                visited[j] = true;
                ans[i][j] = 1;
                ans[j][i] = 1;
            }
        }
    }
    return ans;
}

bool has_path(int start, int end, const vector<vector<int>> &adjMatrix, vector<bool> &visited) {
    if (start == end) {
        return true;
    }
    int n = adjMatrix.size();
    visited[start] = true;
    for (int i = 0; i < n; i++) {
        if (adjMatrix[start][i] == 1 && visited[i] == false) {
            bool result = has_path(i, end, adjMatrix, visited);
            if (result) {
                return true;
            }
        }
    }
    return false;
}

bool isConnected(int u, int v, const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited (n, false);
    return has_path(u, v, adjMatrix, visited);
}

vector<int> dijkstra(int start, int end, const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<int> parent(n, -1);
    vector<int> path;
    vector<bool> visited(n, false);
    vector<int> distance(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    distance[start] = 0;
    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();
        if (visited[node]) continue;
        visited[node] = true;
        for (int j = 0; j < n; j++) {
            if (adjMatrix[node][j] != 0 && !visited[j]) {
                int weight = adjMatrix[node][j];
                if (distance[j] > distance[node] + weight) {
                    distance[j] = distance[node] + weight;
                    parent[j] = node;
                    pq.push({distance[j], j});
                }
            }
        }
    }
    if (distance[end] == INT_MAX) {
        return path;
    }
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> distance(n, INT_MAX);
    vector<int> parent(n, -1);
    distance[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (adjMatrix[j][k] != 0 && distance[j] != INT_MAX && distance[j] + adjMatrix[j][k] < distance[k]) {
                    distance[k] = distance[j] + adjMatrix[j][k];
                    parent[k] = j;
                }
            }
        }
    }
    // Check negative cycle
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != 0 && distance[i] != INT_MAX && distance[i] + adjMatrix[i][j] < distance[j]) {
                return {};  // Negative cycle detected
            }
        }
    }
    if (distance[end] == INT_MAX) {
        return {};  // No path
    }
    vector<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
