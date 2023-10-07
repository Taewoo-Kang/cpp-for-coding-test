// 술래잡기
// 삼성 2022 상반기 오전 1번
// 출처: https://www.codetree.ai/training-field/frequent-problems/problems/hide-and-seek?&utm_source=clipboard&utm_medium=text

/**
 * n x n 격자, 술래는 정중앙에 시작
 * m명의 도망자, 상하or좌우로만 움직이는 유형, 좌우는 오른쪽 보고 시작, 상하는 아래쪽 보고 시작
 * h개 나무, 초기에 도망자와 겹쳐져 주어지는 것 가능
 * 술래잡기는 m명의 도망자가 먼저 동시에 움직이고 그 다음 술래가 움직이는 식으로 k번 반복
 * 
 * 술래와 거리가 3이하 도망자만 움직임(거리 = |x1-x2| + |y1-y2|)
 * 1. 도망자 움직임
 * 1-1. 격자를 벗어나지 않는 경우 술래가 있는 경우라면 움직이지 않고, 술래가 없다면 해당 칸으로 이동(나무가 있어도 가능)
 * 1-2. 격자를 벗어나는 경우 방향을 반대로 틀고 술래가 없다면 움직임
 * 2. 술래 움직임
 * 2-1. 술래는 위쪽 방향으로 시작하여 달팽이 모양으로 움직임(시계방향)
 * 2-2. 만약 끝에 도달하게 되면 다시 거꾸로 중심으로 이동하고, 중심에 오게 되면 다시 시계방향으로
 * 3. 술래는 이동 후 바로 방향을 틀어주고, 시야 내 도망자 잡음(현재 칸 포함 3칸)
 * 3-1. 만약 나무가 놓여있는 칸이라면 도망자는 가려져 잡히지 않음
 * 4. 현재 t번째 턴일 때 (t x 이번 턴에 잡힌 도망자 수) 점수를 얻게 됨
 * 
 * k번에 걸쳐 술래잡기를 진행하는 동안 술래가 총 얻게된 점수?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

#define MAX_N 99

using namespace std;

constexpr int dtx[4] = {0, 1, 0, -1};
constexpr int dty[4] = {-1, 0, 1, 0};
constexpr int dfx[2][2] = {{1, -1}, {0, 0}};
constexpr int dfy[2][2] = {{0, 0}, {1, -1}};

int n, m, h, k;
int cenx, ceny;
vector<int> grid[MAX_N][MAX_N];  // 나무 -2, 술래 -1, 도망자 >= 0
bool visited[MAX_N][MAX_N];  // 술래 움직임

struct Person {
  int x, y, p, d;
};
Person target;
Person flees[MAX_N * MAX_N];

#if DEBUG
void dPrintGrid() {
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (grid[y][x].empty()) cout << ". ";
      else {
        for (int i = 0; i < grid[y][x].size(); ++i) {
          cout << grid[y][x][i];
        }
        cout << ' ';
      }
    }
    cout << endl;
  }
  cout << endl;
}
#endif

bool isExist(int x, int y, int num) {
  for (int elem : grid[y][x]) {
    if (elem == num) {
      return true;
    }
  }
  return false;
}

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void movePerson(int nx, int ny, int num) {
  int cx = num == -1 ? target.x : flees[num].x;
  int cy = num == -1 ? target.y : flees[num].y;

  vector<int>& vec = grid[cy][cx];
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (*it == num) {
      vec.erase(it);
      break;
    }
  }

  if (num == -1) {
    target.x = nx;
    target.y = ny;
  } else {
    flees[num].x = nx;
    flees[num].y = ny;
  }
  grid[ny][nx].push_back(num);
}

void moveFlees() {
  for (int i = 0; i < m; ++i) {
    Person& flee = flees[i];
    if (flee.x == -1 || 
        (abs(flee.x - target.x) + abs(flee.y - target.y) > 3)) {
      continue;
    }
    int nx = flee.x + dfx[flee.p][flee.d];
    int ny = flee.y + dfy[flee.p][flee.d];
    if (!isInRange(nx, ny)) {
      flee.d = (flee.d + 1) % 2;
      nx = flee.x + dfx[flee.p][flee.d];
      ny = flee.y + dfy[flee.p][flee.d];
    }
    if (!isExist(nx, ny, -1)) {
      movePerson(nx, ny, i);
    }
  }
}

void moveTarget() {
  if (target.p == 0) {
    // move clockwise
    int nx = target.x + dtx[target.d];
    int ny = target.y + dty[target.d];
    movePerson(nx, ny, -1);
    visited[ny][nx] = true;
    
    if (nx == 0 && ny == 0) {
      target.p = 1;
      target.d = 2;
      memset(visited, 0, sizeof(visited));
      visited[0][0] = true;
    } else {
      int nd = (target.d + 1) % 4;
      int nrx = nx + dtx[nd];
      int nry = ny + dty[nd];
      if (!visited[nry][nrx]) {
        target.d = nd;
      }
    }
  } else {
    // move reverse
    int nx = target.x + dtx[target.d];
    int ny = target.y + dty[target.d];
    movePerson(nx, ny, -1);
    visited[ny][nx] = true;

    if (nx == cenx && ny == ceny) {
      target.p = 0;
      target.d = 0;
      memset(visited, 0, sizeof(visited));
      visited[ceny][cenx] = true;
    } else {
      nx = target.x + dtx[target.d];
      ny = target.y + dty[target.d];
      if (!isInRange(nx, ny) || visited[ny][nx]) {
        target.d = (target.d - 1 + 4) % 4;
      }
    }
  }
}

int catchFlees() {
  int ret = 0;
  for (int i = 0; i < 3; ++i) {
    int nx = target.x + dtx[target.d] * i;
    int ny = target.y + dty[target.d] * i;
    if (isInRange(nx, ny) && !isExist(nx, ny, -2)) {
      vector<int>& vec = grid[ny][nx];
      for (auto it = vec.begin(); it != vec.end(); ) {
        if (*it >= 0) {
          Person& flee = flees[*it];
          flees[*it].x = -1;
          flees[*it].y = -1;
          vec.erase(it);
          ++ret;
        } else {
          ++it;
        }
      }
    }
  }

  return ret;
}

int simulation(int num) {
  moveFlees();

  moveTarget();

#if DEBUG
  dPrintGrid();
#endif

  int catch_num = catchFlees();

  return num * catch_num;
}

void input() {
  cin >> n >> m >> h >> k;
  cenx = n/2;
  ceny = n/2;
  target.x = cenx;
  target.y = ceny;
  grid[target.y][target.x].push_back(-1);
  visited[target.y][target.x] = true;
  for (int i = 0; i < m; ++i) {
    cin >> flees[i].y >> flees[i].x >> flees[i].p;
    --flees[i].x;
    --flees[i].y;
    --flees[i].p;
    grid[flees[i].y][flees[i].x].push_back(i);
  }

  for (int i = 0; i < h; ++i) {
    int x, y;
    cin >> y >> x;
    grid[--y][--x].push_back(-2);
  }
}

void init() {
  for (int y = 0; y < MAX_N; ++y) {
    for (int x = 0; x < MAX_N; ++x) {
      grid[y][x].clear();
    }
  }
  memset(visited, 0, sizeof(visited));
  target = {-1, -1, 0, 0};
  memset(flees, 0, sizeof(flees));
}

void solution() {
  init();
  input();

  int ans = 0;
  for (int i = 1; i <= k; ++i) {
    ans += simulation(i);
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2022-1-morning1.input", "r", stdin);
  freopen("2022-1-morning1.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}