// 미로 탈출

/**
 * 문제
 * NxM 크기의 미로, 첫 위치는 (1,1), 출구는 (N,M)
 * 괴물이 있는 부분은 0, 없는 부분은 1
 * 미로를 탈출하기 위해 움직여야 하는 최소 칸의 개수는?(시작칸 마지막칸 포함)
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N, M;
int graph[201][201];

int solution(vector<string> input) {
  memset(graph, 0, sizeof(graph));

  N = input.size();
  M = input[0].size();
  for (int i = 0; i < N; i++) {
    string row = input[i];
    for (int j = 0; j < M; j++) {
      graph[i][j] = row[j] - '0';
    }
  }

  vector<int> dx = {-1, 1, 0, 0};
  vector<int> dy = {0, 0, -1, 1};

  queue<pair<int,int>> q;
  q.push({0, 0});
  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
        continue;
      }
      if (graph[nx][ny] == 0) {
        continue;
      }
      if (graph[nx][ny] == 1) {
        graph[nx][ny] = graph[x][y] + 1;
        q.push({nx, ny});
      }
    }
  }

  return graph[N - 1][M - 1];
}

void print(vector<string> input, int answer) {
  int result = solution(input);
  if (result == answer) {
    cout << "Correct!" << endl;
  } else {
    cout << "Wrong Answer" << endl;
    cout << "=> Answer is: " << answer << endl;
    cout << "=> Result is: " << result << endl;
  }
}

int main() {
  print({"101010",
         "111111",
         "000001",
         "111111",
         "111111"}, 10);
  return 0;
}