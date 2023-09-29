// 어른 상어
// 삼성 2020년 상반기 오후 1번
// 출처: https://www.acmicpc.net/problem/19237

/**
 * 상어에는 1~M 자연수 번호, 모든 번호는 다름
 * 상어는 다른 상어들을 쫓아내려고 하는데, 1의 번호를 가진 상어는 가장 강력
 * 
 * NxN(2~20) 격자 중 M개의 칸에 상어가 한 마리씩
 * 1초마다 모든 상어는 동시에 상하좌우로 인접한 칸 중 하나로 이동
 * 이동한 칸에 냄새를 뿌리고 k(1~1000)번 이동하고 나면 사라짐
 * 
 * 상어 이동:
 * 1. 인접한 칸 중 아무 냄새가 없는 칸의 방향
 * 2. 그런 칸이 없으면 자신의 냄새가 있는 칸의 방향
 * 3. 가능한 칸이 여러 개면 우선순위에 따라(상어마다, 방향마다 다름)
 * 
 * 모든 상어가 이동 후 한 칸에 상어가 여러 마리 있으면 가장 작은 번호를 가진 상어 제외하고 모두 쫓겨남
 * 1번 상어만 격자에 남게 되기까지 몇 초가 걸리는지?(1000초 넘으면 -1)
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <map>
#include <vector>

#define MAX_N 20
#define DIR_NUM 4

using namespace std;

constexpr int dx[DIR_NUM] = {0, 0, -1, 1};
constexpr int dy[DIR_NUM] = {-1, 1, 0, 0};

int N, M, k;
int grid[MAX_N][MAX_N];
int new_grid[MAX_N][MAX_N];
int dir_order[MAX_N * MAX_N + 1][DIR_NUM][DIR_NUM];

struct Scent {
  int num, time;
};
Scent scent[MAX_N][MAX_N];

struct Shark {
  int dir, x, y;
  Shark() {}
  Shark(int d, int _x, int _y) : dir(d), x(_x), y(_y) {}
};
map<int, Shark> sharks;

bool isInRange(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

bool moveShark(int nx, int ny, int shark_num) {
  if (new_grid[ny][nx]) {
    return true;
  }

  new_grid[ny][nx] = shark_num;
  sharks[shark_num].x = nx;
  sharks[shark_num].y = ny;
  scent[ny][nx].num = shark_num;
  scent[ny][nx].time = k;
  return false;
}

void simulate() {
  memset(new_grid, 0, sizeof(new_grid));
  Scent old_scent[MAX_N][MAX_N];
  memcpy(old_scent, scent, sizeof(old_scent));
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      int t = scent[y][x].time;
      if (t > 1) {
        --scent[y][x].time;
      } else if (t == 1) {
        --scent[y][x].time;
        scent[y][x].num = 0;
      }
    }
  }

  vector<int> vec;
  for (const auto& it : sharks) {
    int shark_num = it.first;
    Shark shark = it.second;
    bool moved = false;
    for (int i = 0; i < DIR_NUM; ++i) {
      int dir = dir_order[shark_num][shark.dir][i];
      int nx = shark.x + dx[dir];
      int ny = shark.y + dy[dir];
      if (isInRange(nx, ny) && !old_scent[ny][nx].num) {
        sharks[shark_num].dir = dir;
        bool erased = moveShark(nx, ny, shark_num);
        if (erased) {
          vec.push_back(shark_num);
        }
        moved = true;
        break;
      }
    }

    if (!moved) {
      for (int i = 0; i < DIR_NUM; ++i) {
        int dir = dir_order[shark_num][shark.dir][i];
        int nx = shark.x + dx[dir];
        int ny = shark.y + dy[dir];
        if (isInRange(nx, ny) && old_scent[ny][nx].num == shark_num) {
          sharks[shark_num].dir = dir;
          int erased = moveShark(nx, ny, shark_num);
          if (erased) {
            vec.push_back(shark_num);
          }
          moved = true;
          break;
        }
      }
    }
  }

  for (int num : vec) {
    sharks.erase(num);
  }

  memcpy(grid, new_grid, sizeof(grid));
}

void input() {
  cin >> N >> M >> k;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      int num;
      cin >> num;
      grid[y][x] = num;
      if (num) {
        sharks[num] = Shark(-1, x, y);
        scent[y][x].num = num;
        scent[y][x].time = k;
      }
    }
  }

  for (int i = 1; i <= M; ++i) {
    int d;
    cin >> d;
    sharks[i].dir = --d;
  }

  for (int a = 1; a <= M; ++a) {
    for (int b = 0; b < DIR_NUM; ++b) {
      for (int c = 0; c < DIR_NUM; ++c) {
        cin >> dir_order[a][b][c];
        --dir_order[a][b][c];
      }
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  memset(scent, 0, sizeof(scent));
  memset(dir_order, 0, sizeof(dir_order));
  sharks.clear();
}

void solution() {
  init();
  input();

  int ans = 0;
  while (sharks.size() > 1) {
    if (ans >= 1000) {
      ans = -1;
      break;
    }

#if DEBUG
    cout << "---t: " << ans << "---" << endl;
    cout << "grid" << '\t' << "scent" << endl;
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < N; ++x) {
        cout << grid[y][x];
      }
      cout << '\t';
      for (int x = 0; x < N; ++x) {
        cout << scent[y][x].time;
      }
      cout << endl;
    }
    cout << endl;
#endif

    simulate();
    ++ans;
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-1-afternoon1.input", "r", stdin);
  freopen("2020-1-afternoon1.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }
  return 0;
}
