// 마법사 상어와 비바라기
// 삼성 2021년도 상반기 오후 1번
// 출처: https://www.acmicpc.net/problem/21610

/**
 * NxN 크기 격자, 1행과 N행 연결, 1열과 N열 연결됨
 * 각 칸에는 바구니가 하나 있고, A[r][c]는 (r,c)에 있는 바구니에 저장되어 있는 물의 양
 * 
 * 비바라기를 시전하면 (N,1), (N,2), (N-1,1), (N-1,2)에 비구름이 생기고 이동을 M번 명령
 * 명령은 방향 d와 거리 s로 이루어지고 방향은 8개 정수로 표현(좌상우하 순)
 * 1. 모든 구름이 d방향으로 s칸 이동
 * 2. 각 구름에서 비가 내려 바구니에 저장된 물의 양 1 증가
 * 3. 구름이 모두 사라짐
 * 4. 2에서 물이 증가한 칸 (r,c)에 물복사버그 마법 시전하여 대각선 방향으로 거리가 1인 칸에 물이 있는 바구니 수 만큼 바구니의 물의 양 증가
 * 4-1. 경계를 넘어가는 칸은 대각선 방향으로 거리가 1인 칸이 아님
 * 5. 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고 물의 양 2 줄어듦
 * 5-1. 구름이 생기는 칸은 3에서 구름이 사라진 칸이 아니어야 함
 * 
 * M번의 이동이 모두 끝난 후 바구니에 들어있는 물의 양 합?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <queue>
#include <set>

#define MAX_N 50
#define MAX_M 100
#define DIR_NUM 8

using namespace std;

constexpr int dx[DIR_NUM] = {-1, -1, 0, 1, 1, 1, 0, -1};
constexpr int dy[DIR_NUM] = {0, -1, -1, -1, 0, 1, 1, 1};

int N, M;
int A[MAX_N][MAX_N];

struct Spell {
  int d, s;
};
Spell command[MAX_M];

queue<pair<int, int>> q;
set<pair<int, int>> cloud_set;

#if DEBUG
void dPrintGrid() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << A[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

bool isInRange(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

void input() {
  cin >> N >> M;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> A[y][x];
    }
  }

  for (int i = 0; i < M; ++i) {
    int d;
    cin >> d;
    command[i].d = --d;
    cin >> command[i].s;
  }

  q.push({0, N-1});
  q.push({0, N-2});
  q.push({1, N-1});
  q.push({1, N-2});
}

void init() {
  memset(A, 0, sizeof(A));
  memset(command, 0, sizeof(command));
  q = queue<pair<int, int>>();
}

void simulation(int num) {
  Spell spell = command[num];
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    int ns = spell.s % N;
    int nx = (cur.first + dx[spell.d] * ns + N) % N;
    int ny = (cur.second + dy[spell.d] * ns + N) % N;
    cloud_set.insert({nx, ny});
    ++A[ny][nx];
  }

  int temp[MAX_N][MAX_N] = {0,};
  memcpy(temp, A, sizeof(temp));
  for (const auto& it : cloud_set) {
    for (int i = 1; i < DIR_NUM; i += 2) {
      int nx = it.first + dx[i];
      int ny = it.second + dy[i];
      if (isInRange(nx, ny) && temp[ny][nx]) {
        ++A[it.second][it.first];
      }
    }
  }

  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (A[y][x] >= 2 && (cloud_set.find({x, y}) == cloud_set.end())) {
        q.push({x, y});
        A[y][x] -= 2;
      }
    }
  }
  cloud_set.clear();
}

void solution() {
  init();
  input();

  for (int i = 0; i < M; ++i) {
#if DEBUG
    dPrintGrid();
#endif
    simulation(i);
  }

  int ans = 0;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      ans += A[y][x];
    }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-1-afternoon1.input", "r", stdin);
  freopen("2021-1-afternoon1.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}