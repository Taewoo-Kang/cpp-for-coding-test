// 숫자가 가장 큰 인접한 곳으로 동시에 이동
// 분류 - 격자 안에서 여러 객체를 이동

/**
 * 1이상 100이하의 숫자로 이루어진 nxn 크기의 격자판
 * m개 구슬이 서로 다른 위치에서 시작하여 1초에 한 번씩 동시에 이동
 * 상하좌우로 인접한 곳에 있는 숫자들 중 가장 큰 값이 적혀있는 숫자로 이동
 * 만약 그러한 위치가 여러 개 있는 경우 상하좌우 방향 순서대로 우선순위로 이동
 * 하지만 이동한 이후 2개 이상의 구슬 위치가 동일하다면, 해당 위치에 있는 구슬 모두 사라짐
 * t초 후 남아있는 구슬의 수?
 * 
 * 입력:
 * 첫번째 줄에 n, m, t 공백 사이에 두고(2<=n<=20, 1<=m<=n^2, 1<=t<=100)
 * 두번째 줄부터 n개의 줄에 걸쳐 각 행에 해당하는 숫자가 공백을 사이에 두고 주어짐
 * 그 다음 줄부터 m개의 줄에 걸쳐 각 구슬의 시작 위치를 나타내는 r,c값이 공백을 사이에 두고 주어짐
 * 모든 구술의 시작 위치는 다르다고 가정
 * 
 * 출력:
 * t초 이후 격자판에 남아있는 구슬의 수
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m, t, r, c;
int grid[20][20];
int check[20][20];

struct Position {
  int x;
  int y;
};
queue<Position> q;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

bool isInsideGrid(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void move() {
  while (!q.empty()) {
    Position cur = q.front();
    q.pop();
    int max_val = 0;
    int nx = cur.x;
    int ny = cur.y;
    for (int i = 0; i < 4; ++i) {
      int x = cur.x + dx[i];
      int y = cur.y + dy[i];
      if (!isInsideGrid(x, y)) {
        continue;
      }

      if (grid[y][x] > max_val) {
        nx = x;
        ny = y;
        max_val = grid[y][x];
      }
    }
    --check[cur.y][cur.x];
    ++check[ny][nx];
  }

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (check[y][x] > 1) {
        check[y][x] = 0;
      } else if (check[y][x] == 1) {
        q.push({x, y});
      }
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(check, 0, sizeof(check));
  q = queue<Position>();
}

void solution() {
  init();

  cin >> n >> m >> t;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }

  for (int i = 0; i < m; ++i) {
    cin >> r >> c;
    check[r-1][c-1] = 1;
    q.push({c-1, r-1});
  }

  while (t--) {
    move();
  }

  cout << q.size() << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-5-1.input", "r", stdin);
  freopen("1-5-1.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }
  return 0;
}