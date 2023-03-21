// n개 중에 m개 뽑기

/**
 * 1이상 N이하의 숫자 중 M개의 숫자를 골라 만들 수 있는 모든 조합
 * 
 * 입력:
 * 첫째줄에 N과 M이 공백을 사이에 두고 주어짐
 * 1 <= M <= N <= 10
 * 
 * 출력:
 * 조합의 개수만큼의 줄에 걸쳐 한 줄에 하나씩 조합의 상태를 공백을 사이에 두고 출력
 * 앞에서부터 사전순으로 앞선 조합부터 출력하며, 한 조합 내에서는 숫자들을 오름차순으로 정렬
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n, m;
vector<int> vec;

void combination(int cur) {
  if (vec.size() == m) {
    for (int i = 0; i < m; ++i) {
      cout << vec[i] + 1 << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = cur; i < n; ++i) {
    vec.push_back(i);
    combination(i + 1);
    vec.pop_back();
  }
}

void init() {
  vec.clear();
}

void solution() {
  init();

  cin >> n >> m;

  combination(0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-3-1.input", "r", stdin);
  freopen("2-3-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}