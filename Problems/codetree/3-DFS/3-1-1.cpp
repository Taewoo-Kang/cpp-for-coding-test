// 그래프 탐색

/**
 * N개의 정점과 M개의 간선으로 이루어진 양방향 그래프
 * 1번 정점에서 시작하여 주어진 간선을 따라 이동했을 때 도달할 수 있는 서로 다른 정점의 수?
 * 
 * 입력:
 * 첫번째 줄에는 N과 M이 공백을 사이에 두고 주어짐
 * 두번째 줄부터 M개의 줄에 걸쳐 연결된 두 정점 (x,y)가 공백을 사이에 두고 주어짐
 * (1 <= x,y <= N, 1 <= N <= 1,000, 0 <= M <= min(10,000, N(N-1)/2))
 * 
 * 출력:
 * 1번 정점에서 시작하여 주어진 간선을 따라 이동했을 때 도달할 수 있는 서로 다른 정점의 수
*/

#include <iostream>
#include <cstring>
#include <set>

using namespace std;

int N, M;
int graph[1001][1001];
int visited[1001][1001];
set<int> s;

void dfs(int cur) {
  for (int i = 1; i <= N; ++i) {
    if (graph[cur][i] && !visited[cur][i]) {
      visited[cur][i] = 1;
      s.insert(i);
      dfs(i);
    }
  }
}

void init() {
  memset(graph, 0, sizeof(graph));
  memset(visited, 0, sizeof(visited));
  s = set<int>();
}

void solution() {
  init();

  cin >> N >> M;

  int x, y;
  for (int i = 0; i < M; ++i) {
    cin >> x >> y;
    graph[y][x] = 1;
    graph[x][y] = 1;
  }

  dfs(1);
  int ret = s.empty() ? 0 : s.size() - 1;
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("3-1-1.input", "r", stdin);
  freopen("3-1-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}