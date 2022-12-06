// 대표 자연수
// 출처: https://www.acmicpc.net/problem/2548

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int solution(vector<int> input) {
    int ret = 0;

    sort(input.begin(), input.end());

    int diff_min = numeric_limits<int>::max();
    for (int i : input) {
        int diff = 0;
        for (int j : input) {
            if (j > i) diff += j - i;
            else diff += i - j;
        }

        cout << i << diff << endl;
        if (diff < diff_min) {
            diff_min = diff;
            ret = i;
        }
    }
    return ret;
}

void print(vector<int> input, int answer) {
    int result = solution(input);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
        cout << "Result: " << result << ", Answer: " << answer << endl;
    }
}
 
int main() {
    print({4, 3, 2, 2, 9, 10}, 3);
    return 0;
}