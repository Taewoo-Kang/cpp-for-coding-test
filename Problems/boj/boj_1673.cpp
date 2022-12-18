// 치킨 쿠폰
// 출처: https://www.acmicpc.net/problem/1673

#include <iostream>
#include <vector>

using namespace std;

int solution(vector<int> input) {
    int ret = 0;

    int coupon = input[0];
    int k = input[1];

    int stamp = 0;
    // while (coupon) {
    //     coupon--;
    //     ret++;
    //     stamp++;
    //     if (stamp == k) {
    //         coupon++;
    //         stamp = 0;
    //     }
    // }

    while (coupon) {
        ret += coupon;
        stamp += coupon;
        coupon = stamp / k;
        stamp %= k;
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
    print({4, 3}, 5);
    print({10, 3}, 14);
    print({100, 5}, 124);
    return 0;
}