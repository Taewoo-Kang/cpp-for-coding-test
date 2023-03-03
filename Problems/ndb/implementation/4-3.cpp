// 왕실의 나이트

/*
 * 8x8 좌표 평면, 행은 a~h, 열은 1~8로 표현
 * 나이트가 이동할 수 있는 경우는 L자 모양 두 가지
 * 1. 수평으로 두 칸 이동한 뒤 수직으로 한 칸 이동
 * 2. 수직으로 두 칸 이동한 뒤 수평으로 한 칸 이동
 * 
 * 나이트의 위치가 주어졌을 때, 좌표 밖으로 나가지 않도록 나이트가 이동할 수 있는 경우의 수
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isInsideGarden(int col, int row) {
  return (col > 0 && col < 9) && (row > 0 && row < 9);
}

int solution(string input) {
  int answer = 0;

  int col = input[0] - 'a' + 1;
  int row = input[1] - '0';

  vector<vector<int>> moves = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, 
                              {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
  
  for (vector<int> move : moves) {
    if (isInsideGarden(col + move[0], row + move[1])) {
      answer++;
    }
  }
  return answer;
}

void print(string input, int answer) {
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
  print("a1", 2);
  print("c2", 6);
  return 0;
}