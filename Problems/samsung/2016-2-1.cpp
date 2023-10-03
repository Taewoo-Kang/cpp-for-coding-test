// 주사위 굴리기
// 삼성 2016년도 하반기 1번
// 출처: https://www.acmicpc.net/problem/14499

#include <iostream>
#include <cstring>

#define MAX_N 20
#define MAX_M 20
#define MAX_K 1000

using namespace std;

constexpr int dx[4] = {1, -1, 0, 0};
constexpr int dy[4] = {0, 0, -1, 1};

int N, M, cx, cy, K;
int grid[MAX_N][MAX_M];
int command[MAX_K];
int dice[6];

bool isInRange(int x, int y) {
  return x >= 0 && x < M && y >= 0 && y < N;
}

void input() {
  cin >> N >> M >> cy >> cx >> K;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      cin >> grid[y][x];
    }
  }

  for (int i = 0; i < K; ++i) {
    cin >> command[i];
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(command, 0, sizeof(command));
  memset(dice, 0, sizeof(dice));
}

void rollDice(int dir) {
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
  case 1: {  // 서
    next[0] = dice[0];
    next[1] = dice[2];
    next[2] = dice[3];
    next[3] = dice[5];
    next[4] = dice[4];
    next[5] = dice[1];
    break;
  }
  case 2: {  // 북
    next[0] = dice[2];
    next[1] = dice[1];
    next[2] = dice[4];
    next[3] = dice[3];
    next[4] = dice[5];
    next[5] = dice[0];
    break;
  }
  case 3: {  // 남
    next[0] = dice[5];
    next[1] = dice[1];
    next[2] = dice[0];
    next[3] = dice[3];
    next[4] = dice[2];
    next[5] = dice[4];
    break;
  }
  default:
    break;
  }

  memcpy(dice, next, sizeof(dice));
}

void solution() {
  init();
  input();

  for (int i = 0; i < K; ++i) {
    int dir = command[i] - 1;
    int nx = cx + dx[dir];
    int ny = cy + dy[dir];
    if (!isInRange(nx, ny)) {
      continue;
    }
    rollDice(dir);
    cx = nx;
    cy = ny;

    cout << cx << ", " << cy << endl;

    if (grid[ny][nx]) {
      dice[5] = grid[ny][nx];
      grid[ny][nx] = 0;
    } else {
      grid[ny][nx] = dice[5];
    }

    cout << dice[2] << '\n';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2016-2-1.input", "r", stdin);
  freopen("2016-2-1.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }

  return 0;
}