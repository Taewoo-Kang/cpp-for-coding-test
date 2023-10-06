// 어항 정리
// 삼성 2021년도 하반기 오후 2번
// 출처: https://www.acmicpc.net/problem/23291

/**
 * 정육면체 모양 어항, 한 변의 길이는 모두 1, 어항은 N개
 * 어항은 가장 처음 일렬로 바닥에 놓여져 있고, 어항에는 물고기가 한 마리 이상 들어있음
 * 1. 물고기의 수가 가장 적은 어항에 물고기 한 마리 넣음(여러 개면 최소인 어항 모두에 넣음)
 * 2. 가장 왼쪽 어항을 그 오른쪽 어항 위에 올림
 * 3. 쌓여있는 어항을 모두 공중 부양시킨 다음, 시계방향으로 90도 회전해서 쌓음
 * 3-1. 공중 부양시킨 어항 중 가장 오른쪽에 있는 어항의 아래에 어항이 없으면 하지 않고 종료
 * 4. 모든 인접한 두 어항에 대해서 물고기 수 차이를 구해서 5로 나눈 몫 d만큼 적은 곳으로 보냄(모든 인접한 칸에 대해서 동시에 발생)
 * 5. 가장 왼쪽 어항부터 아래에 있는 어항부터 가장 위에 있는 어항까지 순서대로 바닥에 놓음
 * 6. 가운데를 중심으로 왼쪽 N/2개를 공중 부양시켜 전체를 180도 회전 시킨 다음 오른쪽 N/2의 위에 놓는 작업 두 번 반복
 * 7. 다시 4번의 물고기 조절 작업을 수행하고 5번의 바닥에 일렬로 놓는 작업을 수행
 * 
 * 물고기가 가장 많이 들어있는 어항과 가장 적게 들어있는 어항의 물고기 수 차이가 K 이하가 되려면 어항을 몇 번 정리해야?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

#define MAX_N 100
#define MAX_NUM 10000

using namespace std;

constexpr int dx[4] = {-1, 0};
constexpr int dy[4] = {0, 1};

int N, K;
int grid[MAX_N][MAX_N];
int row, col;

#if DEBUG
void dPrintGrid() {
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cout << grid[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

bool isInRange(int x, int y) {
  return x >= 0 && x < col && y >= 0 && y < row;
}

void insertFish() {
  vector<int> min_pos;
  int min_num = MAX_NUM;
  for (int i = 0; i < N; ++i) {
    if (grid[0][i] < min_num) {
      min_num = grid[0][i];
      min_pos.clear();
      min_pos.push_back(i);
    } else if (grid[0][i] == min_num) {
      min_pos.push_back(i);
    }
  }

  for (int pos : min_pos) {
    ++grid[0][pos];
  }
}

bool rollBowl(int i) {
  int temp[MAX_N][MAX_N] = {0,};

  int num = i/2 + 1;
  for (int y = 0; y < row; ++y) {
    for (int x = 0; x < num; ++x) {
      temp[x][row-1-y] = grid[y][x];
    }
  }

  int ncol = col - num;
  for (int x = 0; x < ncol; ++x) {
    temp[num][x] = grid[row-1][num + x];
  }
  int nrow = row + (i+1) % 2;

  cout << nrow << ' ' << ncol << endl;
  if (row > ncol) {
    return true;
  }
  memcpy(grid, temp, sizeof(grid));
  row = nrow; col = ncol;
  return false;
}

void devideFish() {
  int temp[MAX_N][MAX_N] = {0,};
  memcpy(temp, grid, sizeof(temp));

  for (int y = 0; y < row; ++y) {
    for (int x = 0; x < col; ++x) {
      if (!temp[y][x]) {
        continue;
      }

      for (int i = 0; i < 2; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!isInRange(nx, ny) || !temp[ny][nx]) {
          continue;
        }

        int d = (temp[y][x] - temp[ny][nx]) / 5;
        grid[y][x] -= d;
        grid[ny][nx] += d;
      }
    }
  }
}

void straightBowl() {
  int temp[MAX_N][MAX_N] = {0,};
  int idx = 0;
  for (int x = 0; x < col; ++x) {
    for (int y = row-1; y >= 0; --y) {
      if (grid[y][x]) {
        temp[0][idx] = grid[y][x];
        ++idx;
      }
    }
  }

  memcpy(grid, temp, sizeof(grid));
  row = 1; col = N;
}

void foldBowl() {
  int temp[MAX_N][MAX_N] = {0,};

  col /= 2;
  for (int y = 0; y < row; ++y) {
    for (int x = 0; x < col; ++x) {
      temp[y][x] = grid[row-1-y][col-1-x];
    }
  }

  for (int y = 0; y < row; ++y) {
    for (int x = 0; x < col; ++x) {
      temp[row+y][x] = grid[y][col+x];
    }
  }
  row *= 2;

  memcpy(grid, temp, sizeof(grid));
}

void simulation() {
  insertFish();

  bool done = false;
  int num = 0;
  while (!done) {
    done = rollBowl(num);
#if DEBUG
  cout << "After Roll:" << endl;
  dPrintGrid();
#endif
    ++num;
  }

  devideFish();
#if DEBUG
  cout << "After Devide:" << endl;
  dPrintGrid();
#endif

  straightBowl();
#if DEBUG
  cout << "After Straight:" << endl;
  dPrintGrid();
#endif

  foldBowl();  
#if DEBUG
  cout << "After Fold:" << endl;
  dPrintGrid();
#endif
  foldBowl();  
#if DEBUG
  cout << "After Fold:" << endl;
  dPrintGrid();
#endif

  devideFish();
#if DEBUG
  cout << "After Divide:" << endl;
  dPrintGrid();
#endif

  straightBowl();
#if DEBUG
  cout << "After Straight:" << endl;
  dPrintGrid();
#endif
}

void input() {
  cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    cin >> grid[0][i];
  }
  row = 1; col = N;
}

void init() {
  memset(grid, 0, sizeof(grid));
  row = 0; col = 0;
}

bool checkDone() {
  int max_num = 0;
  int min_num = MAX_NUM;
  for (int i = 0; i < N; ++i) {
    max_num = max(max_num, grid[0][i]);
    min_num = min(min_num, grid[0][i]);
  }

  return max_num - min_num <= K;
}

void solution() {
  init();
  input();

  int ans = 0;
  bool done = false;
  while (!done) {
    simulation();
    done = checkDone();
    ++ans;
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2021-2-afternoon2.input", "r", stdin);
  freopen("2021-2-afternoon2.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}