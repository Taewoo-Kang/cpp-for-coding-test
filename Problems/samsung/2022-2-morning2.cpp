// 산타의 선물공장
// 삼성 2022년도 하반기 오전 2번
// 출처: https://www.codetree.ai/training-field/frequent-problems/santa-gift-factory

/**
 * 산타는 공장에서 순서대로 q개의 명령에 따라 일을 진행
 * 1. 공장 설립
 *    m개의 벨트 설치, 각 벨트 위에 정확히 n/m개의 물건들을 놓아 총 n개의 물건을 준비
 *    각 물건에는 고유한 번호(ID)와 무게(W)가 적혀있음
 * 2. 물건 하차
 *    최대 무게인 w_max가 주어질 때 1번부터 m번까지 순서대로 벨트를 보며
 *    각 벨트의 맨 앞에 있는 상자의 무게가 w_max 이하라면 하차하고 아니면 벨트 맨 뒤로 보냄   
 *    과정을 진행한 후 하차된 상자 무게의 총합 출력
 * 3. 물건 제거
 *    제거하기를 원하는 물건의 고유 번호 r_id가 주어짐
 *    해당 고유 번호에 해당하는 상자가 놓여있는 벨트가 있다면 상자를 제거 후 r_id 출력(없으면 -1)
 *    이에 따라 뒤에 있는 상자들을 앞으로 한 칸씩 내려옴
 * 4. 물건 확인
 *    확인하기를 원하는 물건의 고유 번호 f_id가 주어짐
 *    고유 번호에 해당하는 상자가 놓여있는 벨트가 있다면 해당 벨트의 번호 출력(없으면 -1)
 *    상자가 있는 경우 해당 상자 위에 있는 모든 상자를 전부 앞으로 가져옴(순서 유지)
 * 5. 벨트 고장
 *    고장이 발생한 벨트 번호 b_num 주어짐
 *    b_num 벨트의 오른쪽부터 순서대로 아직 고장이 나지 않은 최초의 벨트 위로 상자들을 순서대로 옮겨줌
 *    만약 m번 벤트까지 봤는데도 고장나지 않은 벨트가 없다면 다시 1번부터 순서대로 확인
 *    이 명령을 수행하기 전에 만약 b_num 벨트가 이미 망가져있다면 -1을, 아니면 b_num값 출력
 * q번에 걸쳐 명령을 순서대로 진행하며 원하는 결과를 출력하는 프로그램 작성
 * 
 * 입력:
 * 첫번째 줄에 명령의 수 q가 주어짐 (1 <= q <= 100,000)
 * 두번째 줄부터 q개의 줄에 걸쳐 명령의 정보가 주어짐
 * - 공장 설립
 *   100 n m ID1 ID2 ... IDn W1 W2 ... Wn 형태
 *   m개의 벨트와 n개의 선물로 이루어진 공장을 주어진 순서대로 n/m개씩 잘라 벨트에 올림
 *   (1 <= n <= 100,000 , 1 <= m <= 10, n은 항상 m의 배수, 1 <= ID, W <= 1,000,000,000)
 * - 물건 하차
 *   200 w_max 형태
 * - 물건 제거
 *   300 r_id 형태 (1 <= f_id <= 1,000,000,000)
 * - 물건 확인
 *   400 f_id 형태 (1 <= f_id <= 1,000,000,000)
 * - 벨트 고장
 *   500 b_num 형태 (1 <= b_num <= m) 
 * 
 * 출력:
 * 산타가 q개의 명령을 진행하면서 출력해야 하는 값을 한 줄에 하나씩 출력
*/

#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

struct Box {
  int idx;
  int weight;
  int belt;
  Box* prev;
  Box* next;

  Box() {
    idx = -1, weight = -1, belt = -1;
    prev = nullptr, next = nullptr;
  }
};

struct Belt {
  bool is_broken;
  Box* head;
  Box* tail;

  Belt() {
    is_broken = false;
    head = new Box();
    tail = new Box();
    head->next = tail, tail->prev = head;
    head->prev = nullptr, tail->next = nullptr;
  }

};

int q, cmd, n, m;
int id[100000];
int w[100000];
Box boxs[100000];
Belt belts[10];
unordered_map<int, Box*> box_map;

bool isEmptyBelt(int belt_num) {
  return belts[belt_num].head->next == belts[belt_num].tail;
}

