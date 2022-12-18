// 바이러스
// 출처: https://www.acmicpc.net/problem/2606

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using NodePair = pair<int, int>;
using Graph = vector<vector<int>>;

int bfs(const Graph &graph, int start) {
    vector<int> path;

    bool visited[graph.size()];
    fill_n(visited, graph.size(), false); 
    queue<int> q;

    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        path.push_back(current);
        q.pop();
        for (int node : graph[current]) {
            if (!visited[node]) {
                visited[node] = true;
                q.push(node);
            }
        }
    }


    return path.size() - 1;
}

Graph makeGraph(int vertice, const vector<NodePair> &input) {
    Graph graph(vertice + 1);
    for (NodePair pair : input) {
        graph[pair.first].push_back(pair.second);
        graph[pair.second].push_back(pair.first);
    }

    return graph;
}

void print(int vertice, int edge, const vector<NodePair> &input, int answer) {
    Graph graph = makeGraph(vertice, input);
    int result = bfs(graph, 1);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
        cout << "Result: " << result << ", Answer: " << answer << endl;
    }
}

int main() {
    print(7, 6, {{1, 2}, {2, 3}, {1, 5}, {5, 2}, {5, 6}, {4, 7}}, 4);
    return 0;
}