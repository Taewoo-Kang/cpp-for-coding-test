// 플로이드
// 출처: https://www.acmicpc.net/problem/11404

#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NODE = 101;
constexpr int INF = 987654321;

int n, m;
int graph[MAX_NODE][MAX_NODE];

void floyd() {
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
    int a, b, c;
    cin >> a >> b >> c;
    if (c < graph[a][b]) {
      graph[a][b] = c;
    }
  }
}

void init() {
  for (int i = 0; i < MAX_NODE; i++) {
    fill_n(graph[i], MAX_NODE, INF);
  }
}

void solution() {
  init();

  makeGraph();

  floyd();

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
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("17-37.input", "r", stdin);

  solution();

  return 0;
}