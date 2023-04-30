// 플로이드-워셜

#include <iostream>

using namespace std;

constexpr int MAX_NODE = 501;
constexpr int INF = 987654321;

int n, m;
int graph[MAX_NODE][MAX_NODE];

void floydWarshall() {
  for (int k = 1; k <= n; k++) {
    for (int a = 1; a <= n; a++) {
      for (int b = 1; b <= n; b++) {
        graph[a][b] = min(graph[a][b], graph[a][k] + graph[k][b]);
      }
    }
  }
}

void makeGraph() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <=n; j++) {
      if (i == j) {
        graph[i][j] = 0;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    int s, e, c;
    cin >> s >> e >> c;
    graph[s][e] = c;
  }
}

void init() {
  for (int i = 0; i < MAX_NODE; i++) {
    fill_n(graph[i], MAX_NODE, INF);
  }
}

int main() {
  freopen("9-2.input", "r", stdin);

  init();

  makeGraph();

  floydWarshall();

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <=n; j++) {
      if (graph[i][j] == INF) {
        cout << "INFINITY" << ' ';
      } else {
        cout << graph[i][j] << ' ';
      }
    }
    cout << '\n';
  }

  return 0;
}