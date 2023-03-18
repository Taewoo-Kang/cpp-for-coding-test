// 양수 직사각형의 최대 크기
// 분류 - 격자 안에서 완전탐색

/**
 * nxm 크기의 2차원 영역의 각 위치에 정수 값, 이 영역 안에서 가능한 양수 직사각형 중 최대 크기
 * 양수 직사각형은 직사각형 내에 있는 숫자들이 전부 양수인 직사각형
 * 
 * 입력:
 * 첫번째 줄에는 n과 m이 공백을 사이에 두고 주어짐(1<=n,m<=20)
 * 두번째 줄부터 n+1번째 줄까지 각 행의 숫자가 공백을 사이에 두고 주어짐(-1,000<=정수 값<=1,000)
 * 
 * 출력:
 * 모든 값이 양수로만 이루어져 있는 직사각형 중 최대 크기를 출력
 * 그러한 직사각형이 없다면 -1 출력
*/

#include <iostream>
#include <cstring>

using namespace std;

int n, m;
int grid[20][20];

int calcArea(int sx, int sy, int ex, int ey) {
  for (int y = sy; y <= ey; ++y) {
    for (int x = sx; x <= ex; ++x) {
      if (grid[y][x] < 0) {
        return -1;
      }
    }
  }
  return (ex - sx + 1) * (ey - sy + 1);
}

void init() {
  memset(grid, 0, sizeof(grid));
}

void solution() {
  init();

  cin >> n >> m;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < m; ++x) {
      cin >> grid[y][x];
    }
  }

  int ret = -1;
  for (int sy = 0; sy < n; ++sy) {
    for (int sx = 0; sx < m; ++sx) {
      for (int ey = sy; ey < n; ++ey) {
        for (int ex = sx; ex < m; ++ex) {
          int area = calcArea(sx, sy, ex, ey);
          if (area > ret) {
            ret = area;
          }
        }
      }
    }
  }
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-1-7.input", "r", stdin);
  freopen("1-1-7.output", "w", stdout);
  for (int i = 0; i < 5; ++i) {
    solution();
  }

  return 0;
}