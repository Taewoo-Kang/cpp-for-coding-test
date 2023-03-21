// n개의 점 중 m개 고르기

/**
 * 좌표평면 위에 점 n개가 주어졌을 때, 점 m개를 선택
 * 선택한 점들 중 거리가 가장 먼 두 점 사이의 거리값이 최소가 되도록
 * 
 * 입력:
 * 첫번째 줄에는 n과 m이 공백을 사이에 두고 주어짐
 * 두번째 줄부터는 n개의 줄에 걸쳐 점의 정보 (x,y)가 주어짐
 * (1 <= x,y <= 100, 2 <= m <= n <= 20)
 * 
 * 출력:
 * 점 m개를 적절히 선택하여 가장 먼 두 점 사이의 거리가 최소가 되었을 때,
 * 그 떄의 최소 거리에 제곱한 값을 출력
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m;
int ret;

struct Position {
  int x;
  int y;
};
vector<Position> vec;
vector<Position> selected;

int calcDistance(Position a, Position b) {
  return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

void combination(int start) {
  if (selected.size() == m) {
    int max_distance = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = i + 1; j < m; ++j) {
        int result = calcDistance(selected[i], selected[j]);
        if (result > max_distance) {
          max_distance = result;
        }
      }
    }

    if (max_distance < ret) {
      ret = max_distance;
    }
    return;
  }

  for (int i = start; i < n; ++i) {
    selected.push_back(vec[i]);
    combination(i + 1);
    selected.pop_back();
  }
}

void init() {
  ret = 0x7fffffff;
  vec.clear();
  selected.clear();
}

void solution() {
  init();

  cin >> n >> m;

  int x, y;
  for (int i = 0; i < n; ++i) {
    cin >> x >> y;
    vec.push_back({x, y});
  }

  combination(0);
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-3-5.input", "r", stdin);
  freopen("2-3-5.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}