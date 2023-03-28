// 떡볶이 떡 만들기

/**
 * 절단기의 높이 H를 지정하면 줄지어진 떡을 한번에 절단하고 잘린 떡 길이만큼 손님이 가져간다.
 * 높이가 H보다 긴 떡은 H 위의 부분이 잘리고, 낮은 떡은 잘리지 않는다.
 * 손님이 요청한 총 길이가 M일 때 적어도 M만큼 떡을 얻기 위해 절단기에 설정할 수 있는 높이 최댓값
 * 
 * 입력:
 * 첫째 줄에 떡의 개수 N과 요청한 떡의 길이 M이 주어짐
 * (1 <= N <= 1,000,000, 1 <= M <= 2,000,000,000)
 * 둘째 줄에 떡의 개별 높이가 주어짐 (0 <= 높이 <= 1,000,000,000)
 * 
 * 출력:
 * 적어도 M만큼의 떡을 가져가기 위해 절단기에 설정할 수 있는 높이의 최댓값
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> vec;

int binary_search(int target, int start, int end) {
  int ret = 0;
  while (start <= end) {
    int sum = 0;
    int mid = (start + end) / 2;
    for (int i = 0; i < N; ++i) {
      if (vec[i] > mid) {
        sum += (vec[i] - mid);
      }
    }
    if (sum < target) {
      end = mid - 1;
    } else {
      start = mid + 1;
      ret = mid;
    }
  }

  return ret;
}

void solution() {
  cin >> N >> M;
  vec.reserve(N);
  for (int i = 0; i < N; ++i) {
    cin >> vec[i];
  }

  sort(vec.begin(), vec.end());
  int ret = binary_search(M, 0, vec[N-1]);
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("7-3.input", "r", stdin);
  freopen("7-3.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}