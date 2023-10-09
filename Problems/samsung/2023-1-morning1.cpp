// 포탑 부수기
// 삼성 2023년도 상반기 오전 1번
// 출처: https://www.codetree.ai/training-field/frequent-problems/problems/destroy-the-turret?&utm_source=clipboard&utm_medium=text

/**
 * NxM 격자, 모든 위치에 포탑 존재하며 각 포탑에는 공격력이 있고, 상황에 따라 공격력이 줄어들거나 늘어날 수 있음
 * 공력력이 0이하가 된다면 해당 포탑은 부서지며 더 이상의 공격 불가(최초에 0인 포탑도 존재 가능)
 * 
 * 하나의 턴은 4가지 액션을 순서대로 수행하며, 총 K번 반복(부서지지 않은 포탑이 1개가 된다면 즉시 중지)
 * 1. 공격자 선정
 * 1-1. 부서지지 않은 포탑 중 가장 약한 포탑이 공격자로 선정되어 핸디캡을 적용한 N+M만큼 공격력 증가
 * 1-2. 가장 약한 포탑은 공격력이 가장 낮은 포탑이 2개 이상이면 가장 최근에 공격한 포탑이 가장 약한 포탑
 * 1-3. 만약 그런 포탑이 여러 개이면, 행과 열의 합이 가장 큰 포탑이 가장 약한 포탑
 * 1-4. 만약 그런 포탑이 여러 개이면, 열 값이 가장 큰 포탑이 가장 약한 포탑
 * 
 * 2. 공격자 공격
 * 2-1. 자신을 제외한 가장 강한 포탑을 공격(선정 기준은 약한 포탑 기준의 반대)
 * 2-2. 공격을 할 떄에는 레이저 공격을 먼저 시도하고, 그게 안 된다면 포탄 공격
 * 
 * (1) 레이저 공격 - 공격자의 위치에서 공격 대상 포탑까지의 최단 경로로 공격(만약 최단 경로가 여러 개면 우하좌상 순 우선순위)
 * (1-1) 상하좌우의 4개 방향으로 움직일 수 있음
 * (1-2) 부서진 포탑이 있는 위치는 지날 수 없음
 * (1-3) 가장자리에서 막힌 방향으로 진행하고자 한다면 반대편으로 나옴(N행~1행, N열~1열 연결)
 * 최단경로가 정해졌으면 공격 대상에는 공격자의 공격력만큼 피해 입히며, 레이저 경로에 있는 포탑 역시 공격자의 공격력 절반 만큼 피해
 * 
 * (2) 포탄 공격
 * 공격 대상에 포탄을 던져 공격력 만큼의 피해를 주고, 주위 8개 방향에 있는 포탑도 공격자 공격력의 절반만큼 피해
 * 공격자는 공격에 영향을 받지 않고, 가장자리에 포탄이 떨어졌다면 추가 피해가 반대편 격자에 미
 * 
 * 3. 포탑 부서짐 - 공격을 받아 공격력이 0 이하가 된 포탑은 부서짐침
 * 4. 포탑 정비 - 공격과 무관했던 포탑은 공격력이 1씩 올라감
 * 
 * 전체 과정 종료 후 남아있는 포탑 중 가장 강한 포탑의 공격력?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <tuple>
#include <queue>

#define MAX_N 10

using namespace std;

int N, M, K;
int turn;
int grid[MAX_N][MAX_N];
int history[MAX_N][MAX_N];
bool attacked[MAX_N][MAX_N];

#if DEBUG
void dPrintGrid() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      cout << grid[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

pair<int, int> selectAttacker() {
  // 공격력 낮, 턴 높, 합 큰, 열 큰
  priority_queue<tuple<int, int, int, int, pair<int, int>>> pq;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      if (grid[y][x] <= 0) {
        continue;
      }
      pq.push({-grid[y][x], history[y][x], x+y, x, {x, y}});
    }
  }

  return get<4>(pq.top());
}

pair<int, int> selectTarget(pair<int, int> attacker) {
  priority_queue<tuple<int, int, int, int, pair<int, int>>> pq;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      if (grid[y][x] <= 0 || (attacker.first == x && attacker.second == y)) {
        continue;
      }
      pq.push({grid[y][x], -history[y][x], -x-y, -x, {x, y}});
    }
  }

  return get<4>(pq.top());
}

bool tryLaser(pair<int, int> attacker, pair<int, int> target) {
  const int dx[4] = {1, 0, -1, 0};
  const int dy[4] = {0, 1, 0, -1};

  queue<pair<int, int>> q;
  q.push(attacker);
  bool visited[MAX_N][MAX_N] = {false,};
  visited[attacker.second][attacker.first] = true;
  pair<int, int> parent[MAX_N][MAX_N];
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    if (cur == target) {
      int damage = grid[attacker.second][attacker.first];
      grid[target.second][target.first] -= damage;
      while (1) {
        cur = parent[cur.second][cur.first];
        if (cur == attacker) {
          break;
        }
        grid[cur.second][cur.first] -= damage / 2;
        attacked[cur.second][cur.first] = true;
      }
      return true;
    }

    for (int i = 0; i < 4; ++i) {
      int nx = (cur.first + dx[i] + M) % M;
      int ny = (cur.second + dy[i] + N) % N;
      if (grid[ny][nx] > 0 && !visited[ny][nx]) {
        visited[ny][nx] = true;
        q.push({nx, ny});
        parent[ny][nx] = {cur.first, cur.second};
      }
    }
  }

  return false;
}

void cannonAttack(pair<int, int> attacker, pair<int, int> target) {
  const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
  const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
  
  int damage = grid[attacker.second][attacker.first];
  grid[target.second][target.first] -= damage;
  for (int i = 0; i < 8; ++i) {
    int nx = (target.first + dx[i] + M) % M;
    int ny = (target.second + dy[i] + N) % N;
    if (nx == attacker.first && ny == attacker.second) {
      continue;
    }
    grid[ny][nx] -= damage / 2;
    attacked[ny][nx] = true;
  }
}

void simulation() {
  pair<int, int> attacker = selectAttacker();
  history[attacker.second][attacker.first] = turn;
  grid[attacker.second][attacker.first] += N + M;
  
  pair<int, int> target = selectTarget(attacker);

  memset(attacked, 0, sizeof(attacked));
  bool success = tryLaser(attacker, target);
  if (!success) {
    cannonAttack(attacker, target);
  }

  for (int y = 0; y < N; ++y) {
    for (int x= 0; x < M; ++x) {
      pair<int, int> cur = {x, y};
      if (grid[y][x] > 0 && cur != attacker && cur != target && !attacked[y][x]) {
        ++grid[y][x];
      }
    }
  }
}

void input() {
  cin >> N >> M >> K;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      cin >> grid[y][x];
    }
  }
}

void init() {
  turn = 0;
  memset(grid, 0, sizeof(grid));
  memset(history, 0, sizeof(history));
}

bool checkDone() {
  int num = 0;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      if (grid[y][x] > 0) {
        ++num;
        if (num > 1) {
          return false;
        }
      }
    }
  }

  return true;
}

void solution() {
  init();
  input();

  while (K--) {
    ++turn;
    simulation();
#if DEBUG
    dPrintGrid();
#endif
    if (checkDone()) {
      break;
    }
  }

  int ans = 0;
  for (int y = 0; y < N; ++y) {
    for (int x= 0; x < M; ++x) {
      if (grid[y][x] > ans) {
        ans = grid[y][x];
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2023-1-morning1.input", "r", stdin);
  freopen("2023-1-morning1.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}