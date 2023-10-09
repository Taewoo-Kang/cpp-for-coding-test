// 마법사 상어와 복제
// 삼성 2021년도 하반기 오후 1번
// 출처: https://www.acmicpc.net/problem/23290

/**
 * 4x4 크기의 격자, (r,c)는 r행 c열
 * 격자에 M마리 물고기, 이동방향은 8방 중 하나
 * 마법사 상어도 격자의 한 칸에 들어가 있으며, 물고기와 같은 칸에 있을 수 있음
 * 
 * 1. 복제 마법 시전 - 시간이 걸려 5번에서 칸에 나타남
 * 2. 모든 물고기가 한 칸 이동 - 상어가 있는 칸, 물고기 냄새가 있는 칸, 격자 범위를 벗어나는 칸 이동 불가
 *    물고기는 이동방향이 이동할 수 있는 칸을 향할 때까지 반시계 45도 회전
 * 3. 상어가 연속해서 3칸 이동(상하좌우), 연속해서 3칸 이동 시 격자의 범위를 벗어나는 칸이 있다면 이동 불가능한 방법
 *    연속해서 이동하는 중에 상어가 물고기가 있는 칸으로 이동하게 되면 물고기는 격자에서 제외되고 물고기 냄새를 남김
 *    가능한 이동 방법 중 제외되는 물고기 수가 가장 많은 방법으로 이동하며, 여러가지인 경우 사전순으로
 *    상좌하우를 1,2,3,4로 변환하고 이어붙인 값이 작으면 사전순으로 앞선 것
 * 4. 두 번 전의 연습에서 생긴 물고기 냄새가 격자에서 사라짐
 * 5. 1에서 사용한 복제 마법이 완료되어 그 복제된 위치와 방향을 그대로 갖게 됨
 * 
 * S번의 연습을 모두 마쳤을 때 격자에 있는 물고기의 수?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <string>

#define MAX_N 4
#define DIR_NUM 8

using namespace std;

constexpr int dx[DIR_NUM] = {-1, -1, 0, 1, 1, 1, 0, -1};
constexpr int dy[DIR_NUM] = {0, -1, -1, -1, 0, 1, 1, 1};
constexpr int dsx[4] = {0, -1, 0, 1};
constexpr int dsy[4] = {-1, 0, 1, 0};

int M, S;

int grid[MAX_N][MAX_N][DIR_NUM];  // 위치와 방향이 같은 물고기의 개수를 관리
int cloneGrid[MAX_N][MAX_N][DIR_NUM];
int copyGrid[MAX_N][MAX_N][DIR_NUM];  // 상어 이동용
int smell[MAX_N][MAX_N];

struct Shark {
  int x, y;
} shark;

string max_path;
int max_kill;

#if DEBUG
void dPrintGrid() {
  for (int y = 0; y < MAX_N; ++y) {
    for (int x = 0; x < MAX_N; ++x) {
      int cnt = 0;
      for (int d = 0; d < DIR_NUM; ++d) {
        cnt += grid[y][x][d];
      }
      if (x == shark.x && y == shark.y) {
        if (cnt) {
          cout << 'x' << cnt << ' ';
        } else {
          cout << "x ";
        }
      } else if (!cnt) {
        cout << ". ";
      } else {
        cout << cnt << ' ';
      }
    }
    cout << endl;
  }
  cout << "Smell:" << endl;
  for (int y = 0; y < MAX_N; ++y) {
    for (int x = 0; x < MAX_N; ++x) {
      cout << smell[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

bool isInRange(int x, int y) {
  return x >= 0 && x < MAX_N && y >= 0 && y < MAX_N;
}

void moveFishs() {
  for (int y = 0; y < MAX_N; ++y) {
    for (int x = 0; x < MAX_N; ++x) {
      for (int d = 0; d < DIR_NUM; ++d) {
        int nd = d;
        int nx = x + dx[nd];
        int ny = y + dy[nd];
        int cnt = 0;
        bool canMove = true;
        while (!isInRange(nx, ny) || (nx == shark.x && ny == shark.y) || smell[ny][nx]) {
          if (cnt > 8) {
            canMove = false;
            break;
          }
          nd = (nd - 1 + 8) % 8;
          nx = x + dx[nd];
          ny = y + dy[nd];
          ++cnt;
        }

        if (!canMove) {
          continue;
        }

        grid[y][x][d] -= cloneGrid[y][x][d];
        grid[ny][nx][nd] += cloneGrid[y][x][d];
      }
    }
  }
}

int calcKillNum(const string& path) {
  int kill = 0;

  int nx = shark.x;
  int ny = shark.y;
  for (char c : path) {
    int dir = c - '0';
    nx = nx + dsx[dir];
    ny = ny + dsy[dir];
    for (int d = 0; d < DIR_NUM; ++d) {
      kill += copyGrid[ny][nx][d];
      copyGrid[ny][nx][d] = 0;
    }
  }

  memcpy(copyGrid, grid, sizeof(grid));

  return kill;
}

void dfs(int depth, int sx, int sy, int dir, string path) {
  if (depth == 3) {
    int kill = calcKillNum(path);
    if (kill > max_kill) {
      max_kill = kill;
      max_path = path;
    }
    return;
  }

  for (int d = 0; d < 4; ++d) {
    int nx = sx + dsx[d];
    int ny = sy + dsy[d];
    if (!isInRange(nx, ny)) {
      continue;
    }
    char c = d + '0';
    dfs(depth + 1, nx, ny, d, path + c);
  }
}

void moveShark() {
  memcpy(copyGrid, grid, sizeof(grid));

  max_kill = -1;
  max_path = "";
  dfs(0, shark.x, shark.y, 0, "");

  int nx = shark.x;
  int ny = shark.y;
  for (char c : max_path) {
    int dir = c - '0';
    nx = nx + dsx[dir];
    ny = ny + dsy[dir];
    for (int d = 0; d < DIR_NUM; ++d) {
      if (grid[ny][nx][d]) {
        grid[ny][nx][d] = 0;
        smell[ny][nx] = 3;
      }
    }
  }
  shark.x = nx;
  shark.y = ny;
}

void simulation() {
  memcpy(cloneGrid, grid, sizeof(grid));

  moveFishs();

#if DEBUG
  cout << "After move:" << endl;
  dPrintGrid();
#endif

  moveShark();

#if DEBUG
  cout << "After eat:" << endl;
  dPrintGrid();
#endif

  for (int y = 0; y < MAX_N; ++y) {
    for (int x = 0; x < MAX_N; ++x) {
      if (smell[y][x]) {
        --smell[y][x];
      }
      for (int d = 0; d < DIR_NUM; ++d) {
        grid[y][x][d] += cloneGrid[y][x][d];
      }
    }
  }

}

void input() {
  cin >> M >> S;
  for (int i = 0; i < M; ++i) {
    int x, y, d;
    cin >> y >> x >> d;
    ++grid[--y][--x][--d];
  }
  cin >> shark.y >> shark.x;
  --shark.x;
  --shark.y;
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(cloneGrid, 0, sizeof(cloneGrid));
  memset(copyGrid, 0, sizeof(copyGrid));
  memset(smell, 0, sizeof(smell));
  shark = {-1, -1};
  max_kill = -1;
}

void solution() {
  init();
  input();

  while (S--) {
    simulation();
#if DEBUG
  dPrintGrid();
#endif
  }

  int ans = 0;
  for (int y = 0; y < MAX_N; ++y) {
    for (int x = 0; x < MAX_N; ++x) {
      for (int d = 0; d < DIR_NUM; ++d) {
        ans += grid[y][x][d];
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-2-afternoon1.input", "r", stdin);
  freopen("2021-2-afternoon1.output", "w", stdout);
  for (int i = 0; i < 8; ++i) {
    solution();
  }

  return 0;
}