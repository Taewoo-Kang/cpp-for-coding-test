// 마법사 상어와 블리자드
// 삼성 2021년도 상반기 오후 2번
// 출처: https://www.acmicpc.net/problem/21611

/**
 * NxN 크기 격자, N은 항상 홀수, 마법사 상어는 ((N+1)/2, (N+1),2)에 있음
 * 일부 칸과 칸 사이에는 벽이 세워져 있음
 * 
 * 상어가 있는 칸을 제외한 나머지 칸에 구슬(1~3)이 하나 들어갈 수 있음
 * 같은 번호를 가진 구실이 번호가 연속하는 칸에 있으면 연속하는 구슬
 * 
 * 1. 블리자드 마법은 d 방향으로 거리 s 이하인 모든 칸에 얼음 파편을 던져 그 칸에 있는 구슬을 파괴
 * 2. 만약 어떤 칸의 번호보다 하나 작은 칸이 빈 칸이면 구슬은 그 빈 칸으로 이동하며, 더이상 구슬이 이동하지 않을 때까지 반복
 * 3. 4개 이상 연속하는 구슬이 있을 때 구슬 폭발
 * 4. 다시 구슬 이동 후 다시 폭발하면서 더 이상 폭발하는 구슬이 없을 때까지 반복
 * 5. 연속하는 구슬은 하나의 그룹이라고 하고, 하나의 그룹은 두 개의 구슬 A, B로 변함
 * 5-1. A는 그룹에 들어있는 구슬의 개수
 * 5-2. B는 그룹을 이루고 있는 구슬의 번호
 * 5-3. 구슬이 칸의 수보다 많아 칸에 들어가지 못하는 경우 사라짐
 * 
 * 블리자드 M번 시전했을 때 1x(폭발한 1번 구슬의 개수) + 2x(폭발한 2번 구슬의 개수) + 3x(폭발한 3번 구슬의 개수)?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <queue>

#define MAX_N 49
#define MAX_M 100
#define DIR_NUM 4

using namespace std;

constexpr int dx[DIR_NUM] = {0, 1, 0, -1};
constexpr int dy[DIR_NUM] = {1, 0, -1, 0};

int N, M;
int grid[MAX_N][MAX_N];

struct Spell {
  int d, s;
};
Spell command[MAX_M];

int bids[4];

#if DEBUG
void dPrintGrid() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (grid[y][x] >= 0) {
        cout << ' ';
      }
      cout << grid[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

bool isInRange(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

int convDir(int d) {
  if (d == 1) return 2;
  if (d == 2) return 0;
  if (d == 3) return 3;
  if (d == 4) return 1;

#if DEBUG
  cout << "Direction Error!" << endl;
#endif
  return -1;
}

void input() {
  cin >> N >> M;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> grid[y][x];
      if (x == (N-1)/2 && y == (N-1)/2) {
        grid[y][x] = -1;
      }
    }
  }

  for (int i = 0; i < M; ++i) {
    cin >> command[i].d >> command[i].s;
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(command, 0, sizeof(command));
  memset(bids, 0, sizeof(bids));
}

void blizard(int num) {
  Spell spell = command[num];
  int cx = N / 2;
  int cy = N / 2;
  for (int i = 1; i <= spell.s; ++i) {
    int nx = cx + dx[convDir(spell.d)] * i;
    int ny = cy + dy[convDir(spell.d)] * i;
    grid[ny][nx] = 0;
  }
}

void moveBids() {
  bool visited[MAX_N][MAX_N] = {false,};
  int cx = N / 2 - 1;
  int cy = N / 2;

  queue<pair<int, int>> q;
  q.push({cx, cy});
  visited[cy][cx+1] = true;
  visited[cy][cx] = true;

  int dir = 0;
  queue<pair<int, int>> eq;
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    cx = cur.first;
    cy = cur.second;

    if (!grid[cy][cx]) {
      eq.push({cx, cy});
    } else if (!eq.empty()) {
      pair<int, int> pos = eq.front();
      eq.pop();
      grid[pos.second][pos.first] = grid[cy][cx];
      grid[cy][cx] = 0;
      eq.push({cx, cy});
    }

    int nx = cx + dx[dir];
    int ny = cy + dy[dir];
    if (!isInRange(nx, ny)) {
      break;
    }
    q.push({nx, ny});
    visited[ny][nx] = true;

    int nd = (dir + 1) % 4;
    int nrx = nx + dx[nd];
    int nry = ny + dy[nd];
    if (!visited[nry][nrx]) {
      dir = nd;
    }
  }
}

bool explodeBids() {
  bool ret = true;

  bool visited[MAX_N][MAX_N] = {false,};
  int cx = N / 2 - 1;
  int cy = N / 2;

  queue<pair<int, int>> q;
  q.push({cx, cy});
  visited[cy][cx+1] = true;
  visited[cy][cx] = true;

  int dir = 0;
  int num = grid[cy][cx];
  int cnt = 1;
  queue<pair<int, int>> nq;
  nq.push({cx, cy});
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    cx = cur.first;
    cy = cur.second;

    int nx = cx + dx[dir];
    int ny = cy + dy[dir];
    if (!isInRange(nx, ny)) {
      break;
    }
    q.push({nx, ny});
    visited[ny][nx] = true;

    int nd = (dir + 1) % 4;
    int nrx = nx + dx[nd];
    int nry = ny + dy[nd];
    if (!visited[nry][nrx]) {
      dir = nd;
    }

    if (grid[ny][nx] == num) {
      nq.push({nx, ny});
      ++cnt;
    } else {
      if (nq.size() >= 4) {
        ret = false;
        while (!nq.empty()) {
          pair<int, int> cur = nq.front();
          nq.pop();
          grid[cur.second][cur.first] = 0;
          ++bids[num];
        }
      } else {
        while (!nq.empty()) {
          nq.pop();
        }
      }
      nq.push({nx, ny});
      num = grid[ny][nx];
      if (!num) {
        break;
      }
      cnt = 1;
    }
  }

  return ret;
}

void changeBids() {
  bool visited[MAX_N][MAX_N] = {false,};
  int cx = N / 2 - 1;
  int cy = N / 2;

  queue<pair<int, int>> q;
  q.push({cx, cy});
  visited[cy][cx+1] = true;
  visited[cy][cx] = true;

  int dir = 0;
  queue<pair<int, int>> nq;
  queue<pair<int, int>> tq;
  queue<pair<int, int>> cq;
  tq.push({cx, cy});
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    cx = cur.first;
    cy = cur.second;

    int nx = cx + dx[dir];
    int ny = cy + dy[dir];
    if (!isInRange(nx, ny)) {
      break;
    }
    q.push({nx, ny});
    tq.push({nx, ny});
    cq.push({nx, ny});
    visited[ny][nx] = true;

    int nd = (dir + 1) % 4;
    int nrx = nx + dx[nd];
    int nry = ny + dy[nd];
    if (!visited[nry][nrx]) {
      dir = nd;
    }
  }

  int temp[MAX_N][MAX_N] = {0,};
  temp[(N-1)/2][(N-1)/2] = -1;
  int num = grid[(N-1)/2][(N-3)/2];
  int cnt = 1;
  while (!cq.empty()) {
    if (tq.empty()) {
      break;
    }

    int nx = cq.front().first;
    int ny = cq.front().second;
    cq.pop();

    if (grid[ny][nx] == num) {
      nq.push({nx, ny});
      ++cnt;
    } else {
      while (!nq.empty()) {
        nq.pop();
      }
      int xx = tq.front().first;
      int yy = tq.front().second;
      tq.pop();
      temp[yy][xx] = cnt;

      xx = tq.front().first;
      yy = tq.front().second;
      tq.pop();
      temp[yy][xx] = num;

      nq.push({nx, ny});
      num = grid[ny][nx];
      if (!num) {
        break;
      }
      cnt = 1;
    }
  }

  memcpy(grid, temp, sizeof(grid));
}

void simulation(int num) {
#if DEBUG
  cout << "Current:" << endl;
  dPrintGrid();
#endif

  blizard(num);

#if DEBUG
  cout << "After Blizard:" << endl;
  dPrintGrid();
#endif

  bool done = false;
  while (!done) {
    moveBids();
#if DEBUG
  cout << "After Move:" << endl;
  dPrintGrid();
#endif
    done = explodeBids();
#if DEBUG
  cout << "After Explosion:" << endl;
  dPrintGrid();
#endif
  }

  changeBids();
#if DEBUG
  cout << "After Change:" << endl;
  dPrintGrid();
#endif
}

void solution() {
  init();
  input();
  
  for (int i = 0; i < M; ++i) {
    simulation(i);
  }

  int ans = 0;
  for (int i = 1; i <= 3; ++i) {
    ans += i * bids[i];
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-1-afternoon2.input", "r", stdin);
  freopen("2021-1-afternoon2.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }

  return 0;
}