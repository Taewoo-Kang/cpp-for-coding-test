// 뿌요뿌요

/**
 * n x n 크기의 격자에 1이상 100이하의 숫자가 각 칸에 하나씩 주어짐
 * 상하좌우로 인접한 칸끼리 같은 숫자로 이루어져 있는 경우 하나의 블럭으로 생각하며,
 * 블럭을 이루고 있는 칸의 수가 4개 이상일 경우 해당 블럭은 터지게 됨
 * 초기 상태가 주어졌을 때 터지게 되는 블럭의 수와 최대 블럭의 크기?
 * 
 * 입력:
 * 첫번째 줄에는 격자의 크기를 나타내는 n이 주어짐 (1 <= n <= 100)
 * 두번째 줄부터는 n개의 줄에 걸쳐 각 행에 해당하는 n개의 숫자가 순서대로 공백을 사이에 두고 주어짐
 * 1 <= 주어지는 숫자 <= 100
 * 
 * 출력:
 * 터지게 되는 블럭의 수와 최대 블럭의 크기를 공백을 사이에 두고 출력
*/

#include <iostream>
#include <cstring>

using namespace std;

int n;
int grid[100][100];
bool visited[100][100];
int max_val;
int cnt;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void dfs(int sx, int sy) {
  visited[sy][sx] = true;
  ++cnt;
  for (int i = 0; i < 4; ++i) {
    int nx = sx + dx[i];
    int ny = sy + dy[i];
    if (isInRange(nx, ny) && grid[ny][nx] == grid[sy][sx] && !visited[ny][nx]) {
      dfs(nx, ny);
    }
  }

}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
  max_val = 0;
  cnt = 0;
}

void solution() {
  init();

  cin >> n;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }

  int block = 0;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (!visited[y][x]) {
        dfs(x, y);
        if (cnt > max_val) {
          max_val = cnt;
        }
        if (cnt >= 4) {
          ++block;
        }
        cnt = 0;
      }
    }
  }
  cout << block << ' ' << max_val << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("3-1-5.input", "r", stdin);
  freopen("3-1-5.output", "w", stdout);
  for (int i = 0; i < 5; ++i) {
    solution();
  }

  return 0;
}