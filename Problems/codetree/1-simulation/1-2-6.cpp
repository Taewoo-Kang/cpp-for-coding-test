// 최단 Run Length 인코딩
// 분류 - 격자 안에서 밀고 딩기기

/**
 * 길이가 n인 문자열 A, 적절하게 특정 횟수만큼 오른쪽으로 shift
 * 문자열에 Run-Length Encoding을 진행했을 때 길이가 최소가 되도록
 * Run-Length Encoding은 연속해서 나온 문자와 연속해서 나온 개수로 나타내는 방식
 * 
 * 입력:
 * 첫번째 줄에 문자열 A가 소문자 알파벳으로
 * 문자열 길이는 1 이상 10 이하
 * 
 * 출력:
 * 문자열 A를 오른쪽으로 특정 횟수만큼 shift하고 Run-Length Encoding 시 길이 중 최소
*/

#include <iostream>
#include <string>

using namespace std;

string A;

int calcEncodingLength() {
  string encoded;
  encoded.push_back(A[0]);

  int len = A.length();
  int count = 1;
  for (int i = 0; i < len; ++i) {
    char cur = A[i];
    if (cur == encoded.back()) {
      ++count;
    } else {
      encoded += to_string(count);
      encoded.push_back(cur);
      count = 1;
    }
  }
  encoded += to_string(count);
  return encoded.length();
}

void solution() {
  cin >> A;
  int ret = 0x7fffffff;

  int len = A.length();
  for (int i = 0; i < len; ++i) {
    char temp = A.back();
    for (int j = len - 1; j > 0; --j) {
      A[j] = A[j - 1];
    }
    A[0] = temp;
    int candi = calcEncodingLength();
    if (candi < ret) {
      ret = candi;
    }
  }
  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("1-2-6.input", "r", stdin);
  freopen("1-2-6.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}