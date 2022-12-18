// BFS와 DFS
// 출처: https://www.acmicpc.net/problem/1260

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

using NodePair = pair<int, int>;
using Graph = vector<vector<int>>;

bool visited[1001]; // Initialized zero for global variable

// Recursion version
// void dfs_internal(const Graph &graph, int current, vector<int> &result) {
//     visited[current] = true;
//     result.push_back(current);
//     for (int node : graph[current]) {
//         if (!visited[node]) {
//             dfs_internal(graph, node, result);
//         }
//     }
// }

// vector<int> dfs(const Graph &graph, int start) {
//     vector<int> ret;
//     dfs_internal(graph, start, ret);

//     return ret;
// }

// Stack version
vector<int> dfs(const Graph &graph, int start) {
    vector<int> ret;
    stack<int> s;

    ret.push_back(start);
    visited[start] = true;
    s.push(start);
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        for (int node : graph[current]) {
            if (!visited[node]) {
                ret.push_back(node);
                visited[node] = true;
                s.push(current);
                s.push(node);
                break;
            }
        }
    }

    return ret;
}

vector<int> bfs(const Graph &graph, int start) {
    vector<int> ret;
    queue<int> q;

    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        ret.push_back(current);
        q.pop();
        for (int node : graph[current]) {
            if (!visited[node]) {
                visited[node] = true;
                q.push(node);
            }
        }
    }


    return ret;
}

Graph makeGraph(int vertice, const vector<NodePair> &input) {
    Graph graph(vertice + 1);
    for (NodePair pair : input) {
        graph[pair.first].push_back(pair.second);
        graph[pair.second].push_back(pair.first);
    }

    for (vector<int> &node : graph) {
        sort(node.begin(), node.end());
    }
    return graph;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &vec) {
    os << "{";
    for (int i = 0; i < vec.size(); i++) {
        const T &elem = vec[i];
        if (i == vec.size() - 1) {
            os << elem;
        } else {
            os << elem << ", ";
        }
    }
    os << "}";
    return os;
}
 
void print(int vertice, int edge, int start, const vector<NodePair> &input,
           const pair<vector<int>, vector<int>> &answer) {
    Graph graph = makeGraph(vertice, input);
    fill_n(visited, 1001, false); 
    vector<int> dfs_ret = dfs(graph, start);
    fill_n(visited, 1001, false); 
    vector<int> bfs_ret = bfs(graph, start);

    pair<vector<int>, vector<int>> result = make_pair(dfs_ret, bfs_ret);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
        cout << "Result: " << result.first << ", " << result.second << endl;
        cout << "Answer: " << answer.first << ", " << answer.second << endl;
    }
}

int main() {
    print(4, 5, 1, {{1, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}},
          {{1, 2, 4, 3}, {1, 2, 3, 4}});
    print(5, 5, 3, {{5, 4}, {5, 2}, {1, 2}, {3, 4}, {3, 1}},
          {{3, 1, 2, 5, 4}, {3, 1, 4, 2, 5}});
    print(1000, 1, 1000, {{999, 1000}}, {{1000, 999}, {1000, 999}});
    print(10, 10, 4, {{5, 4}, {6, 4}, {6, 8}, {8, 9}, {1, 10}, {2, 10}, {10, 3}, {8, 2}, {1, 7}, {4, 10}}, 
          {{4, 5, 6, 8, 2, 10, 1, 7, 3, 9}, {4, 5, 6, 10, 8, 1, 2, 3, 9, 7}});
    return 0;
}