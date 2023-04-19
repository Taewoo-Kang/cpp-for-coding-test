// 최소 비용 구하기
// 출처: https://www.acmicpc.net/problem/1916

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constexpr int MAX_NODE = 1001;
constexpr int INF = 987654321;

int N, M;
vector<pair<int, int>> graph[MAX_NODE];
int dist[MAX_NODE];

void dijkstra(int start) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  pq.push({0, start});
  dist[start] = 0;
  while (!pq.empty()) {
    int cur = pq.top().second;
    int d = pq.top().first;
    pq.pop();

    if (dist[cur] < d) {
      continue;
    }

    for (int i = 0; i < graph[cur].size(); i++) {
      pair<int, int> target = graph[cur][i];
      int cost = d + target.second;
      if (cost < dist[target.first]) {
        dist[target.first] = cost;
        pq.push({cost, target.first});
      }
    }
  }
}

void makeGraph() {
  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
  }
}

void init() {
  for (int i = 0; i < MAX_NODE; i++) {
    graph[i].clear();
  }
  fill_n(dist, MAX_NODE, INF);
}

void solution() {
  init();

  cin >> N >> M;
  makeGraph();

  int start, end;
  cin >> start >> end;
  dijkstra(start);

  cout << dist[end];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("boj_1916.input", "r", stdin);
  freopen("boj_1916.output", "w", stdout);

  for (int i = 0; i < 1; i++) {
    solution();
  }

  return 0;
}