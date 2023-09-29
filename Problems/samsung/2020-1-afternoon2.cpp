// 스타트 택시
// 삼성 2020년 상반기 오후 2번
// 출처: https://www.acmicpc.net/problem/19238

/**
 * 택시는 손님을 도착지로 데려다줄 때마다 연료가 충전되고, 연료가 바닥나면 업무 끝
 * NxN 격자 내 M명의 승객
 * 각 칸은 비어있거나 벽이 놓여있으며, 택시는 상하좌우로 인접한 빈칸 중 이동 가능
 * 특정 위치로 이동할 때 항상 최단경로로 이동
 *
 * 태울 승객을 고를 때는 현재 위치에서 최단거리가 가장 짧은 승객을 고름(여러 명이면 그 중 행/열 번호가 작은 순)
 * 연료는 한 칸 이동할 때마다 1만큼 소모, 승객을 목적지로 이동에 성공하면 이동하면서 소모한 연료 양의 두 배 충전
 * 승객을 목적지로 이동시킨 동시에 연료가 바닥나는 경우는 실패한 것으로 간주하지 않음
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

#define MAX_N 20
#define DIR_NUM 4

using namespace std;

constexpr int dx[DIR_NUM] = {1, 0, -1, 0};
constexpr int dy[DIR_NUM] = {0, -1, 0, 1};

int N, M;
int grid[MAX_N][MAX_N];  // 0은 빈칸, 1은 벽
int dist[MAX_N][MAX_N];

#if DEBUG
char state[MAX_N][MAX_N];
#endif

struct Position {
  int x, y;
};

struct Taxi {
  int fuel, x, y;
} taxi;

struct Passenger {
  int x, y, dst_x, dst_y;
};
Passenger passengers[MAX_N * MAX_N];

bool isInRange(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

void bfs() {
  memset(dist, 0, sizeof(dist));
  dist[taxi.y][taxi.x] = 1;
  queue<Position> q;
  q.push({taxi.x, taxi.y});
  while (!q.empty()) {
    Position cur = q.front();
    q.pop();

    for (int i = 0; i < DIR_NUM; ++i) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (isInRange(nx, ny) && !grid[ny][nx] && !dist[ny][nx]) {
        q.push({nx, ny});
        dist[ny][nx] = dist[cur.y][cur.x] + 1;
      }
    }
  }

#if DEBUG
  cout << "dist:" << endl;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << dist[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
#endif
}

int pickTarget() {
  bfs();

  int target_num = -1;
  tuple<int, int, int> best = { 2*N, N, N };
  for (int i = 0; i < M; ++i) {
    Passenger p = passengers[i];
    if (p.x == -1) {
      continue;
    }
    tuple<int, int, int> candi = { dist[p.y][p.x] - 1, p.y, p.x };
    if (candi < best) {
      best = candi;
      target_num = i;
    }
  }

#if DEBUG
  if (target_num == -1) {
    cout << "Something Wrong!" << endl;
  }
#endif

  return target_num;
}

void moveTaxi(int target_num) {
  Passenger& p = passengers[target_num];
#if DEBUG
  cout << "Before fuel: " << taxi.fuel << endl;
  state[p.y][p.x] = '.';
  state[taxi.y][taxi.x] = '.';
  state[p.dst_y][p.dst_x] = 'T';
#endif
  taxi.x = p.x;
  taxi.y = p.y;
  int p_dist = dist[p.y][p.x] - 1;
  if (p_dist < 0) {
    // Can not reach
    taxi.fuel = -1;
    return;
  }
  taxi.fuel -= p_dist;
  p.x = -1;
  if (taxi.fuel < 0) {
    return;
  }

  bfs();

  taxi.x = p.dst_x;
  taxi.y = p.dst_y;
  int goal_dist = dist[p.dst_y][p.dst_x] - 1;
  if (goal_dist < 0) {
    // Can not reach
    taxi.fuel = -1;
    return;
  }
  taxi.fuel -= goal_dist;
  if (taxi.fuel < 0) {
    return;
  }

  taxi.fuel += 2 * goal_dist;
#if DEBUG
  cout << "After fuel: " << taxi.fuel << endl;
#endif
}

void simulate() {
  int target_num = pickTarget();
  moveTaxi(target_num);
}

void input () {
  cin >> N >> M >> taxi.fuel;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> grid[y][x];
    }
  }
  cin >> taxi.y >> taxi.x;
  --taxi.y; --taxi.x;
  for (int i = 0; i < M; ++i) {
    Passenger& p = passengers[i];
    cin >> p.y >> p.x >> p.dst_y >> p.dst_x;
    --p.y; --p.x; --p.dst_y; --p.dst_x;
  }

#if DEBUG
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (grid[y][x]) {
        state[y][x] = 'x';
      } else {
        state[y][x] = '.';
      }
    }
  }
  state[taxi.y][taxi.x] = 'T';
  for (int i = 0; i < M; ++i) {
    Passenger& p = passengers[i];
    state[p.y][p.x] = '0' + i;
  }
#endif
}
void init() {
  memset(grid, 0, sizeof(grid));
#if DEBUG
  memset(state, 0, sizeof(state));
#endif
}

void solution() {
  init();
  input();

  int t = M;
  while (t--) {
    if (taxi.fuel < 0) {
      taxi.fuel = -1;
      break;
    }
#if DEBUG
  cout << "Current State:" << endl;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << state[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
#endif

    simulate();
  }

  cout << taxi.fuel << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-1-afternoon2.input", "r", stdin);
  freopen("2020-1-afternoon2.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }

  return 0;
}