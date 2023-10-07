// 예술성
// 삼성 2022년도 상반기 오전 2번
// 출처: https://www.codetree.ai/training-field/frequent-problems/problems/artistry?&utm_source=clipboard&utm_medium=text

/**
 * n x n 크기의 격자 그림, 각 칸의 색깔을 1~10 숫자로 표현
 * 동일한 숫자가 상하좌우로 인접해있을 경우 동일한 그룹
 * 예술 점수는 모든 그룹 쌍의 조화로움의 합으로 정의
 * 그룹 a와 b의 조화로움 = (a에 속한 칸 수 + b에 속한 칸 수) x (a를 이루고 있는 값) x (b를 이루고 있는 값) x (a와 b가 서로 맞닿아 있는 변의 수)
 * 
 * 초기 예술 점수를 구한 뒤 그림에 대한 회전
 * 정중앙을 기준으로 십자가 모양은 반시계 방향 90도 회전, 이외의 4개 영역은 각각 시계방향 90도 회전
 * 초기 예술 점수와 회전을 1, 2, 3회 이후 예술 점수를 모두 합한 값?
*/

#define DEBUG 0

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

#define MAX_N 29

using namespace std;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, -1, 0, 1};

int n;
int grid[MAX_N][MAX_N];

struct PicGroup {
  int num;
  vector<pair<int, int>> pos;

  PicGroup(int n) : num(n) {}
};

#if DEBUG
void dPrintGroups(const vector<PicGroup>& groups) {
  for (PicGroup group : groups) {
    for (pair<int, int> elem : group.pos) {
      cout << '(' << elem.first << ", " << elem.second << ") ";
    }
    cout << endl;
  }
}

void dPrintGrid() {
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cout << grid[y][x] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
#endif

void input() {
  cin >> n;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
}

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void groupPictures(vector<PicGroup>& groups) {
  bool visited[MAX_N][MAX_N] = {false,};
  queue<pair<int, int>> q;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      if (isInRange(x, y) && !visited[y][x]) {
        visited[y][x] = true;
        q.push({x, y});
        int num = grid[y][x];
        PicGroup group(num);
        group.pos.push_back({x, y});
        while (!q.empty()) {
          pair<int, int> cur = q.front();
          q.pop();
          for (int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if (isInRange(nx, ny) && !visited[ny][nx] && grid[ny][nx] == num) {
              q.push({nx, ny});
              visited[ny][nx] = true;
              group.pos.push_back({nx, ny});
            }
          }
        }
        groups.push_back(group);
      }
    }
  }
}

int getAdjacency(const PicGroup& a, const PicGroup& b) {
  int ret = 0;
  for (pair<int, int> pos1 : a.pos) {
    for (pair<int, int> pos2 : b.pos) {
      if (abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second) == 1) {
        ++ret;
      }
    }
  }

  return ret;
}

int calcScore() {
  vector<PicGroup> groups;
  groupPictures(groups);

#if DEBUG
  // dPrintGroups(groups);
#endif

  int total = 0;
  for (int i = 0; i < groups.size()-1; ++i) {
    for (int j = i+1; j < groups.size(); ++j) {
      PicGroup a = groups[i];
      PicGroup b = groups[j];
      int score = (a.pos.size() + b.pos.size()) * a.num * b.num * getAdjacency(a, b);
      total += score;
    }
  }

  return total;
}

void rotateSmall(int sx, int sy, int temp[MAX_N][MAX_N]) {
  int cenx = n / 2;
  int ceny = n / 2;
  for (int yy = 0; yy < ceny; ++yy) {
    for (int xx = 0; xx < cenx; ++xx) {
      grid[yy + sy][xx + sx] = temp[cenx-1-xx + sy][yy + sx];
    } 
  }
}

void rotatePicture() {
  int temp[MAX_N][MAX_N] = {0,};
  memcpy(temp, grid, sizeof(grid));

  int cenx = n / 2;
  int ceny = n / 2;
  for (int y = 0; y < n; ++y) {
    grid[n - 1 - cenx][y] = temp[y][cenx];
  }
  for (int x = 0; x < n; ++x) {
    grid[n - 1 - x][ceny] = temp[ceny][x];
  }

  rotateSmall(0, 0, temp);
  rotateSmall(cenx+1, 0, temp);
  rotateSmall(0, ceny+1, temp);
  rotateSmall(cenx+1, ceny+1, temp);
}

void solution() {
  init();
  input();
  
  int ans = 0;
  ans += calcScore();
  for (int i = 0; i < 3; ++i) {
    rotatePicture();
#if DEBUG
    dPrintGrid();
#endif
    ans += calcScore();
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2022-1-morning2.input", "r", stdin);
  freopen("2022-1-morning2.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}