// 연구소 - 삼성 기출
// 출처: https://www.acmicpc.net/problem/14502

/**
 * NxM 크기 연구소, 빈 칸과 벽으로 이루어져 있음. 0은 빈칸, 1은 벽, 2는 바이러스
 * 일부 칸은 바이러스가 존재, 상하좌우로 인접한 빈칸으로 모두 퍼져나갈 수 있음
 * 새로 세울 수 있는 벽의 개수는 3개, 꼭 3개를 세워야 함
 * 벽을 3개 세운 뒤, 바이러스가 퍼질 수 없는 안전 영역의 크기의 최댓값?
 * 
 * 입력:
 * 첫째 줄에 지도의 세로 크기 N, 가로 크기 M이 주어진다.(3<=N,M<=8)
 * 둘째 줄부터 N개의 줄에 지도의 모양이 주어진다.
 * 바이러스는 2 이상, 10 이하
 * 빈 칸의 개수는 3개 이상
 * 
 * 출력:
 * 첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력
 * 
 ****************************************************
 * 경우의 수 확인
 * 최대 빈 공간 8x8 - 2(바이러스) = 62
 * 62C3 = 38,450가지
 * 
 * 최악의 경우 62가지 경우에 BFS가 62번 수행
 * 38,450 x 62 = 2,383,900번
 * => 충분함
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, M;
int lab[8][8];
int ret;

int num_wall;

struct Position {
  int x;
  int y;
};
queue<Position> virus;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { 1, -1, 0, 0 };

void bfs() {
  int copied_lab[8][8];
  memcpy(copied_lab, lab, sizeof(lab));
  queue<Position> copied_virus = virus;
  int visited[8][8] = { 0, };

  int num_virus = copied_virus.size();
  while (!copied_virus.empty()) {
    Position cur = copied_virus.front();
    copied_virus.pop();
    int x = cur.x;
    int y = cur.y;
    visited[y][x] = 1;
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 0 || nx >= M || ny < 0 || ny >= N) {
        continue;
      }
      if (visited[ny][nx] == 0 && copied_lab[ny][nx] == 0) {
        copied_lab[ny][nx] = 2;
        copied_virus.push({nx, ny});
        ++num_virus;
      }
    }
  }

  int safe_zone = N * M - (num_wall + 3) - num_virus;
  if (safe_zone > ret) {
    ret = safe_zone;
  }
}

void dfs(int count, int sx, int sy) {
  if (count == 3) {
    bfs();
    return;
  }

  for (int y = 0; y < N; ++y) {
    for (int x = sx; x < M; ++x) {
      if (lab[y][x] == 0) {
        lab[y][x] = 1;
        dfs(count + 1, x, y);
        lab[y][x] = 0;
      }
    }
    sx = 0;
  }
}

void init() {
  memset(lab, 0, sizeof(lab));
  ret = 0;
  num_wall = 0;
  virus = queue<Position>();
}

void solution() {
  init();

  cin >> N >> M;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      cin >> lab[y][x];
      if (lab[y][x] == 2) {
        virus.push({x, y});
      } else if (lab[y][x] == 1) {
        ++num_wall;
      }
    }
  }

  dfs(0, 0, 0);
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("13-16.input", "r", stdin);
  freopen("13-16.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}
