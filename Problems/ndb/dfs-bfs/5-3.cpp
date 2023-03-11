// 음료수 얼려 먹기

/**
 * NxM 크기의 얼음틀, 구멍이 뚫려 있는 부분은 0, 칸막이가 존재하는 부분은 1
 * 구멍이 뚫려 있는 부분끼리 상하좌우 붙어있는 경우 서로 연결되어 있는 것으로 간주
 * 얼음 틀의 모양이 주어졌을 때 생성되는 총 아이스크림의 개수
*/

// 참고: 공백없이 입력을 받는 경우 - https://chogyujin.github.io/2019/02/15/공백없이-입력-받을-때/
// 1. scanf("1%d", &var);
// 2. char로 받은 변수에 '0' 빼기

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N, M;
int graph[1001][1001];

bool dfs(int x, int y) {
  if (x < 0 || x >= N || y < 0 || y >= M) {
    return false;
  }

  if (graph[x][y] == 0) {
    graph[x][y] = 1;
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x,  y + 1);
    dfs(x, y - 1);
    return true;
  }

  return false;
}

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

  int answer = 0;
  for (int i = 0; i < N; i++) {
    for (int j= 0; j < M; j++) {
      if (dfs(i, j)) {
        answer++;
      }
    }
  }

  return answer;
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
  print({"00110",
         "00011",
         "11111",
         "00000"}, 3);
  print({"00000111100000",
         "11111101111110",
         "11011101101110",
         "11011101100000",
         "11011111111111",
         "11011111111100",
         "11000000011111",
         "01111111111111",
         "00000000011111",
         "01111111111000",
         "00011111111000",
         "00000001111000",
         "11111111110011",
         "11100011111111",
         "11100011111111"}, 8);
  return 0;
}