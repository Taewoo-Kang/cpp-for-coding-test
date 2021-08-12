// 다리를 지나는 트럭
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42583

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    queue<int> q;
    for (int weight : truck_weights) {
        q.push(weight);
    }

    vector<pair<int, int>> trucksOnBridge;
    int weightsOnBridge = 0;
    while (1) {
        int truckWeight = q.front();
        if (!q.empty() && weightsOnBridge + truckWeight < weight) {
            q.pop();
            weightsOnBridge += truckWeight;
            trucksOnBridge.push_back(make_pair(truckWeight, 0));
        }
        for (auto it = trucksOnBridge.begin(); it != trucksOnBridge.end(); ) {
            if (it->second == bridge_length) {
                weightsOnBridge -= it->first;
                trucksOnBridge.erase(it);
            } else {
                ++it->second;
                ++it;
            }
        }
        ++answer;

        if (q.empty() && trucksOnBridge.empty()) {
            break;
        }
    }
    return answer;
}

void print(int bridge_length, int weight, vector<int> truck_weights, int answer) {
    int result = solution(bridge_length, weight, truck_weights);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print(2, 10, {7, 4, 5, 6}, 8);
    print(100, 100, {10}, 101);
    print(100, 100, {10,10,10,10,10,10,10,10,10,10}, 110);
    return 0;
}