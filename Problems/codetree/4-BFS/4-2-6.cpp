// 상한 귤

/**
 * 숫자 0,1,2로만 이루어진 n x n 격자(0은 아무것도 없음, 1은 귤, 2는 상한귤)
 * 0초에 k개의 상한 귤로부함 시작하여 1초에 한번씩 인접한 곳에 있는 귤이 동시에 전부 상함
 * 각 귤마다 최초로 상하게 되는 시간을 구하라
 * 
 * 입력:
 * 첫번째 줄에 격자의 크기를 나타내는 n과 초기에 상해있는 귤의 수를 나타내는 k가 공백을 사이에 두고 주어짐
 * 두번째 줄부터 n개의 줄에 걸쳐 각 행에 해당하는 n개의 숫자가 순서대로 공백을 사이에 두고 주어짐
 * (2 <= n <= 100, 1 <= k <= n*n)
 * 
 * 출력:
 * n개의 줄에 걸쳐 각 행마다 각 칸의 귤이 상하는 데 까지 걸리는 시간을 공백을 사이에 두고 출력
 * 처음부터 비어있던 칸은 -1, 만약 끝까지 상하지 않는 귤이라면 -2
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, k;
int grid[100][100];
bool visited[100][100];

struct Position {
  int x, y;
};
queue<Position> q;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void bfs() {
  while (!q.empty()) {
    Position cur = q.front();
    q.pop();
    visited[cur.y][cur.x] = true;
    for (int i = 0; i < 4; ++i) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (isInRange(nx, ny) && grid[ny][nx] == -2 && !visited[ny][nx]) {
        visited[ny][nx] = true;
        grid[ny][nx] = grid[cur.y][cur.x] + 1;
        q.push({nx, ny});
      }
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
}

void solution() {
  init();

  cin >> n >> k;
  int num;
  for (int y = 0 ; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> num;
      if (num == 2) {
        grid[y][x] = 0;
        q.push({x, y});
      } else if (num == 1) {
        grid[y][x] = -2;
      } else {
        grid[y][x] = -1;
      }
    }
  }

  bfs();

  for (int y = 0 ; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      int num = grid[y][x];
      cout << num << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("4-2-6.input", "r", stdin);
  freopen("4-2-6.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}