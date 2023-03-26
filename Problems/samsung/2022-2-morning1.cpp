// 싸움땅
// 삼성 2022년도 하반기 오전 1번
// 출처: https://www.codetree.ai/training-field/frequent-problems/battle-ground

/**
 * n x n 크기의 격자에서 진행되며, 각 격자에는 무기들이 있을 수 있음
 * 초기에는 무기들이 없는 빈 격자에 플레이어들이 위치하며 각 플레이어는 초기 능력치를 가짐
 * 빨간색 배경의 숫자는 총의 공격력 or 플레이어의 초기 능력치, 노란색 배경의 숫자는 플레이어 번호
 * 한 라운드 진행 과정
 * 1-1. 첫번째 플레이어부터 순차적으로 본인이 향하고 있는 방향대로 한 칸만큼 이동
 *      만약 해당 방향으로 나갈 때 격자를 벗어나는 경우에는 정반대로 방향을 바꾸어 이동
 * 2-1. 만약 이동한 방향에 플레이어가 없다면 해당 칸에 총이 있는지 확인 후 획득
 *      이미 총을 가지고 있는 경우 공격력이 더 쎈 총을 획득하고 나머지 총은 해당 격자에 둠
 * 2-2-1. 만약 이동한 방향에 플레이어가 있다면 두 플레이어가 싸우게 됨
 *        해당 플레이어의 초기 능력치와 가지고 있는 총의 공격력 합을 비교하여 더 큰 플에이어가 이김
 *        만일 이 수치가 같은 경우 플레이어의 초기 능력치가 높은 플레이어가 승리
 *        이긴 플레이어는 그 수치 차이만큼을 포인트로 획득
 * 2-2-2. 진 플레이어는 본인이 가지고 있는 총을 해당 격자에 내려놓고, 원래 방향으로 한 칸 이동
 *        만약 이동하려는 칸에 다른 플레이어가 있거나 격자 범위 밖인 경우 오른쪽으로 90도씩 회전하여 빈칸으로 이동
 *        만약 해당 칸에 총이 있다면, 가장 공격력이 높은 총을 획득하고 나머지 총들은 격자에 내려놓음
 * 2-2-3. 이긴 플레이어는 승리한 칸에 떨어져 있는 총들과 원래 들고 있던 총 중 가장 공격력이 높은 총을 획득
 * 위 과정을 1번부터 n번 플레이어까지 순차적으로 진행하면 1라운드가 끝남
 * k라운드 동안 게임을 진행하면서 각 플레이어들이 획득한 포인트를 출력하는 프로그램 작성
 * 
 * 입력:
 * 첫번째 줄에 격자의 크기 n, 플레이어의 수 m, 라운드의 수 k가 공백을 사이에 두고 주어짐
 * (2 <= n <= 20, 1 <= m <= min(n^2, 30), 1 <= k <= 500)
 * 이후 n개의 줄에 걸쳐 격자에 있는 총의 정보가 주어짐. 0은 빈칸, 0보다 큰 값은 총의 공격력
 * 이후 m개의 줄에 걸쳐 플레이어들의 위치 (x,y), 방향 d, 초기 능력치 s 정보가 주어짐
 * 방향 d는 0부터 3까지 순서대로 상우하좌를 의미
 * 각 플레이어의 위치는 겹치지 않게 주어지며, 플레이어의 초기 위치에는 총이 존재하지 않음
 * 
 * 출력:
 * k라운드 동안 게임을 진행하면서 각 플레이어들이 획득한 포인트를 공백을 사이에 두고 출력
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m, k;

struct Grid {
  priority_queue<int> guns;
  int player_id;

  Grid() {
    player_id = -1;
  }
};
Grid grid[20][20];

struct Player {
  int id;
  int x, y, d, s;
  int gun;
  int score;
};
Player players[30];

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

bool isInRange(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void movePlayer(int player_num) {
  Player& player = players[player_num];
  Grid& old_grid = grid[player.x][player.y];

  // 1-1.
  int nx = player.x + dx[player.d];
  int ny = player.y + dy[player.d];
  if (!isInRange(nx, ny)) {
    player.d = (player.d + 2) % 4;
    nx = player.x + dx[player.d];
    ny = player.y + dy[player.d];
  }
  player.x = nx;
  player.y = ny;
  old_grid.player_id = -1;

  Grid& next_grid = grid[nx][ny];
  if (next_grid.player_id == -1) {
    // 2-1.
    if (!next_grid.guns.empty() && next_grid.guns.top() > player.gun) {
      next_grid.guns.push(player.gun);
      player.gun = next_grid.guns.top();
      next_grid.guns.pop();
    }
    next_grid.player_id = player.id;
    return;
  } else {
    // 2-2-1.
    Player& enermy = players[next_grid.player_id];
    int winner_id = player.id;
    int loser_id = enermy.id;
    if (enermy.s + enermy.gun > player.s + player.gun
       || ((enermy.s + enermy.gun) == (player.s + player.gun) && enermy.s > player.s)) {
      winner_id = enermy.id;
      loser_id = player.id;
    }
    Player& winner = players[winner_id];
    Player& loser = players[loser_id];
    next_grid.player_id = winner.id;
    winner.score += winner.s + winner.gun - loser.s - loser.gun;

    // 2-2-2.
    next_grid.guns.push(loser.gun);
    loser.gun = 0;
    int loser_nx = loser.x + dx[loser.d];
    int loser_ny = loser.y + dy[loser.d];
    while (!isInRange(loser_nx, loser_ny) || grid[loser_nx][loser_ny].player_id >= 0) {
      loser.d = (loser.d + 1) % 4;
      loser_nx = loser.x + dx[loser.d];
      loser_ny = loser.y + dy[loser.d];
    }
    Grid& loser_grid = grid[loser_nx][loser_ny];
    loser.x = loser_nx;
    loser.y = loser_ny;
    loser_grid.player_id = loser.id;
    if (!loser_grid.guns.empty() && loser_grid.guns.top() > loser.gun) {
      loser_grid.guns.push(loser.gun);
      loser.gun = loser_grid.guns.top();
      loser_grid.guns.pop();
    }

    // 2-2-3.
    if (!next_grid.guns.empty() && next_grid.guns.top() > winner.gun) {
      next_grid.guns.push(winner.gun);
      winner.gun = next_grid.guns.top();
      next_grid.guns.pop();
    }
  }
}

void init() {
  for (int y = 0; y < 20; ++y) {
    for (int x = 0; x < 20; ++x) {
      grid[y][x] = Grid();
    }
  }

  for (int i = 0; i < 30; ++i) {
    players[i] = Player();
  }
}

void solution() {
  init();

  cin >> n >> m >> k;

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      int g;
      cin >> g;
      if (g > 0) {
        grid[x][y].guns.push(g);
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    Player& player = players[i];
    player.id = i;
    cin >> player.x >> player.y >> player.d >> player.s;
    --player.x;
    --player.y;
    grid[player.x][player.y].player_id = i;
  }

  while (k--) {
    for (int i = 0; i < m; ++i) {
      movePlayer(i);
    }
  }

  for (int i = 0; i < m; ++i) {
    cout << players[i].score << ' ';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2022-2-morning1.input", "r", stdin);
  freopen("2022-2-morning1.output", "w", stdout);
  for (int i = 0; i < 7; ++i) {
    solution();
  }

  return 0;
}