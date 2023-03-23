// 우리는 하나

/**
 * n x n 크기의 격자로 이루어져 있는 나라의 정보
 * 각 칸마다 하나의 도시가 있고, 각 도시마다 높이 정보가 주어짐
 * k개의 도시를 겹치지 않게 적절하게 골라 골라진 k개의 도시로부터 갈 수 있는 서로 다른 도시의 수를 최대화
 * 이 때 이동은 상하좌우로 인접한 도시간의 이동만 가능하며, 두 도시간의 높이 차가 u이상 d이하인 경우에만 가능
 * 
 * 입력:
 * 첫번째 줄에 격자의 크기를 나타내는 n과 고를 도시의 수를 나타내는 k, 그리고 u,d 값이 공백을 사이에 두고 주어짐
 * (1 <= n <= 8, 1 <= k <= min(n,3), 0 <= u <= d <= 100)
 * 두번째 줄부터 n개의 줄에 걸쳐 각 행에 해당하는 n개의 숫자가 순서대로 공백을 사이에 두고 주어짐
 * (1 <= 입력으로 주어지는 숫자 <= 100)
 * 
 * 출력:
 * k개의 도시를 적절하게 골라 갈 수 있는 서로 다른 도시의 수 중 최댓값 출력
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

int n, k, u, d;
int grid[100][100];
bool visited[100][100];

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

struct Position {
  int x, y;
};

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

bool canMove(Position cur, Position next) {
  if (!isInRange(next.x, next.y)) {
    return false;
  }
  if (visited[next.y][next.x]) {
    return false;
  }
  if (abs(grid[next.y][next.x] - grid[cur.y][cur.x]) < u
      || abs(grid[next.y][next.x] - grid[cur.y][cur.x]) > d) {
    return false;
  }
  return true;
}

int bfs(int sx, int sy) {
  queue<Position> q;
  Position cur = {sx, sy};
  visited[sy][sx] = true;
  q.push(cur);

  int cnt = 1;
  while (!q.empty()) {
    cur = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (canMove(cur, {nx, ny})) {
        visited[ny][nx] = true;
        q.push({nx, ny});
        ++cnt;
      }
    }
  }

  return cnt;
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
}

void solution() {
  init();

  cin >> n >> k >> u >> d;
  for (int y = 0 ; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }

  priority_queue<int> pq;
  for (int y = 0 ; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (!visited[y][x]) {
        int cnt = bfs(x, y);
        pq.push(cnt);
      }
    }
  }

  int ret = 0;
  for (int i = 0; i < k; ++i) {
    if (pq.empty()) {
      break;
    }
    ret += pq.top();
    pq.pop();
  }
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("4-1-6.input", "r", stdin);
  freopen("4-1-6.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}