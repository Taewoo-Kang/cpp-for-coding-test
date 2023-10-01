// 상어 중학교
// 삼성 2021년도 상반기 오전 2번
// 출처: https://www.acmicpc.net/problem/21609

/**
 * NxN 크기의 격자, 모든 칸에는 블록이 하나씩 들어있고, 블록은 검은색, 무지개, 일반 블록이 존재
 * 일반 블록은 M가지 색상(1~M), 검은색 블록은 -1, 무지개 블록은 0으로 표현
 * |r1-r2| + |c1-c2| = 1을 만족하는 두 컨을 인접한 칸이라고 함
 * 
 * 블록 그룹은 연결된 블록의 집합으로, 일반 블록이 적어도 하나 존재해야하며 색은 모두 같아야 함
 * 검은색 블록은 포함되면 안 되고, 무지개 블록은 얼마나 들어있든 상관없음
 * 블록 그룹의 기준 블록은 일반 블록 중에서 행/열 순에서 가장 작은 블록
 * 
 * 게임의 오토 플레이 기능
 * 1. 크기가 가장 큰 블록 그룹을 찾는다.
 * 1-1. 여러 개라면 무지개 블록의 수, 기준 블록의 행/열 순으로 가장 큰 것 찾음
 * 2. 1에서 찾은 블록 그룹의 모든 블록을 제거하고 그 갯수의 제곱점을 획득
 * 3. 격자에 중력 작용하여 검은색 블록을 제외한 모든 블록이 행의 번호가 큰 칸으로 이동
 * 3-1. 이동은 다른 블록이나 격자의 경계를 만나기 전까지 계속
 * 4. 격자가 90도 반시계 방향으로 회전
 * 5. 다시 격자에 중력 작용
 * 6. 블록 그룹이 존재하지 않으면 종료
 * 
 * 오토 플레이가 끝났을 때 획득한 점수의 합?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
#include <cmath>

#define MAX_N 20

using namespace std;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, -1, 0, 1};

int N, M;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int ans;

tuple<int, int, int, int> best;  // 블록 갯수, 무지개 갯수, 행, 열
vector<pair<int, int>> blocks;

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

void bfs(int x, int y) {
  queue<pair<int, int>> q;
  q.push({x, y});
  visited[y][x] = true;

  bool temp[MAX_N][MAX_N];
  memcpy(temp, visited, sizeof(temp));

  vector<pair<int, int>> vec;
  vec.push_back({x, y});
  int block_num = 1;
  int rainbow_num = 0;
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      int nx = cur.first + dx[i];
      int ny = cur.second + dy[i];
      if (isInRange(nx, ny) && (grid[ny][nx] == 0 || grid[ny][nx] == grid[y][x])  && !temp[ny][nx]) {
        temp[ny][nx] = true;
        if (grid[ny][nx] > 0) {
          visited[ny][nx] = true;  // NOTE: 무지개 블록은 다른 bfs에서도 공유하기 위함
        } else {
          ++rainbow_num;
        }
        ++block_num;
        q.push({nx, ny});
        vec.push_back({nx, ny});
      }
    }
  }

  tuple<int, int, int, int> candi = {block_num, rainbow_num, y, x};
  if (candi > best) {
    best = candi;
    blocks = vec;
  }
}

void drop() {
  for (int y = N-1; y >= 0; --y) {
    for (int x = N-1; x >= 0; --x) {
      if (grid[y][x] < 0) {
        continue;
      }
      int temp = grid[y][x];
      grid[y][x] = -2;
      for (int yy = 0; yy < N - y; ++yy) {
        if (grid[y + yy][x] > -2) {
          grid[y + yy - 1][x] = temp;
          break;
        }
        if (y + yy == N-1) {
          grid[y + yy][x] = temp;
          break;
        }
      }
    }
  }
}

void rotate() {
  int temp[MAX_N][MAX_N] = {0,};
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      temp[N - 1 - x][y] = grid[y][x];
    }
  }

  memmove(grid, temp, sizeof(grid));
}

bool autoPlay() {
  memset(visited, 0, sizeof(visited));
  best = {0, 0, -N, -N};
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (grid[y][x] > 0 && !visited[y][x]) {
        bfs(x, y);
      }
    }
  }

  int cnt = blocks.size();
  if (cnt < 2) {
    return true;
  }

  ans += pow(cnt, 2);
  for (const auto& it : blocks) {
    grid[it.second][it.first] = -2;
  }
  blocks.clear();

#if DEBUG
  cout << "After Remove:" << endl;
  dPrintGrid();
  cout << "Get Point: " << pow(cnt, 2) << endl;
#endif

  drop();

#if DEBUG
  cout << "After Drop:" << endl;
  dPrintGrid();
#endif

  rotate();

#if DEBUG
  cout << "After Rotate:" << endl;
  dPrintGrid();
#endif

  drop();

#if DEBUG
  cout << "After Drop:" << endl;
  dPrintGrid();
#endif

  return false;
}

void simulate() {
  bool done = false;
  while (!done) {
    done = autoPlay();
  }
}

void input() {
  cin >> N >> M;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> grid[y][x];
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  ans = 0;
}

void solution() {
  init();
  input();
  
  simulate();
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-1-morning2.input", "r", stdin);
  freopen("2021-1-morning2.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}