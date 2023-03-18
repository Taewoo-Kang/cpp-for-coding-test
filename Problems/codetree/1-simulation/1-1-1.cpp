// 최고의 33위치
// 분류 - 격자 안에서 완전탐색

/**
 * 입력:
 * 첫번째 줄에는 N(3<=N<=20)
 * 두번째 줄부터 N개의 줄에 걸쳐 격자 정보(0: 동전x, 1: 동전o)
 * 
 * 출력:
 * NxN 격자를 벗어나지 않으면서 3x3 크기 격자 내에 들어올 수 있는 최대 동전의 수
*/

#include <iostream>
#include <cstring>

using namespace std;

int N;
int grid[20][20];

void init() {
  memset(grid, 0, sizeof(grid));
}

void solution() {
  init();

  cin >> N;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> grid[y][x];
    }
  }

  int ret = 0;
  for (int y = 0; y < N - 2; ++y) {
    for (int x = 0; x < N - 2; ++x) {
      int count = 0;
      for (int dy = 0; dy < 3; ++dy) {
        for (int dx = 0; dx < 3; ++dx) {
          if (grid[y + dy][x + dx] == 1) {
            ++count;
          }
        }
      }
      if (count > ret) {
        ret = count;
      }
    }
  }

  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-1-1.input", "r", stdin);
  freopen("1-1-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }
  return 0;
}