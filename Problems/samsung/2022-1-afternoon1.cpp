// 꼬리잡기놀이
// 삼성 2022년도 상반기 오후 1번
// 출처: https://www.codetree.ai/training-field/frequent-problems/problems/tail-catch-play?&utm_source=clipboard&utm_medium=text

/**
 * n x n 격자에서 꼬리잡기놀이 진행
 * 3명 이상이 한 팀, 모든 사람들은 자신의 앞 사람의 허리를 잡고 움직임, 맨 앞은 머리사람, 맨 뒤는 꼬리사람
 * 각 팀은 주어진 이동 선을 따라서만 이동, 이동선은 끝이 이어져 있으며 각 팀의 이동선은 서로 겹치지 않음
 * 
 * 한 라운드 진행
 * 1. 각 팀은 머리사람을 따라서 한 칸 이은
 * 2. 각 라운드마다 공이 정해진 선을 따라 던져짐
 * 3. 공이 던져질 때 최초에 만나게 되는 사람만이 공을 얻어 점수를 얻게 됨
 * 3-1. 머리사람을 시작으로 팀 내에서 k번째 사람이면 k제곱만큼 점수 얻음
 * 3-2. 공을 획득한 팀은 방향을 뒤집어 머리 사람과 꼬리 사람이 바뀜
 * 
 * 각 팀이 획득한 점수의 총합?
*/

#define DEBUG 1

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAX_N 20

using namespace std;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, -1, 0, 1};

int n, m, k;
int grid[MAX_N][MAX_N];  // 0 빈칸, 1 머리, 2 중간, 3 꼬리, 4 이동선

struct Person {
  int x, y;
};
vector<vector<Person>> groups;

#if DEBUG
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

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void moveForward(Person& person, int temp[MAX_N][MAX_N]) {
  for (int i = 0; i < 4; ++i) {
    int nx = person.x + dx[i];
    int ny = person.y + dy[i];
    if (!isInRange(nx, ny)) {
      continue;
    }

    // grid에 이동한 위치를 판별하기 위해 값을 5로 임시 적용
    switch (temp[person.y][person.x]) {
      case 1: {
        if (temp[ny][nx] == 4 || temp[ny][nx] == 3) {
          grid[ny][nx] = temp[person.y][person.x];
          grid[person.y][person.x] = 5;
          person.x = nx;
          person.y = ny;
          return;
        }
        break;
      }
      case 2: {
        if (grid[ny][nx] == 5) {
          grid[ny][nx] = temp[person.y][person.x];
          grid[person.y][person.x] = 5;
          person.x = nx;
          person.y = ny;
          return;
        }
        break;
      }
      case 3: {
        if (grid[ny][nx] == 5) {
          grid[ny][nx] = temp[person.y][person.x];
          if (grid[person.y][person.x] != 1) {
            grid[person.y][person.x] = 4;
          }
          person.x = nx;
          person.y = ny;
          return;
        }
        break;
      }
      default:
        break;
    }
  }
}

int throwBall(int round) {
  int ret = 0;

  int dir = (round / n) % 4;
  int num = round % n;
  int cx, cy;
  switch (dir) {
    case 0: {
      cx = -1;
      cy = num;
      break;
    }
    case 1: {
      cx = num;
      cy = n;
      break;
    }
    case 2: {
      cx = n;
      cy = n-1 - num;
      break;
    }
    case 3: {
      cx = n-1 - num;
      cy = -1;
      break;
    }
  }

  while (1) {
    cx += dx[dir];
    cy += dy[dir];
    if (!isInRange(cx, cy)) {
      break;
    }
    if (grid[cy][cx] >= 1 && grid[cy][cx] <= 3) {
      for (vector<Person>& group : groups) {
        for (int i = 0; i < group.size(); ++i) {
          if (group[i].x == cx && group[i].y == cy) {
            ret = (i+1) * (i+1);
            reverse(group.begin(), group.end());
            grid[group[0].y][group[0].x] = 1;
            grid[group[group.size()-1].y][group[group.size()-1].x] = 3;
#if DEBUG
      cout << "Hit: " << cx << ' ' << cy << endl;
      cout << "Score: " << ret << endl;
#endif
            return ret;
          }
        }
      }
    }
  }

  return ret;
}

int simulation(int round) {
  int ret = 0;
  int temp[MAX_N][MAX_N] = {0,};
  memcpy(temp, grid, sizeof(temp));
  for (vector<Person>& group : groups) {
    for (Person& person : group) {
      moveForward(person, temp);
    }
  }

#if DEBUG
  dPrintGrid();
#endif

  ret = throwBall(round);
  return ret;
}

void makeGroup() {
  bool visited[MAX_N][MAX_N] = {false,};
  for (vector<Person>& vec : groups) {
    Person cur = vec[0];
    Person last;
    visited[cur.y][cur.x] = true;
    bool cont = true;
    while (cont) {
      cont = false;
      for (int i = 0; i < 4; ++i) {
        int nx = cur.x + dx[i];
        int ny = cur.y + dy[i];
        if (isInRange(nx, ny) && !visited[ny][nx] && grid[ny][nx] == 2) {
          visited[ny][nx] = true;
          vec.push_back({nx, ny});
          cur = {nx, ny};
          cont = true;
        } else if (grid[ny][nx] == 3) {
          last = {nx, ny};
        }
      }
    }
    vec.push_back(last);
  }
}

void input() {
  cin >> n >> m >> k;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> grid[y][x];
      if (grid[y][x] == 1) {
        vector<Person> vec;
        vec.push_back({x, y});
        groups.push_back(vec);
      }
    }
  }
}

void init() {
  memset(grid, 0, sizeof(grid));
  groups.clear();
}

void solution() {
  init();
  input();

  makeGroup();

  int ans = 0;
  for (int i = 0; i < k; ++i) {
    ans += simulation(i);
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2022-1-afternoon1.input", "r", stdin);
  freopen("2022-1-afternoon1.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}