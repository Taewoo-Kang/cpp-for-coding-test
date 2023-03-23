// 최소 경로로 탈출하기

/**
 * n x m 크기의 2차원 영역의 좌측 상단에서 출발하여 우측 하단까지 뱀에게 물리지 않고 탈출
 * 이동은 반드시 상하좌우에 인접한 칸으로만 할 때 탈출 가능한 경로의 최단거리
 * 
 * 입력:
 * 첫번째 줄에 n과 m이 공백을 사이에 두고 주어짐 (2 <= n,m <= 100)
 * 두번째 줄부터 n+1번째 줄까지 각 행에 뱀이 없는 경우 1, 있는 경우 0이 입력으로 공백을 사이에 두고 주어짐
 * 
 * 출력:
 * 좌측 상단에서 출발하여 우측 하단까지 이동 가능한 경로 중 최단거리 출력
 * 불가능한 경우 -1을 출력
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
int grid[100][100];
bool visited[100][100];

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

struct Position {
  int x, y;
};

bool isInRange(int x, int y) {
  return x >= 0 && x < m && y >= 0 && y < n;
}

bool canMove(int x, int y) {
  if (!isInRange(x, y)) {
    return false;
  }
  if (visited[y][x] || !grid[y][x]) {
    return false;
  }
  return true;
}

int bfs() {
  queue<Position> q;
  Position cur = {0, 0};
  visited[0][0] = true;
  q.push(cur);

  while (!q.empty()) {
    cur = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (canMove(nx, ny)) {
        grid[ny][nx] = grid[cur.y][cur.x] + 1;
        if (nx == m-1 && ny == n-1) {
          return grid[n-1][m-1] - 1;
        }
        visited[ny][nx] = true;
        q.push({nx, ny});
      }
    }
  }

  return -1;
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
}

void solution() {
  init();

  cin >> n >> m;
  for (int y = 0 ; y < n; ++y) {
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

  freopen("4-2-1.input", "r", stdin);
  freopen("4-2-1.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}