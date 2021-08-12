// 베스트앨범
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42579

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 참고! std::map은 binary search tree로 구현되어 있어 key가 아닌 value를 기준으로 정렬하는 기능을 제공하지 않음
// 출처: https://stackoverflow.com/questions/14323914/define-a-compare-function-for-stdmap-which-uses-values-instead-of-keys

bool cmpGenre(const pair<string, int> &lhs, const pair<string, int> &rhs) {
    return lhs.second > rhs.second;
}

bool cmpPlay(const pair<int, int> &lhs, const pair<int, int> &rhs) {
    if (lhs.first == rhs.first) {
        return lhs.second < rhs.second;
    }
    return lhs.first > rhs.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    unordered_map<string, int> genreToPlaysMap;
    unordered_map<string, vector<pair<int, int>>> genreMap;
    for (int i = 0; i < genres.size(); i++) {
        genreToPlaysMap[genres[i]] += plays[i];
        genreMap[genres[i]].push_back(make_pair(plays[i], i));
    }

    vector<pair<string, int>> genreVector;
    for (auto elem : genreToPlaysMap) {
        genreVector.push_back(make_pair(elem.first, elem.second));
    }
    sort(genreVector.begin(), genreVector.end(), cmpGenre);

    for (auto elem : genreVector) {
        vector<pair<int, int>> pairVector = genreMap[elem.first];
        sort(pairVector.begin(), pairVector.end(), cmpPlay);
        int cnt = 0;
        for (auto pair : pairVector) {
            if (cnt > 1) {
                break;
            }
            answer.push_back(pair.second);
            ++cnt;
        }
    }

    return answer;
}

void print(vector<string> genres, vector<int> plays, vector<int> answer) {
    vector<int> result = solution(genres, plays);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({"classic", "pop", "classic", "classic", "pop"}, {500, 600, 150, 800, 2500}, {4, 1, 3, 0});
    return 0;
}