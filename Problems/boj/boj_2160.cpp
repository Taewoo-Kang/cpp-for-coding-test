// 그림 비교
// 출처: https://www.acmicpc.net/problem/2160

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <bitset>

using namespace std;
using PicturePair = pair<int, int>;

PicturePair solution(int num, vector<string> input) {
    PicturePair ret;

    // int diff_min = numeric_limits<int>::max();;
    // for (int i = 0; i < num; i++) {
    //     for (int j = i+1; j < num; j++) {
    //         int diff = 0;
    //         for (int k = 0; k < 5; k++) {
    //             string a = input[5*i+k];
    //             string b = input[5*j+k];
    //             for (int l = 0; l < 7; l++) {
    //                 if (a[l] != b[l]) {
    //                     diff++;
    //                 }
    //             }
    //         }
    //         if (diff < diff_min) {
    //             diff_min = diff;
    //             ret = make_pair(i+1, j+1);
    //         }
    //     }
    // }

    vector<bitset<35>> bits;
    for (int n = 0; n < num; n++) {
        bitset<35> bit;
        for (int i = 0; i < 5; i++) {
            string str = input[5*n + i];
            for (int j = 0; j < 7; j++) {
                if (str[j] == 'X') {
                    bit.set(7*i + j);
                }
            }
        }
        bits.push_back(bit);
    }

    int diff_min = numeric_limits<int>::max();;
    for (int i = 0; i < num; i++) {
        for (int j = i+1; j < num; j++) {
            bitset<35> a = bits[i];
            bitset<35> b = bits[j];
            int diff = (a ^ b).count();
            if (diff < diff_min) {
                diff_min = diff;
                ret = make_pair(i+1, j+1);
            }
        }
    }
    
    return ret;
}

void print(int num, vector<string> input, PicturePair answer) {
    PicturePair result = solution(num, input);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
    }
}
 
int main() {
    print(3, {"..X....",
            ".XXX...",
            ".XX....",
            ".....X.",
            ".X...X.",

            "XX.....",
            "X......",
            "XX...XX",
            "XXXX.XX",
            "XXX..XX",

            "...X...",
            "..XX...",
            ".XX....",
            ".XX..X.",
            ".X...X."}, {1, 3});
    return 0;
}