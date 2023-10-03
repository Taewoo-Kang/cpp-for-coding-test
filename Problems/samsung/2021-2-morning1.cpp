// 주사위 굴리기 2
// 삼성 2021년도 하반기 오전 1번
// 출처: https://www.acmicpc.net/problem/23288

#include <iostream>
#include <cstring>
#include <queue>

#define MAX_N 20

using namespace std;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

int N, M, K;
int grid[MAX_N][MAX_N];
int dice[6];

int cx, cy, dir;

bool isInRange(int x, int y) {
  return x >= 0 && x < M && y >= 0 && y < N;
}

void rollDice() {
  int next[6] = {0,};
  switch (dir)
  {
  case 0: {  // 동
    next[0] = dice[0];
    next[1] = dice[5];
    next[2] = dice[1];
    next[3] = dice[2];
    next[4] = dice[4];
    next[5] = dice[3];
    break;
  }
  case 1: {  // 남
    next[0] = dice[5];
    next[1] = dice[1];
    next[2] = dice[0];
    next[3] = dice[3];
    next[4] = dice[2];
    next[5] = dice[4];
    break;
  }
  case 2: {  // 서
    next[0] = dice[0];
    next[1] = dice[2];
    next[2] = dice[3];
    next[3] = dice[5];
    next[4] = dice[4];
    next[5] = dice[1];
    break;
  }
  case 3: {  // 북
    next[0] = dice[2];
    next[1] = dice[1];
    next[2] = dice[4];
    next[3] = dice[3];
    next[4] = dice[5];
    next[5] = dice[0];
    break;
  }
  default:
    break;
  }

  memcpy(dice, next, sizeof(dice));
}

int calcPoint(int x, int y) {
  int num = grid[y][x];
  int cnt = 1;

  bool visited[MAX_N][MAX_N] = {false,};
  queue<pair<int, int>> q;
  q.push({x, y});
  visited[y][x] = true;

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int nx = cur.first + dx[i];
      int ny = cur.second + dy[i];
      if (isInRange(nx, ny) && !visited[ny][nx] && grid[ny][nx] == num) {
        q.push({nx, ny});
        visited[ny][nx] = true;
        ++cnt;
      }
    }
  }
  return num * cnt;
}

int simulation() {
  int nx = cx + dx[dir];
  int ny = cy + dy[dir];
  if (!isInRange(nx, ny)) {
    dir = (dir + 2) % 4;
    nx = cx + dx[dir];
    ny = cy + dy[dir];
  }
  rollDice();
  cx = nx;
  cy = ny;

  int point = calcPoint(nx, ny);

  if (dice[5] > grid[ny][nx]) {
    dir = (dir + 1) % 4;
  } else if (dice[5] < grid[ny][nx]) {
    dir = (dir - 1 + 4) % 4;
  }

  return point;
}

void input() {
  cin >> N >> M >> K;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      cin >> grid[y][x];
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  cx = 0;
  cy = 0;
  dir = 0;
  dice[0] = 2;
  dice[1] = 4;
  dice[2] = 1;
  dice[3] = 3;
  dice[4] = 5;
  dice[5] = 6;
}

void solution() {
  init();
  input();

  int ans = 0;
  while (K--) {
    ans += simulation();
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-2-morning1.input", "r", stdin);
  freopen("2021-2-morning1.output", "w", stdout);
  for (int i = 0; i < 8; ++i) {
    solution();
  }

  return 0;
}