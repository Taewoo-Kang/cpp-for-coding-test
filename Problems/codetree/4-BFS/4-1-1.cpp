// 네 방향 탈출 가능 여부 판별하기

/**
 * n x m 크기의 2차원 영역의 좌측 상단에서 출발하여 우측 하단까지 뱀에 물리지 않고 탈출
 * 이동은 반드시 상하좌우에 인접한 칸으로만 가능
 * 이 때 뱀에게 물리지 않고 탈출 가능한 경로가 있는지 여부를 판별
 * 
 * 입력:
 * 첫번째 줄에는 n과 m이 공백을 사이에 두고 주어짐 (2 <= n,m <= 100)
 * 두번째 줄부터 n+1번째 줄까지 각 행에 뱀이 없는 경우 1, 있는 경우 0이 입력으로 공백을 사이에 두고 주어짐
 * 
 * 출력:
 * 좌측 상단에서 출발하여 우측 하단까지 뱀에게 물리지 않고 탈출 가능한 경로가 있으면 1, 없으면 0을 출력
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
int grid[100][100];
bool visited[100][100];

struct Position {
  int x;
  int y;
};

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

bool isInRange(int x, int y) {
  return x >= 0 && x < m && y >= 0 && y < n;
}

int bfs() {
  queue<Position> q;
  Position cur = {0, 0};
  q.push(cur);
  while (!q.empty()) {
    cur = q.front();
    q.pop();
    if (cur.x == m - 1 && cur.y == n - 1) {
      return 1;
    }

    for (int i = 0; i < 4; ++i) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (isInRange(nx, ny) && grid[ny][nx] == 1 && !visited[ny][nx]) {
        visited[ny][nx] = true;
        ++grid[ny][nx];
        q.push({nx, ny});
      }
    }
  }

  return 0;
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
}

void solution() {
  init();
  
  cin >> n >> m;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < m; ++x) {
      cin >> grid[y][x];
    }
  }

  int ret = bfs();
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("4-1-1.input", "r", stdin);
  freopen("4-1-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}