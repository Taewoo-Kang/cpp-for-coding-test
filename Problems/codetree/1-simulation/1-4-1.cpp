// 숫자가 더 큰 인접한 곳으로 이동
// 분류 - 격자 안에서 단일 객체를 이동

/**
 * 1이상 100이하의 숫자로 이루어진 nxn 크기의 격자판
 * 상하좌우로 인접한 곳에 있는 숫자들 중 현재 위치에 있는 숫자보다 더 큰 위치로 이동
 * 만약 그러한 위치가 여러 개 있는 경우 상하좌우 순서대로 우선순위를 매겨 이동
 * 더 이상 움직일 수 없을 때 방문한 숫자를 순서대로 출력
 * 
 * 입력:
 * 첫번째 줄에 격자의 크기를 나타내는 n과 시작 위치를 나타내는 r, c값이 공백을 사이에 두고 주어짐
 * 두번째 줄부터는 n개의 줄에 걸쳐 각 행에 해당하는 숫자가 공백을 사이에 두고 주어짐
 * 1 <= r,c <= n <= 100
 * 
 * 출력:
 * 첫번째 줄에 시작 위치로부터 움직임이 종료될 때까지 방문한 격자에 적혀있는 숫자들을 공백을 사이에 두고 출력
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, r, c;
int grid[100][100];
queue<int> q;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

bool move() {
  for (int i = 0; i < 4; ++i) {
    int x = c + dx[i];
    int y = r + dy[i];
    if (x < 0 || x >= n || y < 0 || y >= n) {
      continue;
    }
    if (grid[y][x] > grid[r][c]) {
      c = x;
      r = y;
      q.push(grid[y][x]);
      return true;
    }
  }
  return false;
}

void init() {
  memset(grid, 0, sizeof(grid));
  q = queue<int>();
}

void solution() {
  init();

  cin >> n >> r >> c;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }

  --r;
  --c;
  q.push(grid[r][c]);
  while (move()) {}
  
  while (!q.empty()) {
    cout << q.front() << ' ';
    q.pop();
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-4-1.input", "r", stdin);
  freopen("1-4-1.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }

  return 0;
}