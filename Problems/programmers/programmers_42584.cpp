// 주식가격
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42584

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
/*
vector<int> solution(vector<int> prices) {
    vector<int> answer;
    for (int i = 0; i < prices.size(); ++i) {
        int cnt = 0;
        for (int j = i+1; j < prices.size(); ++j) {
            ++cnt;
            if (prices[i] > prices[j]) {
                break;
            }
        }
        answer.push_back(cnt);
    }

    return answer;
}
*/
// stack을 이용한 풀이
vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());
    stack<int> st;
    st.push(0);
    for (int i =1; i < prices.size(); ++i) {
        while (!st.empty() && prices[st.top()] > prices[i]) {
            answer[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }

    while (!st.empty()) {
        answer[st.top()] = prices.size() - 1 - st.top();
        st.pop();
    }

    return answer;
}

void print(vector<int> prices, vector<int> answer) {
    vector<int> result = solution(prices);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({1, 2, 3, 2, 3}, {4, 3, 1, 1, 0});
    print({2, 3, 4, 4, 1}, {4, 3, 2, 1, 0});
    return 0;
}