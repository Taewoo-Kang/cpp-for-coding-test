// 치킨 배달 - 삼성 기출
// 출처: https://www.acmicpc.net/problem/15686

/**
 * NxN 크기 도시, 도시의 칸은 (r, c)와 같은 형태 - r행 c열
 * 치킨 거리는 집과 가장 가까운 치킨집 사이의 거리, 도시의 치킨 거리는 모든 집의 치킨거리의 합
 * 치킨 거리 = |r1 - r2| + |c1 - c2|
 * 도시의 치킨집 중 최대 M개를 고르고 나머지 치킨집은 폐업시킬 때, 어떻게 도시의 치킨 거리가 가장 작게 될지?
 * 
 * 입력:
 * 첫째 줄에 N(2<=N<=50)과 M(1<=M<=13)
 * 둘째 줄부터 N개의 줄에 도시의 정보(0은 빈 칸, 1은 집, 2는 치킨집)
 * 집의 개수는 2N개를 넘지 않으며, 적어도 1개는 존재
 * 치킨집의 개수는 M<=치킨집<=13
 * 
 * 출력: 
 * 첫째 줄에 폐업시키지 않을 치킨집 최대 M개 골랐을 때 도시의 치킨 거리의 최솟값
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

int N, M;
int city[50][50];
int ret;

struct Position {
  int x;
  int y;
};
vector<Position> house, chicken, selected;

int calcDistance(Position a, Position b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

void calcCitywiseDistance() {
  int total_distance = 0;
  for (int i = 0; i < house.size(); ++i) {
    int distance = 0x7fffffff;
    for (int j = 0; j < selected.size(); ++j) {
      int cur_distance = calcDistance(house[i], selected[j]);
      if (cur_distance < distance) {
        distance = cur_distance;
      }
    }
    total_distance += distance;
  }

  if (total_distance < ret) {
    ret = total_distance;
  }
}

void dfs(int pos) {
  if (selected.size() == M) {
    calcCitywiseDistance();
    return;
  }

  for (int i = pos; i < chicken.size(); ++i) {
    selected.push_back(chicken[i]);
    dfs(i + 1);
    selected.pop_back();
  }
}

void init() {
  memset(city, 0, sizeof(city));
  ret = 0x7fffffff;
  house.clear();
  chicken.clear();
  selected.clear();
}

void solution() {
  init();

  cin >> N >> M;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> city[y][x];
      if (city[y][x] == 1) {
        house.push_back({x, y});
      } else if (city[y][x] == 2) {
        chicken.push_back({x, y});
      }
    }
  }

  dfs(0);
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("12-13.input", "r", stdin);
  freopen("12-13.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }

  return 0;
}