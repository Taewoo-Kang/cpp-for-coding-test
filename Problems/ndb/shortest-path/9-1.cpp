// 다익스트라 알고리즘

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr int MAX_NODE = 100001;

int n, m, start;

struct EdgePair {
  int dest;
  int cost;
};
vector<EdgePair> graph[MAX_NODE];
int dist[MAX_NODE];

void dijkstra() {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  pq.push({0, start});
  dist[start] = 0;
  while (!pq.empty()) {
    int d = pq.top().first;
    int cur = pq.top().second;
    pq.pop();

    if (dist[cur] < d) {
      continue;
    }

    for (int i = 0; i < graph[cur].size(); i++) {
      EdgePair target = graph[cur][i];
      int cost = d + target.cost;
      if (cost < dist[target.dest]) {
        dist[target.dest] = cost;
        pq.push({cost, target.dest});
      }
    }
  }
}

int main() {
  freopen("9-1.input", "r", stdin);

  cin >> n >> m >> start;
  
  for (int i = 0; i < m; i++) {
    int s, e, c;
    cin >> s >> e >> c;
    graph[s].push_back({e, c});
  }

  fill_n(dist, MAX_NODE, INT_MAX);

  dijkstra();

  for (int i = 1; i <= n; i++) {
    if (dist[i] == INT_MAX) {
      cout << "INFINITY" << '\n';
    } else {
      cout << dist[i] << '\n';
    }
  }
  return 0;
}