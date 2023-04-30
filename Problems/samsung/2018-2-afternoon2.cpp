// 아기 상어
// 출처: https://www.acmicpc.net/problem/16236

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

constexpr int MAX_SIZE = 20;
constexpr int INF = 987654321;

int N;
int grid[MAX_SIZE][MAX_SIZE];

struct Position {
  int x, y;
};

struct Shark {
  int size;
  int ate;
  Position pos;

  Shark() {
    size = 2;
    ate = 0;
  }
} shark;

struct cmp {
  bool operator() (const Position& lhs, const Position& rhs) {
    if (lhs.y == rhs.y) {
      return lhs.x > rhs.x;
    }
    return lhs.y > rhs.y;
  }
};

// 상좌우하
constexpr int dx[] = {0, -1, 1, 0};
constexpr int dy[] = {-1, 0, 0, 1};

void eatFish(int x, int y) {
  // cout << "Eat fish at (" << x << ", " << y << ")\n";
  grid[y][x] = 0;
  shark.pos.x = x;
  shark.pos.y = y;
  shark.ate++;
  if (shark.ate == shark.size) {
    shark.ate = 0;
    shark.size++;
  }
}

bool canEat(int x, int y) {
  return grid[y][x] > 0 && grid[y][x] < shark.size;
}

bool canMove(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N
         && grid[y][x] <= shark.size;
}

int moveShark() {
  int step[MAX_SIZE][MAX_SIZE] = { 0, };
  step[shark.pos.y][shark.pos.x] = 1;
  queue<Position> q;
  q.push(shark.pos);
  priority_queue<Position, vector<Position>, cmp> pq;
  int min = INF;
  while (!q.empty()) {
    int x = q.front().x;
    int y = q.front().y;
    q.pop();
    if (step[y][x] > min) {
      eatFish(pq.top().x, pq.top().y);
      return step[y][x] - 1;
    }
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (!canMove(nx, ny)) {
        continue;
      }
      if (canEat(nx, ny)) {
        pq.push({nx, ny});
        min = step[y][x];
      }
      if (step[ny][nx] == 0) {
        step[ny][nx] = step[y][x] + 1;
        q.push({nx, ny});
      }
    }
  }

  return 0;
}

int simulate() {
  int ret = 0;
  while (int t = moveShark()) {
    ret += t;
  }

  return ret;
}

void input() {
  cin >> N;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> grid[y][x];
      if (grid[y][x] == 9) {
        shark.pos.x = x;
        shark.pos.y = y;
        grid[y][x] = 0;
      }
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  shark = Shark();
}

void solution() {
  init();

  input();

  int t = simulate();
  cout << t << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2018-2-afternoon2.input", "r", stdin);
  freopen("2018-2-afternoon2.output", "w", stdout);
  for (int i = 0; i < 6; ++i) {
    solution();
  }

  return 0;
}