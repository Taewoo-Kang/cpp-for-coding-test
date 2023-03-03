// 게임 개발

/**
 * NxM 크기의 직사각형 맵, 각 칸은 육지 또는 바다, 캐릭터는 동서남북 중 한 곳을 바라본다.
 * 맵의 각 칸은 (A, B)로 표현되며, A는 북쪽으로부터 떨어진 칸의 개수, B는 서쪽으로부터 떨어진 칸의 개수
 * 
 * 캐릭터 동작 매뉴얼
 * 1. 현재 위치에서 현재 방향 기준으로 왼쪽부터
 * 2. 왼쪽에 아직 가보지 않은 칸이 있으면 회전 후 전진, 없으면 왼쪽으로 회전만
 * 3. 네 방향 모두 가본 칸이거나 바다이면, 바라보는 방향을 유지한 채로 한칸 뒤로 가고, 뒤쪽 방향이 바다면 멈춘다.
 * 
 * 입력 조건
 * 첫째 줄에 맵의 세로 크기 N과 가로 크기 M(3 <= N,M <= 50)
 * 둘째 줄에 캐릭터가 있는 칸의 좌표 (A, B)와 바라보는 방향 d(북동남서 순으로 0123)
 * 셋째 줄부터 맵이 육지(0)인지 바다(1)인지에 대한 정보
 * 
 * 출력 조건
 * 첫째 줄에 이동을 마친 캐릭터가 방문한 칸의 수
 */

#include <iostream>
#include <vector>

using namespace std;

int turnLeft(int current) {
  int next = current--;
  return next % 4;
}

int solution(vector<int> condition, vector<vector<int>> map) {
  int N = map.size();
  int M = map[0].size();
  int x = condition[0];
  int y = condition[1];
  int direction = condition[2];

  vector<vector<int>> manuals = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}};

  int answer = 1;
  while (1) {
    vector<vector<int>> manual(manuals.begin() + direction, manuals.begin() + direction + 4);
    bool move = false;
    for (vector<int> step : manual) {
      direction = turnLeft(direction);
      int next_x = x + step[0];
      int next_y = y + step[1];
      if (!map[next_y][next_x]) {
        ++map[next_y][next_x];
        x = next_x;
        y = next_y;
        move = true;
        answer++;
        break;
      }
    }

    if (!move) {
      vector<int> backstep = manual[2];
      x = x + backstep[0];
      y = y + backstep[1];
      if (map[y][x]) {
        return answer;
      }
    }
  }

  cout << "Error! DO NOT REACHED" << endl;
  return answer;
}

void print(vector<int> condition, vector<vector<int>> map, int answer) {
  int result = solution(condition, map);
  if (result == answer) {
    cout << "Correct!" << endl;
  } else {
    cout << "Wrong Answer" << endl;
    cout << "=> Answer is: " << answer << endl;
    cout << "=> Result is: " << result << endl;
  }
}

int main() {
  print({1, 1, 0}, {{1, 1, 1, 1}, 
                    {1, 0, 0, 1},
                    {1, 1, 0, 1},
                    {1, 1, 1, 1}}, 3);
  return 0;
}