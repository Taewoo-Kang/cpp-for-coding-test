// 크기가 n인 순열

/**
 * 1부터 n까지의 수를 정확히 한 번씩만 사용하여 만들 수 있는 가능한 모든 순열
 * 단, 사전 순으로 먼저 출력
 * 
 * 입력:
 * 정수 n (1 <= n <= 8)
 * 
 * 출력:
 * 한 줄에 하나의 수열에 대한 정보를 공백을 사이에 두고 출력
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> vec;
bool visited[8];

void init() {
  vec.clear();
}

void permutation() {
  if (vec.size() == n) {
    for (int i = 0; i < n; ++i) {
      cout << vec[i] + 1 << ' ';
    }
    cout << '\n';
  }

  for (int i = 0; i < n; ++i) {
    if (visited[i]) {
      continue;
    }

    vec.push_back(i);
    visited[i] = true;
    permutation();
    vec.pop_back();
    visited[i] = false;
  }
}

void solution() {
  init();

  cin >> n;
  permutation();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-4-1.input", "r", stdin);
  freopen("2-4-1.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}
