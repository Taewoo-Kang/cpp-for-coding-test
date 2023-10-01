// 마법사 상어와 토네이도
// 삼성 2020년 하반기 오후 1번
// 출처: https://www.acmicpc.net/problem/20057

/**
 * NxN 격자, A[r][c]는 위치 (r,c)에 있는 모래의 양을 의미
 * 토네이도를 시전하면 가운데 칸부터 토네이도의 이동이 시작, 토네이도는 한 번에 한 칸 이동
 * 
 * 토네이도가 한 칸 이동할 때마다 모래는 일정한 비율로 흩날리게 됨
 * 토네이도가 x에서 y로 이동하면 비율이 적혀있는 칸으로 y에 있는 모래의 해당 비율만큼 이동(소수점 아래 버림),
 * \alpha로 이동하는 모래의 양은 비율이 적혀있는 칸으로 이동하지 않은 남은 모래의 양
 * 모래가 이미 있는 칸으로 모래가 이동하면 모래의 양은 더해짐
 * 
 * 토네이도가 (1,1)까지 이동하여 소멸되었을 때 격자 밖으로 나간 모래의 양?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>

#define MAX_N 499
#define DIR_NUM 4
#define MOVE_RANGE 5

using namespace std;

constexpr int dx[DIR_NUM] = {-1, 0, 1, 0};
constexpr int dy[DIR_NUM] = {0, 1, 0, -1};
constexpr int move_ratio[MOVE_RANGE][MOVE_RANGE] = {{0, 0, 2, 0, 0},
                                                    {0, 10, 7, 1, 0},
                                                    {5, 0, 0, 0, 0},
                                                    {0, 10, 7, 1, 0},
                                                    {0, 0, 2, 0, 0}};

int N, ans;
int A[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

struct Tornado {
  int x, y, dir;
} tornado;

void _dPrintGrid() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << A[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

void _dCheckVisited() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << visited[y][x];
    }
    cout << endl;
  }
  cout << endl;
}

bool isInRange(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

pair<int, int> rotate(int x, int y, int d) {
  if (d % DIR_NUM == 0) {
    return {x, y};
  }
  return rotate(y, MOVE_RANGE - x - 1, d + 1);
}

void _dCheckRotate(int d) {
  cout << "Dir: " << d << endl;
  for (int yy = 0; yy < MOVE_RANGE; ++yy) {
    for (int xx = 0; xx < MOVE_RANGE; ++xx) {
      pair<int, int> rot = rotate(xx, yy, d);
      cout << move_ratio[rot.second][rot.first] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

void _dCheckMove(int x, int y, int d) {
  int grid[MAX_N][MAX_N] = {0,};
  memset(grid, 0, sizeof(grid));

  for (int yy = 0; yy < MOVE_RANGE; ++yy) {
    for (int xx = 0; xx < MOVE_RANGE; ++xx) {
      int nx = x - MOVE_RANGE/2 + xx;
      int ny = y - MOVE_RANGE/2 + yy;
      if (isInRange(nx, ny)) {
        pair<int, int> rot = rotate(xx, yy, d);
        grid[ny][nx] = move_ratio[rot.second][rot.first];
      }
    }
  }
  grid[y][x] = -1;
  int nx = x + dx[d];
  int ny = y + dy[d];
  if (isInRange(nx, ny)) {
    grid[ny][nx] = -2;
  }

  for (int yy = 0; yy < N; ++yy) {
    for (int xx = 0; xx < N; ++xx) {
      cout << grid[yy][xx] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

void simulate() {
  tornado.x = tornado.x + dx[tornado.dir];
  tornado.y = tornado.y + dy[tornado.dir];
  visited[tornado.y][tornado.x] = true;

  int cd = tornado.dir;
  int nd = (tornado.dir + 1) % DIR_NUM;
  if (!visited[tornado.y + dy[nd]][tornado.x + dx[nd]]) {
    tornado.dir = nd;
  }

#if DEBUG
  // _dCheckVisited();
  // _dCheckRotate(cd);
  // _dCheckMove(tornado.x, tornado.y, cd);
#endif

  int cur_sand = A[tornado.y][tornado.x];
  int remain = cur_sand;
  for (int yy = 0; yy < MOVE_RANGE; ++yy) {
    for (int xx = 0; xx < MOVE_RANGE; ++xx) {
      pair<int, int> rot = rotate(xx, yy, cd);
      int new_sand = cur_sand * move_ratio[rot.second][rot.first] / 100;
      remain -= new_sand;

      int nx = tornado.x - MOVE_RANGE/2 + xx;
      int ny = tornado.y - MOVE_RANGE/2 + yy;
      if (isInRange(nx, ny)) {
        A[ny][nx] += new_sand;
      } else {
        ans += new_sand;
      }
    }
  }
  int nx = tornado.x + dx[cd];
  int ny = tornado.y + dy[cd];
  if (isInRange(nx, ny)) {
    A[ny][nx] += remain;
  } else {
    ans += remain;
  }
  A[tornado.y][tornado.x] = 0;
}

void input() {
  cin >> N;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> A[y][x];
    }
  }
  tornado.x = N/2;
  tornado.y = N/2;
}

void init() {
  ans = 0;
  memset(A, 0, sizeof(A));
  memset(visited, 0, sizeof(visited));
  tornado = {-1, -1, 0};

}

void solution() {
  init();
  input();

  while (!visited[0][0]) {
#if DEBUG
    _dPrintGrid();
#endif
    visited[tornado.y][tornado.x] = true;
    simulate();
  }
  
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-2-afternoon1.input", "r", stdin);
  freopen("2020-2-afternoon1.output", "w", stdout);
  for (int i = 0; i < 6; ++i) {
    solution();
  }

  return 0;
}