// 모노미노도미노2
// 삼성 2020년도 상반기 오전 1번
// 출처: https://www.acmicpc.net/problem/20061

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Box;
Box blue;
Box green;

int flip(int t) {
  if (t == 1) return 1;
  if (t == 2) return 3;
  return 2;
}

void eraseRow(int row, bool is_blue) {
  Box& box = is_blue ? blue : green;
  box.erase(box.begin() + row);
  box.insert(box.begin(), {0,0,0,0});
}

int insertBlock(int t, int y, bool is_blue) {
  Box& box = is_blue ? blue : green;
  if (is_blue) {
    t = flip(t);
  }

  // 블록 두기
  for (int x = 0; x < 6; ++x) {
    if (t == 1) {
      if (x == 5 || box[x + 1][y]) {
        box[x][y] = 1;
        break;
      }
    } else if (t == 2) {
      if (x == 5 || box[x + 1][y] || box[x + 1][y + 1]) {
        box[x][y] = 1;
        box[x][y + 1] = 1;
        break;
      }
    } else {
      if (x == 4 || box[x + 2][y]) {
        box[x][y] = 1;
        box[x + 1][y] = 1;
        break;
      }
    }
  }

  // 점수 획득
  int ret = 0;
  for (int x = 2; x < 6; ++x) {
    bool not_full = false;
    for (int y = 0; y < 4; ++y) {
      if (!box[x][y]) {
        not_full = true;
      }
    }
    if (!not_full) {
      eraseRow(x, is_blue);
      ++ret;
    }
  }

  // 연한 칸 처리
  int move = 0;
  for (int x = 0; x < 2; ++x) {
    for (int y = 0; y < 4; ++y) {
      if (box[x][y]) {
        ++move;
        break;
      }
    }
  }
  for (int i = 0; i < move; ++i) {
    eraseRow(5, is_blue);
  }

  return ret; 
}

int play(int t, int x, int y) {
  int ret = 0;
  ret += insertBlock(t, x, true);
  ret += insertBlock(t, y, false);
  return ret;
}

void init() {
  blue.clear();
  for (int i = 0; i < 6; ++i) {
    blue.push_back({0,0,0,0});
  }

  green.clear();
  for (int i = 0; i < 6; ++i) {
    green.push_back({0,0,0,0});
  }
}

void solution() {
  init();

  int N, t, x, y;
  cin >> N;

  int score = 0;
  for (int i = 0; i < N; ++i) {
    cin >> t >> x >> y;
    score += play(t, x, y);
  }

  int num = 0;
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (blue[i][j]) ++num;
      if (green[i][j]) ++num;
    }
  }

  cout << score << '\n' << num << '\n';
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-1-morning1.input", "r", stdin);
  freopen("2020-1-morning1.output", "w", stdout);
  for (int i = 0; i < 8; ++i) {
    solution();
  }
  return 0;
}
