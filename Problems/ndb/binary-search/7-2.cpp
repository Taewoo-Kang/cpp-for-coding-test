// 부품 찾기

/**
 * N개의 부품에는 정수 형태의 고유한 번호가 있음
 * M개 종류의 부품을 확인해서 요청한 부품의 순서대로 부품이 있으면 yes, 없으면 no 출력
 * 
 * 입력:
 * 첫째 줄에 정수 N (1 <= N <= 1,000,000)
 * 둘째 줄에 공백으로 구분하여 N개의 정수가 주어짐 (1 <= 정수 <= 1,000,000)
 * 셋째 줄에 정수 M (1 <= M  <= 100,000)
 * 넷째 줄에 공백으로 구분하여 M개의 정수가 주어짐
 * 
 * 출력:
 * 첫째 줄에 공백으로 구분하여 각 부품이 존재하면 yes, 없으면 no 출력
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> elems, target;

int binary_search(int target_num, int start, int end) {
  while (start <= end) {
    int mid = (start + end) / 2;
    if (elems[mid] == target_num) {
      return mid;
    }
    if (elems[mid] > target_num) {
      end = mid -1;
    } else {
      start = mid + 1;
    }
  }

  return -1;
}

void solution() {
  elems.clear();
  target.clear();

  cin >> N;
  elems.reserve(N);
  for (int i = 0; i < N; ++i) {
    cin >> elems[i];
  }

  cin >> M;
  target.reserve(M);
  for (int i = 0; i < M; ++i) {
    cin >> target[i];
  }

  sort(elems.begin(), elems.end());
  for (int i = 0; i < M; ++i) {
    int ret = binary_search(target[i], 0, N-1);
    if (ret >= 0) {
      cout << "yes" << ' ';
    } else {
      cout << "no" << ' ';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("7-2.input", "r", stdin);
  freopen("7-2.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}