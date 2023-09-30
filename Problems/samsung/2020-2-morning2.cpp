// 마법사 상어와 파이어볼
// 삼성 2020년도 하반기 오전 2번
// 출처: https://www.acmicpc.net/problem/20056

/**
 * 마법사 상어가 NxN 크기 격자에 파이어볼 M개 발사
 * 가장 처음에 파이어볼은 각자 위치에서 이동을 대기
 * i번 파이어볼의 위치는 (r_i, c_i), 질량 m_i, 방향 d_i, 속력 s_i
 * 격자 행/열은 1~N, 1번과 N번은 서로 연결됨
 * 
 * 1. 모든 파이어볼이 방향 d로 속력 s칸 만큼 이동
 * 2. 이동이 모두 끝난 뒤 2개 이상의 파이어볼 있는 칸
 * 2-1. 같은 칸의 파이어볼은 모두 하나로 합쳐짐
 * 2-2. 파이어볼은 4개로 나누어짐
 * 2-3. 나누어진 파이어볼의
 *      질량 = 합 / 5
 *      속력 = 합 / 갯수
 *      합쳐지는 파이어볼 방향이 모두 홀수 or 짝수 = 0,2,4,6 else 1,3,5,7
 * 2-4. 질량이 0인 파이어볼은 소멸
 * 
 * K번 명령 후 남아있는 파이어볼 질량의 합?
*/

#define DEBUG 1

#include <iostream>
#include <queue>

#define MAX_N 50
#define DIR_NUM 8

using namespace std;

constexpr int dr[DIR_NUM] = { -1, -1, 0, 1, 1, 1, 0, -1};
constexpr int dc[DIR_NUM] = { 0, 1, 1, 1, 0, -1, -1, -1};
constexpr int nd[2][4] = {{1, 3, 5, 7}, {0, 2, 4, 6}};

int N, M, K;

struct Fire {
  int r, c, m, s, d;
};
queue<Fire> grid[MAX_N][MAX_N];
queue<Fire> new_grid[MAX_N][MAX_N];

void moveFire() {

  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      queue<Fire>& q = grid[y][x];
      int size = q.size();
      while (size--) {
        Fire f = q.front();
        q.pop();

        f.r = (f.r + dr[f.d] * f.s + f.s * N) % N;
        f.c = (f.c + dc[f.d] * f.s + f.s * N) % N;
        new_grid[f.r][f.c].push(f);
      }
    }
  }

  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      while (!new_grid[y][x].empty()) {
        grid[y][x].push(new_grid[y][x].front());
        new_grid[y][x].pop();
      }
    }
  }
}

void splitFire() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (grid[y][x].size() > 1) {
#if DEBUG
        cout << "Crash (" << x << ", " << y << ")!" << endl;
#endif
        int nm = 0;
        int ns = 0;
        queue<Fire>& q = grid[y][x];
        int d = q.front().d % 2;
        bool same = true;
        int size = q.size();
        for (int i = 0; i < size; ++i) {
          Fire f = q.front();
#if DEBUG
        cout <<"m: " << f.m << ", s: " << f.s << endl;
#endif
          q.pop();

          nm += f.m;
          ns += f.s;
          if (same) {
            same = f.d % 2 == d;
          }
        }
        nm /= 5;
        ns /= size;
#if DEBUG
        cout <<"nm: " << nm << ", ns: " << ns << ", same: " << same << endl;
#endif

        if (nm) {
          for (int i = 0; i < 4; ++i) {
            q.push({y, x, nm, ns, nd[same][i]});
          }
        }
      }
    }
  }
}

void simulate() {
  moveFire();
  splitFire();
}

void input() {
  cin >> N >> M >> K;
  for (int i = 0; i < M; ++i) {
    int r, c, m, s, d;
    cin >> r >> c >> m >> s >> d;
    --r; --c;
    grid[r][c].push({r, c, m, s, d});
  }
}

void init() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      grid[y][x] = queue<Fire>();
    }
  }
}

void solution() {
  init();
  input();

  while (K--) {
#if DEBUG
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (grid[y][x].empty()) cout << '.';
      else cout << grid[y][x].front().m;
    }
    cout << endl;
  }
  cout << endl;
#endif
    simulate();
  }

  int ans = 0;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      while (!grid[y][x].empty()) {
        ans += grid[y][x].front().m;
        grid[y][x].pop();
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-2-morning2.input", "r", stdin);
  freopen("2020-2-morning2.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}