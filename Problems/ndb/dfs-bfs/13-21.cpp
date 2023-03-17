// 인구 이동 - 삼성 기출
// 출처: https://www.acmicpc.net/problem/16234

/**
 * NxN 크기 땅, r행 c열에 있는 나라에는 A[r][c]명 살고 있음
 * 인구 이동은 하루에 아래같이 진행되고, 더 이상 인구 이동이 없을 때까지 지속
 * 1. 국경선을 공유하는 두 나라의 인구 차이가 L명 이상, R명 이하 -> 국경선 하루동안 염
 * 2. 위 조건에 따라 열어야하는 국경선이 모두 열리면 인구 이동 시작
 * 3. 국경선이 열려 있어 이동 가능하면 연합
 * 4. 연합을 이루고 있는 각 칸의 인구 수는 (연합 인구 수) / (연합을 이루는 칸의 갯수)가 되며 소수점은 버림
 * 5. 연합을 해체하고, 모든 국경선을 닫는다.
 * 
 * 입력:
 * 첫째 줄에 N, L, R (1<=N<=50, 1<=L<=R<=100)
 * 둘째 줄부터 각 나라의 인구 수 0<=A[r][c]<=100
 * 인구 이동이 발생하는 일수는 2,000번보다 작거나 같은 입력만
 * 
 * 출력:
 * 인구 이동이 며칠동안 발생하는지 첫째 줄에 출력
*/

#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

int N, L, R;
int nation[50][50];
int visited[50][50];
int ret;

struct Position {
  int x;
  int y;
};
queue<Position> q;
int population;

const int dx[] = { 0, 0, -1, 1};
const int dy[] = { 1, -1, 0, 0};

void dfs(int sx, int sy) {
  if (visited[sy][sx] == 0) {
    visited[sy][sx] = 1;
    bool open = false;
    for (int i = 0; i < 4; ++i) {
      int nx = sx + dx[i];
      int ny = sy + dy[i];
      int diff = abs(nation[ny][nx] - nation [sy][sx]);
      if (nx >= 0 && nx < N && ny >= 0 && ny < N
            && diff >= L && diff <= R) {
        open = true;
        dfs(nx, ny);
      }
    }
    if (open) {
      q.push({sx, sy});
      population += nation[sy][sx];
    }
  } 
}

bool day() {
  bool moved = false;
  for (int r = 0; r < N; ++r) {
    for (int c =0; c < N; ++c) {
      population = 0;
      dfs(c, r);
      int new_population = population / q.size();
      if (!q.empty()) {
        moved = true;
      }
      while (!q.empty()) {
        Position cur = q.front();
        q.pop();
        nation[cur.y][cur.x] = new_population;
      }
    }
  }

  if (moved) {
    ++ret;
  }
  memset(visited, 0, sizeof(visited));
  return moved;
}

void init() {
  memset(nation, 0, sizeof(nation));
  memset(visited, 0, sizeof(visited));
  ret = 0;
}

void solution() {
  init();

  cin >> N >> L >> R;
  for (int r = 0; r < N; ++r) {
    for (int c =0; c < N; ++c) {
      cin >> nation[r][c];
    }
  }

  while (day());
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("13-21.input", "r", stdin);
  freopen("13-21.output", "w", stdout);
  for (int i = 0; i < 5; ++i) {
    solution();
  }
  return 0;
}