// 컨베이어 벨트 위의 로봇
// 삼성 2020년 하반기 오전 1번
// 출처: https://www.acmicpc.net/problem/20055

/**
 * 길이가 N인 컨베이어 벨트에 길이가 2N인 벨트가 위아래로 감싸며 돌고 있음
 * 벨트가 한 칸 회전 -> 1~2N-1까지 칸은 다음 번호의 칸이 있는 위치로 이동, 2N번 칸은 1번 칸의 위치로 이동
 * i번 칸의 내구도는 A_i
 * 1번 칸이 있는 위치를 '올리는 위치', N번 칸이 있는 위치를 '내리는 위치'라고 함
 * 
 * 로봇은 올리는 위치에만 올릴 수 있고, 언제든지 로봇이 내리는 위치에 도달하면 그 즉시 내림
 * 로봇을 올리는 위치에 올리거나 로봇이 어떤 칸으로 이동하면 그 칸의 내구도는 1만큼 감소
 * 
 * 1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전
 * 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동
 *   -> 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1이상 남아있어야 함
 * 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 로봇을 올림
 * 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정 종료
 * 
 * 종료되었을 때 몇 번째 단계가 진행 중이었는지?
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int N, K;
vector<bool> belt;
vector<int> duration;

int breakdown;

void unload() {
  if (belt[N-1]) {
    belt[N-1] = false;
  }
}

void rotate() {
  bool temp_robot = belt[2*N - 1];
  belt.pop_back();
  belt.insert(belt.begin(), temp_robot);

  int temp_duration = duration[2*N - 1];
  duration.pop_back();
  duration.insert(duration.begin(), temp_duration);

  unload();
}

void moveRobot() {
  for (int i = N-2; i >= 0; --i) {
    if (!belt[i] || belt[i+1] || duration[i+1] == 0) {
      continue;
    }
    belt[i+1] = true;
    belt[i] = false;
    --duration[i+1];
    if (!duration[i+1]) {
      ++breakdown;
    }
  }

  unload();
}

void simulate() {
  rotate();

  moveRobot();

  if (duration[0]) {
    belt[0] = true;
    --duration[0];
    if (!duration[0]) {
      ++breakdown;
    }
  }
}

void input() {
  cin >> N >> K;
  belt.resize(2 * N);
  duration.resize(2 * N);
  for (int i = 0; i < 2 * N; ++i) {
    cin >> duration[i];
  }
}

void init() {
  belt.clear();
  duration.clear();
}

void solution() {
  init();
  input();

  breakdown = 0;
  int t = 0;
  while (breakdown < K) {
    ++t;
    simulate();
  }

  cout << t << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2020-2-morning1.input", "r", stdin);
  freopen("2020-2-morning1.output", "w", stdout);
  for (int i = 0; i < 4; ++i) {
    solution();
  }

  return 0;
}