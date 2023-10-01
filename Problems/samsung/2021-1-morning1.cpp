// 상어 초등학교
// 삼성 2021년도 상반기 오전 1번
// 출처: https://www.acmicpc.net/problem/21608

/**
 * NxN 크기 교실, 학생은 1~N^2번까지 번호
 * 학생의 순서를 정했고, 각 학생이 좋아하는 학생 4명도 조사
 * 한 칸에는 한 명만 자리할 수 있고, |r1-r2| + |c1-c2| = 1을 만족하는 두 칸이 인접하다고 함
 * 
 * 1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정함
 * 2. 1을 만족하는 칸이 여러 개이면, 그 중 비어있는 칸이 가장 많은 칸
 * 3. 2를 만족하는 칸도 여러 개이면 행/열 순으로 가장 작은 칸으로
 * 
 * 학생의 만족도는 자리 배치가 모두 끝난 후 그 학생과 인접한 칸에 앉은 좋아하는 학생의 수
 * 0이면 0, 1이면 1, 2이면 10, 3이면 100, 4이면 1000
 * 
 * 학생의 만족도 총합?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <tuple>
#include <unordered_set>
#include <cmath>

#define MAX_N 20

using namespace std;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, -1, 0, 1};

int N;
int grid[MAX_N][MAX_N];
struct Student {
  int num, x, y;
  unordered_set<int> preference;
};
Student order[MAX_N * MAX_N];

bool isInRange(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

void input() {
  cin >> N;
  for (int i = 0; i < MAX_N * MAX_N; ++i) {
    cin >> order[i].num;
    for (int j = 0; j < 4; ++j) {
      int n;
      cin >> n;
      order[i].preference.insert(n);
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  for (int i = 0; i < MAX_N * MAX_N; ++i) {
    order[i].preference.clear();
  }
}

pair<int, int> findBestPosition(int num) {
  unordered_set<int>& p = order[num].preference;
  tuple<int, int, int, int> best = {0, 0, -N, -N};
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (grid[y][x]) {
        continue;
      }

      int like = 0;
      int empty = 0;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!isInRange(nx, ny)) {
          continue;
        }

        if (!grid[ny][nx]) {
          ++empty;
        } else if (p.find(grid[ny][nx]) != p.end()) {
          ++like;
        }
      }

      tuple<int, int, int, int> candi = {like, empty, -y, -x};
      if (best < candi) {
        best = candi;
      }
    }
  }
  return {-get<3>(best), -get<2>(best)};
}

int calcSatisfaction(int num) {
  unordered_set<int>& p = order[num].preference;
  int x = order[num].x;
  int y = order[num].y;

  int cnt = 0;
  for (int i = 0; i < 4; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (!isInRange(nx, ny)) {
      continue;
    }

    if (p.find(grid[ny][nx]) != p.end()) {
      ++cnt;
    }
  }

  if (cnt == 0) {
    return 0;
  }
  return pow(10, cnt - 1);
}

void solution() {
  init();
  input();

  for (int i = 0; i < N*N; ++i) {
    pair<int, int> pos = findBestPosition(i);
    order[i].x = pos.first;
    order[i].y = pos.second;
    grid[pos.second][pos.first] = order[i].num;
  }

#if DEBUG
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << grid[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
#endif

  int ans = 0;
  for (int i = 0; i < N*N; ++i) {
    ans += calcSatisfaction(i);
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-1-morning1.input", "r", stdin);
  freopen("2021-1-morning1.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}