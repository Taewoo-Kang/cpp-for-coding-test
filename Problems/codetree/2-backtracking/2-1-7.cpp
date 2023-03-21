// 알파벳과 사칙연산
// 분류 - K개 중 하나를 N번 선택하기(Simple)

/**
 * a에서 f까지의 소문자 알파벳과 +,=,x 기호만으로 이루어져 있는 길이가 n인 식이 하나 주어짐
 * 이 때 각 소문자 알파벳에 1이상 4이하의 숫자를 집어넣어 식의 결과를 최대로
 * 단, x가 우선순위가 더 높은 것이 아닌, 모든 연산의 우선순위가 전부 같다고 가정
 * 
 * 입력:
 * 첫번째 줄에 식이 주어지며 알파벳이나 연산자는 항상 번갈아가며 주어짐
 * 1 <= 식의 길이 <= 200
 * 
 * 출력:
 * 가능한 최대 결과를 출력
 * 계산 도중 값이 항상 -2^31이상 2^31-1 이하를 벗어나지 않음을 가정
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

string expression;
vector<char> alphabet;
vector<int> target;
unordered_map<char, int> m;
priority_queue<int> results;
int n;

int operation(int lhs, int rhs, char op) {
  if (op == '+') {
    return lhs + rhs;
  }
  if (op == '-') {
    return lhs - rhs;
  }
  if (op == '*') {
    return lhs * rhs;
  }

  cout << "error!" << '\n';
  return -1;
}

int calculate() {
  vector<int> v = target;
  char cur = expression[0];
  m[cur] = v.back();
  v.pop_back();

  int ret = m[cur];
  for (int i = 1; i < expression.size(); ) {
    char op = expression[i];
    cur = expression[i+1];
    if (m[cur] == 0) {
      m[cur] = v.back();
      v.pop_back();
    }

    ret = operation(ret, m[cur], op);

    i += 2;
  }

  m.clear();
  return ret;
}

void recursion() {
  if (target.size() == n) {
    int result = calculate();
    results.push(result);
    return;
  }

  for (int i = 1; i <= 4; ++i) {
    target.push_back(i);
    recursion();
    target.pop_back();
  }
}

void init() {
  alphabet.clear();
  target.clear();
  results = priority_queue<int>();
  m.clear();
}

void solution() {
  init();

  cin >> expression;
  for (int i = 0; i < expression.size(); ++i) {
    char cur = expression[i];
    if (cur >= 'a' && cur <= 'f') {
      alphabet.push_back(cur);
    }
  }

  for (int i = 0; i < alphabet.size(); ++i) {
    m[alphabet[i]] = 0;
  }
  n = m.size();
  recursion();
  cout << results.top() << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-1-7.input", "r", stdin);
  freopen("2-1-7.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}