void pushBackBox(int belt_num, Box* box) {
  box_map[box->idx] = box;
  Box* prev = belts[belt_num].tail->prev;
  Box* next = belts[belt_num].tail;

  box->prev = prev;
  box->next = next;
  prev->next = box;
  next->prev = box;
}

void popFrontBox(int belt_num) {
  if (isEmptyBelt(belt_num)) {
    return;
  }

  Box* box = belts[belt_num].head->next;
  box_map.erase(box->idx);

  Box* prev = belts[belt_num].head;
  Box* next = belts[belt_num].head->next->next;

  prev->next = next;
  next->prev = prev;
  box->prev = nullptr;
  box->next = nullptr;
}

void cmd100() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> id[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> w[i];
  }

  int pos = 0;
  for (int belt_num = 0; belt_num < m; ++belt_num) {
    belts[belt_num].is_broken = false;
    belts[belt_num].head->next = belts[belt_num].tail;
    belts[belt_num].tail->prev = belts[belt_num].head;
    belts[belt_num].head->prev = nullptr;
    belts[belt_num].tail->next = nullptr;
    for (int i = 0; i < n / m; ++i) {
      boxs[pos].idx = id[pos];
      boxs[pos].weight = w[pos];
      boxs[pos].belt = belt_num;
      pushBackBox(belt_num, &boxs[pos]);
      ++pos;
    }
  }
}

int cmd200() {
  int ret = 0;
  int w_max;
  cin >> w_max;

  for (int belt_num = 0; belt_num < m; ++belt_num) {
    if (isEmptyBelt(belt_num) || belts[belt_num].is_broken) {
      continue;
    }

    Box* front = belts[belt_num].head->next;
    if (front->weight <= w_max) {
      ret += front->weight;
      popFrontBox(belt_num);
    } else {
      popFrontBox(belt_num);
      pushBackBox(belt_num, front);
    }
  }

  return ret;
}

int cmd300() {
  int r_id;
  cin >> r_id;
  if (box_map.find(r_id) == box_map.end()) {
    return -1;
  }

  Box* item = box_map[r_id];
  Box* prev = item->prev;
  Box* next = item->next;

  prev->next = next;
  next->prev = prev;
  item->prev = nullptr;
  item->next = nullptr;

  box_map.erase(r_id);
  return r_id;
}

int cmd400() {
  int f_id;
  cin >> f_id;
  if (box_map.find(f_id) == box_map.end()) {
    return -1;
  }

  Box* item = box_map[f_id];
  Box* prev = item->prev;
  Box* begin = belts[item->belt].head->next;
  Box* end = belts[item->belt].tail->prev;

  if (item != begin) {
    item->prev = belts[item->belt].head;
    belts[item->belt].head->next = item;

    begin->prev = end;
    end->next = begin;

    prev->next = belts[item->belt].tail;
    belts[item->belt].tail->prev = prev;
  }

  return item->belt + 1;
}

int cmd500() {
  int b_num;
  cin >> b_num;
  --b_num;

  if (belts[b_num].is_broken) {
    return -1;
  }

  belts[b_num].is_broken = true;
  if (!isEmptyBelt(b_num)) {
    int target = (b_num + 1) % m;
    while (belts[target].is_broken) {
      target = (target + 1) % m;
    }

    Box* prev = belts[target].tail->prev;
    Box* begin = belts[b_num].head->next;
    Box* end = belts[b_num].tail->prev;

    for (auto it = begin; it != belts[b_num].tail; it = it->next) {
      it->belt = target;
    }

    prev->next = begin;
    begin->prev = prev;

    end->next = belts[target].tail;
    belts[target].tail->prev = end;

    belts[b_num].head->next = belts[b_num].tail;
    belts[b_num].tail->prev = belts[b_num].head;
  }

  return b_num + 1;
}

void init() {
  memset(id, 0, sizeof(id));
  memset(w, 0, sizeof(w));
  box_map.clear();
}

void solution() {
  init();

  cin >> q;
  while (q--) {
    cin >> cmd;
    switch (cmd) {
      case 100:
        cmd100();
        break;
      case 200:
        cout << cmd200() << '\n';
        break;
      case 300:
        cout << cmd300() << '\n';
        break;
      case 400:
        cout << cmd400() << '\n';
        break;
      case 500:
        cout << cmd500() << '\n';
        break;
      default:
        cout << "Unkown Command!";
        break;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2022-2-morning2.input", "r", stdin);
  freopen("2022-2-morning2.output", "w", stdout);
  for (int i = 0; i < 3; ++i) {
    solution();
  }

  return 0;
}