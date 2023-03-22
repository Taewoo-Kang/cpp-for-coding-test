// 두 방향 탈출 가능 여부 판별하기

/**
 * n x m 크기의 2차원 영역의 좌측 상단에서 출발하여 우측 하단까지 뱀에게 물리지 않고 탈출
 * 이동할 때에는 반드시 아래, 오른쪽 두 방향 중 인접한 칸으로만 이동
 * 이 때 뱀에게 물리지 않고 탈출 가능한 경로가 있는지 여부를 판별
 * 
 * 입력: 
 * 첫번째 줄에는 n, m이 공백을 사이에 두고 주어짐
 * 두번째 줄부터 n+1번째 줄까지 각 행에 뱀이 없는 경우 1, 뱀이 있는 경우 0이 공백을 사이에 두고 주어짐
 * 2 <= n,m <= 100
 * 
 * 출력:
 * 좌측 상단에서 출발하여 우측 하단까지 뱀에 물리지 않고 탈출 가능한 경로가 있으면 1, 없으면 0
*/

#include <iostream>
#include <cstring>

using namespace std;

int n, m;
int grid[100][100];
bool visited[100][100];
int ret;

const int dx[] = { 1, 0 };
const int dy[] = { 0, 1 };

bool isInRange(int x, int y) {
  return x >= 0 && x < m && y >= 0 && y < n;
}

void dfs(int sx, int sy) {
  if (sx == m - 1 && sy == n - 1) {
    ret = 1;
    return;
  }

  for (int i = 0; i < 2; ++i) {
    int nx = sx + dx[i];
    int ny = sy + dy[i];
    if (isInRange(nx, ny) && grid[ny][nx] && !visited[ny][nx]) {
      visited[ny][nx] = true;
      dfs(nx, ny);
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
  ret = 0;
}

void solution() {
  init();

  cin >> n >> m;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < m; ++x) {
      cin >> grid[y][x];
    }
  }

  dfs(0, 0);
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("3-1-2.input", "r", stdin);
  freopen("3-1-2.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}