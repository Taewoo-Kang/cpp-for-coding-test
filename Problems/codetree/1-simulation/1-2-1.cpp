// 컨베이어 벨트
// 분류 - 격자 안에서 밀고 당기기

/**
 * 시계 방향으로 한 칸씩 회전하는 컨베이어 벨트
 * 위 아래로 n개씩 총 2n개의 숫자가 두 줄로 적혀있고, 1초에 한 칸씩 움직임
 * t초 후 컨베이어 벨트 숫자들의 상태 출력
 * 
 * 입력:
 * 첫번째 줄에는 n과 t가 공백을 사이에 두고 주어짐 (1<=n<=200, 1<=t<=1,000)
 * 두번째 줄에는 윗 변에 있는 초기 n개의 숫자들이 공백을 사이에 두고 주어짐
 * 세번째 줄에는 아랫 변에 있는 초기 n개의 숫자들이 공백을 사이에 두고 주어짐
 * 숫자는 각 변마다 숫자가 올바르게 보이는 방향에서 봤을 때 왼쪽에서 오른쪽 순으로 주어짐
 * 주어지는 숫자는 1 이상 9 이하
 * 
 * 출력:
 * t초 후 컨베이어 벨트에 놓여있는 숫자들의 상태 출력
 * 첫번째 줄에는 윗 변에 있는 n개의 숫자들을 공백을 사이에 두고 출력
 * 두번째 줄에는 아랫 변에 있는 n개의 숫자들을 공백을 사이에 두고 출력
*/

#include <iostream>
#include <cstring>

using namespace std;

int n, t;
int grid[400];

void move() {
  int last = grid[2*n - 1];
  for (int i = 2*n - 1; i > 0; --i) {
    grid[i] = grid[i - 1];
  }
  grid[0] = last;
}

void init() {
  memset(grid, 0, sizeof(grid));
}

void solution() {
  init();

  cin >> n >> t;
  for (int i = 0; i < 2 * n; ++i) {
    cin >> grid[i];
  }

  for (int i = 0; i < t; ++i) {
    move();
  }

  for (int i = 0; i < 2 * n; ++i) {
    cout << grid[i] << ' ';
    if (i == n - 1) {
      cout << '\n';
    }
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-2-1.input", "r", stdin);
  freopen("1-2-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}