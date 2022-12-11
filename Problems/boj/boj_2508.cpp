// 사탕박사 고창영
// 출처: https://www.acmicpc.net/problem/2508

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solution(vector<string> input) {
    int ret = 0;

    int row = input.size();
    int column = input[0].size();
    vector<string> permute(column);
    for (string str : input) {
        for (int i = 0; i < column; i++) {
            char c = str[i];
            permute[i].push_back(c);
            if (i > 0 && i < column - 1) {
                if (str[i-1] == 62 && c == 111 && str[i+1] == 60) {
                    ret++;
                }
            }
        }
    }

    for (string str : permute) {
        for (int i = 1; i < row - 1; i++) {
            if (str[i-1] == 118 && str[i] == 111 && str[i+1] == 94) {
                ret++;
            }
        }
    }

    return ret;
}

void print(vector<string> input, int answer) {
    int result = solution(input);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
        cout << "Result: " << result << ", Answer: " << answer << endl;
    }
}
 
int main() {
    print({".>o<",
           "v.^.",
           "ooo.",
           "^.^.",
           ">o<<",}, 3);
    print({".>o<",
           "vo^.",
           "ooo.",
           "^.^.",
           ">o<<",}, 3);
    return 0;
}