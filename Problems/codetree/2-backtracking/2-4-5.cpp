// 수들 중 최솟값 최대화하기

/**
 * 크기가 n x n인 2차원 격자 내 각 칸에 정수값이 적혀 있다.
 * 정확히 n개의 칸에 색칠을 하여 각 행과 열에 정확히 1개의 칸만 색칠되도록
 * 이 때 색칠된 칸에 적힌 수들 중 최솟값이 최대가 되도록 하는 프로그램
 * 
 * 입력:
 * 첫번째 줄에 n (1 <= n <= 10)
 * 두번째 줄부터 n개의 줄에 걸쳐 각 줄에 n개씩의 정수가 공백을 두고 주어짐
 * 1 <= 정수 <= 10,000
 * 
 * 출력:
 * 조건을 만족하는 경우 중 색칠된 칸에 적힌 수들의 최솟값이 될 수 있는 값들 중 최대를 출력
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n;
int ret;
int grid[10][10];
int visited[10];

struct Position {
  int x;
  int y;
};
vector<Position> selected;

void init() {
  memset(grid, 0, sizeof(grid));
  memset(visited, 0, sizeof(visited));
  ret = 0;
}

void recursion(int start_y) {
  if (selected.size() == n) {
    int min_val = 0x7fffffff;
    for (int i = 0; i < n; ++i) {
      int val = grid[selected[i].y][selected[i].x];
      if (val < min_val) {
        min_val = val;
      }
    }
    if (min_val > ret) {
      ret = min_val;
    }
    return;
  }

  for (int y = start_y; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (visited[x]) {
        continue;
      }
      visited[x] = true;
      selected.push_back({x, y});
      recursion(y + 1);
      selected.pop_back();
      visited[x] = false;
    }
  }
}

void solution() {
  init();

  cin >> n;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }

  recursion(0);

  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-4-5.input", "r", stdin);
  freopen("2-4-5.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}