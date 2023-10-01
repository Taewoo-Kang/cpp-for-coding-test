// 마법사 상어와 파이어스톰
// 삼성 2020년도 하반기 오후 2번
// 출처: https://www.acmicpc.net/problem/20058

/**
 * 2^N x 2^N 크기 격자, A[r][c]는 (r,c)에 있는 얼음의 양
 * L단계마다 2^L x 2^L 크기의 부분격자로 나누고 모든 부분 격자를 시계 방향으로 90도 회전
 * 이후 얼음이 있는 칸 3개 또는 그 이상과 인접(상하좌우)해있지 않은 칸은 얼음의 양이 1 줄어듦
 * 
 * 파이어스톰 총 Q번 시전 후 1. 남아있는 얼음의 합, 2. 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

#define MAX_N 64
#define MAX_Q 1000
#define DIR_NUM 4

using namespace std;

constexpr int dx[DIR_NUM] = {1, 0, -1, 0};
constexpr int dy[DIR_NUM] = {0, -1, 0, 1};

int N, Q;
int grid_size;
int A[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];
int level[MAX_Q];

bool visited[MAX_N][MAX_N];

bool isInRange(int x, int y) {
  return x >= 0 && x < grid_size && y >= 0 && y < grid_size;
}

void rotate(int x, int y, int sub_size) {
  for (int yy = 0; yy < sub_size; ++yy) {
    for (int xx = 0; xx < sub_size; ++xx) {
      temp[xx][sub_size - yy - 1] = A[y + yy][x + xx];
    }
  }
  for (int yy = 0; yy < sub_size; ++yy) {
    for (int xx = 0; xx < sub_size; ++xx) {
      A[y + yy][x + xx] = temp[yy][xx];
    }
  }
}

void rotateGrid(int sub_size) {
  for (int y = 0; y < grid_size; y += sub_size) {
    for (int x = 0; x < grid_size; x += sub_size) {
      rotate(x, y, sub_size);
    }
  }
}

void melt() {
  memcpy(temp, A, sizeof(temp));
  for (int y = 0; y < grid_size; ++y) {
    for (int x = 0; x < grid_size; ++x) {
      if (!A[y][x]) {
        continue;
      }
      int cnt = 0;
      for (int i = 0; i < DIR_NUM; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isInRange(nx, ny) && temp[ny][nx]) {
          ++cnt;
        }
      }
      if (cnt < 3) {
        --A[y][x];
      }
    }
  }
}

void simulate(int cur) {
  rotateGrid(pow(2, level[cur]));
  melt();
}

void input() {
  cin >> N >> Q;
  grid_size = pow(2, N);
  for (int y = 0; y < grid_size; ++y) {
    for (int x = 0; x < grid_size; ++x) {
      cin >> A[y][x];
    }
  }

  for (int i = 0; i < Q; ++i) {
    cin >> level[i];
  }
}

void init() {
  memset(A, 0, sizeof(A));
  memset(temp, 0, sizeof(temp));
  memset(level, 0, sizeof(level));
  memset(visited, 0, sizeof(visited));
}

int bfs(int cx, int cy) {
  queue<pair<int, int>> q;
  q.push({cx, cy});

  int ret = 1;
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    for (int i = 0; i < DIR_NUM; ++i) {
      int nx = cur.first + dx[i];
      int ny = cur.second + dy[i];
      if (isInRange(nx, ny) && A[ny][nx] && !visited[ny][nx]) {
        visited[ny][nx] = true;
        q.push({nx, ny});
        ++ret;
      }
    }
  }

  return ret;
}

#if DEBUG
void _dPrintGrid() {
  for (int y = 0; y < grid_size; ++y) {
    for (int x = 0; x < grid_size; ++x) {
      cout << A[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

void solution() {
  init();
  input();

  for (int i = 0; i < Q; ++i) {
    simulate(i);
#if DEBUG
    _dPrintGrid();
#endif
  }

  int sum = 0;
  int largest = 0;
  for (int y = 0; y < grid_size; ++y) {
    for (int x = 0; x < grid_size; ++x) {
      sum += A[y][x];
      if (A[y][x] && !visited[y][x]) {
        visited[y][x] = true;
        largest = max(largest, bfs(x, y));
      }
    }
  }
  cout << sum << '\n';
  cout << largest << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-2-afternoon2.input", "r", stdin);
  freopen("2020-2-afternoon2.output", "w", stdout);
  for (int i = 0; i < 6; ++i) {
    solution();
  }

  return 0;
}