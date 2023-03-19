// 핀볼게임
// 분류 - 격자 안에서 단일 객체를 이동

/**
 * nxn 크기의 격자판에서 핀볼게임을 진행. 0은 빈공간, 1은 /모양 2는 \모양을 의미
 * 숫자가 1이나 2일 경우 구슬이 해당 위치로 진입했을 때 진행방향이 바뀌게 됨
 * 구슬은 단 하나만 이용하며, 4n개의 지점 중 한 곳에서 정해진 방향으로만 시작 가능
 * 격자판의 상태가 주어졌을 때, 시작점을 적절하게 선택하여 격자 밖으로 나오는 데까지 걸리는 시간이 최대로
*/

#include <iostream>
#include <cstring>

using namespace std;

int n;
int grid[102][102];

const int dx[] = { 0, 0, 1, -1 };
const int dy[] = { 1, -1, 0, 0 };

int convertDirection(int type, int dir) {
  if (type == 1) {
    if (dir == 0) {
      return 3;
    } else if (dir == 1) {
      return 2;
    } else if (dir == 2) {
      return 1;
    } else {
      return 0;
    }
  }

  if (dir == 0) {
    return 2;
  } else if (dir == 1) {
    return 3;
  } else if (dir == 2) {
    return 0;
  } else {
    return 1;
  }
}

bool isInsideGrid(int x, int y) {
  return x > 0 && x <= n && y > 0 && y <= n;
}

int play(int x, int y, int dir) {
  int play_time = 0;
  do {
    x = x + dx[dir];
    y = y + dy[dir];
    if (grid[y][x] != 0) {
      dir = convertDirection(grid[y][x], dir);
    }
    ++play_time;
    
  } while (isInsideGrid(x, y));
  return play_time;
}

void init() {
  memset(grid, 0, sizeof(grid));
}

void solution() {
  init();

  cin >> n;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y+1][x+1];
    }
  }

  int ret = 0;
  for (int dir = 0; dir < 4; ++dir) {
    for (int i = 1; i <= n; ++i) {
      int sx, sy;
      if (dir == 0) {
        sx = i;
        sy = 0;
      } else if (dir == 1) {
        sx = i;
        sy = n + 1;
      } else if (dir == 2) {
        sx = 0;
        sy = i;
      } else if (dir == 3) {
        sx = n + 1;
        sy = i;
      }
      int play_time = play(sx, sy, dir);
      if (play_time > ret) {
        ret = play_time;
      }
    }
  }

  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-4-7.input", "r", stdin);
  freopen("1-4-7.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}