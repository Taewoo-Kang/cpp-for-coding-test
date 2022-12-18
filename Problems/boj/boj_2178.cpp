// 미로 탐색
// 출처: https://www.acmicpc.net/problem/2178

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

using Graph = vector<vector<int>>;

int bfs(const Graph &graph, int start) {
    int depth = 1;
    int end = graph.size() - 1;

    bool visited[graph.size()];
    fill_n(visited, graph.size(), false); 
    queue<pair<int, int>> q;

    visited[start] = true;
    q.push(make_pair(start, depth));
    while (q.front().first != end) {
        pair<int, int> current = q.front();
        q.pop();
        for (int node : graph[current.first]) {
            if (!visited[node]) {
                visited[node] = true;
                q.push(make_pair(node, current.second + 1));
            }
        }
    }

    return q.front().second;
}

Graph makeGraph(const vector<string> &input) {
    int N = input.size();
    int M = input[0].size();
    Graph graph(N * M);
    for (int i = 0; i < N; i++) {
        string row = input[i];
        for (int j = 0; j < M - 1; j++) {
            if (row[j] == '1' && row[j + 1] == '1') {
                int src = M * i + j;
                int dst = M * i + (j + 1);
                graph[src].push_back(dst);
                graph[dst].push_back(src);
            }
        }
    }

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < M; j++) {
            if (input[i][j] == '1' && input[i + 1][j] == '1') {
                int src = M * i + j;
                int dst = M * (i + 1) + j;
                graph[src].push_back(dst);
                graph[dst].push_back(src);
            }
        }
    }

    return graph;
}

int solution(const vector<string> &input) {
    int ret = 0;
    Graph graph = makeGraph(input);
    ret = bfs(graph, 0);

    return ret;
}

void print(vector<string> input, int answer) {
    int result = solution(input);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
        cout << "Result: " << result << ", Answer: " << answer << endl;
    }
}
 
int main() {
    print({"101111",
           "101010",
           "101011",
           "111011"}, 15);
    print({"110110",
           "110110",
           "111111",
           "111101"}, 9);
    print({"1011101110111011101110111",
           "1110111011101110111011101"}, 38);
    print({"1011111",
           "1110001",
           "1000001",
           "1000001",
           "1000001",
           "1000001",
           "1111111"}, 13);
    return 0;
}