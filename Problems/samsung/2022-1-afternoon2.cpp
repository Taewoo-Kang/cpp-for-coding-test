// 나무박멸
// 삼성 2022년도 하반기 오후 2번
// 출처: https://www.codetree.ai/training-field/frequent-problems/problems/tree-kill-all?&utm_source=clipboard&utm_medium=text

/**
 * n x n 격자에 나무 그루 수와 벽의 정보, 제초제를 뿌려 나무의 성장 억제
 * 제초제는 k 범위만큼 대각선으로 퍼지고 벽이 있는 경우 전파 X
 * 
 * 1. 인접한 네 칸 중 나무가 있는 칸의 수만큼 나무가 성장(모든 나무가 동시에 일어남)
 * 2. 기존에 있던 나무들은 인접한 4개 칸 중 벽, 다른 나무, 제초제가 없는 칸에 번식 진행
 * 2-1. 각 칸의 (나무 그루 수) / (번식 가능한 칸의 개수) 만큼 번식(나머지는 버리며 동시에 일어남)
 * 3. 각 칸 중 제초제를 뿌렸을 때 나무가 가장 많이 박멸되는 칸에 제초제 뿌림
 * 3-1. 제초제가 뿌려진 칸에는 c년만큼 제초제가 남아있게 됨
 * 3-2. 이미 제초제가 뿌려진 칸에 제초제가 다시 뿌려지면 새로 뿌려진 것 기준으로 다시 c년동안 유지
 * 3-3. 만약 박멸시키는 나무의 수가 동일한 칸이 여러 개면, 행/열 순서로 작은 칸에
 * 
 * m년 동안 총 박멸한 나무의 그루 수?
*/

#define DEBUG 1

#include <iostream>
#include <cstring>

#define MAX_N 20

using namespace std;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, -1, 0, 1};
constexpr int dkx[4] = {1, 1, -1, -1};
constexpr int dky[4] = {1, -1, -1, 1};

int n, m, k, c;
int grid[MAX_N][MAX_N];
int herbicide[MAX_N][MAX_N];

#if DEBUG
void dPrintGrid() {
  cout << "Grid:" << endl;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cout << grid[y][x] << ' ';
    }
    cout << endl;
  }
  cout << "Herbicide:" << endl;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cout << herbicide[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void growupTree() {
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (grid[y][x] <= 0) {
        continue;
      }
      int cnt = 0;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isInRange(nx, ny) && grid[ny][nx] > 0) {
          ++cnt;
        }
      }
      grid[y][x] += cnt;
    }
  }
}

void breedTree() {
  int temp[MAX_N][MAX_N] = {0,};
  memcpy(temp, grid, sizeof(temp));

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (temp[y][x] <= 0) {
        continue;
      }
      int cnt = 0;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isInRange(nx, ny) && !herbicide[ny][nx] && !temp[ny][nx]) {
          ++cnt;
        }
      }
      if (!cnt) {
        continue;
      }
      int num = temp[y][x] / cnt;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isInRange(nx, ny) && !herbicide[ny][nx] && !temp[ny][nx]) {
          grid[ny][nx] += num;
        }
      }
    }
  }
}

int killTree() {
  int max_kill = -1;
  pair<int, int> max_pos = {-1, -1};

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (grid[y][x] <= 0) {
        continue;
      }
      int kill = grid[y][x];
      pair<int, int> pos = {x, y};
      for (int i = 0; i < 4; ++i) {
        for (int d = 1; d <= k; ++d) {
          int nx = x + dkx[i] * d;
          int ny = y + dky[i] * d;
          if (!isInRange(nx, ny) || grid[ny][nx] <= 0) {
            break;
          }
          kill += grid[ny][nx];
        }
      }

      if (kill > max_kill) {
        max_kill = kill;
        max_pos = pos;
      }
    }
  }

  if (!isInRange(max_pos.first, max_pos.second)) {
#if DEBUG
    cout << "Something Wrong!" << endl;
#endif
    return 0;
  }

  if (grid[max_pos.second][max_pos.first] > 0) {
    grid[max_pos.second][max_pos.first] = 0;
    herbicide[max_pos.second][max_pos.first] = c;
    for (int i = 0; i < 4; ++i) {
      for (int d = 1; d <= k; ++d) {
        int nx = max_pos.first + dkx[i] * d;
        int ny = max_pos.second + dky[i] * d;
        if (!isInRange(nx, ny) || grid[ny][nx] < 0) {
          break;
        }
        if (!grid[ny][nx]) {
          herbicide[ny][nx] = c;
          break;
        }
        grid[ny][nx] = 0;
        herbicide[ny][nx] = c;
      }
    }
  }

  return max_kill;
}

int simulation() {
  growupTree();
  breedTree();
#if DEBUG
  cout << "After breed:" << endl;
  dPrintGrid();
#endif

  for (int y = 0; y < n; ++y) {
    for (int x= 0; x < n; ++x) {
      if (herbicide[y][x]) {
        --herbicide[y][x];
      }
    }
  }
  int kill = killTree();
  return kill;
}

void input() {
  cin >> n >> m >> k >> c;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(herbicide, 0, sizeof(herbicide));
}

void solution() {
  init();
  input();

  int ans = 0;
  while (m--) {
    ans += simulation();
#if DEBUG
    dPrintGrid();
    cout << ans << endl;
#endif
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2022-1-afternoon2.input", "r", stdin);
  freopen("2022-1-afternoon2.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}