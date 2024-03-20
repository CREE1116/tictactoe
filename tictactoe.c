#include <stdio.h>
typedef enum { EMPTY = 0, USER = 1, COMPUTER = 2 } State;
struct point {
  int x;
  int y;
};
void printField(int board[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      switch (board[i][j]) {
        case USER:
          printf("O");
          break;
        case COMPUTER:
          printf("X");
          break;
        default:
          printf(" ");
          break;
      }
      if (j != 2) printf(" | ");
    }
    printf("\n");
    if (i != 2) printf("----------\n");
  }
}

int check(int board[3][3]) {
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
      board[0][0] != EMPTY)
    return board[0][0];
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
      board[0][0] != EMPTY)
    return board[0][2];
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
        board[i][0] != EMPTY)
      return board[i][0];
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
        board[0][i] != EMPTY)
      return board[0][i];
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == EMPTY) return 0;
    }
  }
  return 3;
}
struct point cpu(int board[3][3]) {
  int row = 0, col = 0;
  if (board[1][1] == EMPTY) {
    struct point p = {1, 1};
    return p;
  }
  // 승리할 수 있는 칸 선택
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] != EMPTY &&
        board[i][2] == EMPTY) {
      row = i;
      col = 2;
      break;
    }
    if (board[i][0] == board[i][2] && board[i][2] != EMPTY &&
        board[i][1] == EMPTY) {
      row = i;
      col = 1;
      break;
    }
    if (board[i][1] == board[i][2] && board[i][2] != EMPTY &&
        board[i][0] == EMPTY) {
      row = i;
      col = 0;
      break;
    }
    if (board[0][i] == board[1][i] && board[1][i] != EMPTY &&
        board[2][i] == EMPTY) {
      row = 2;
      col = i;
      break;
    }
    if (board[0][i] == board[2][i] && board[2][i] != EMPTY &&
        board[1][i] == EMPTY) {
      row = 1;
      col = i;
      break;
    }
    if (board[1][i] == board[2][i] && board[2][i] != EMPTY &&
        board[0][i] == EMPTY) {
      row = 0;
      col = i;
      break;
    }
    if (board[i][0] == board[1][1] && board[1][1] != EMPTY &&
        board[2][2] == EMPTY) {
      row = 2;
      col = 2;
      break;
    }
    if (board[i][0] == board[2][2] && board[2][2] != EMPTY &&
        board[1][1] == EMPTY) {
      row = 1;
      col = 1;
      break;
    }
    if (board[i][2] == board[1][1] && board[1][1] != EMPTY &&
        board[2][0] == EMPTY) {
      row = 2;
      col = 0;
      break;
    }
    if (board[0][2] == board[1][1] && board[1][1] != EMPTY &&
        board[2][0] == EMPTY) {
      row = 0;
      col = 2;
      break;
    }
  }
  // 패배를 막을 수 있는 칸 선택
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] != COMPUTER &&
        board[i][2] == EMPTY) {
      row = i;
      col = 2;
      break;
    }
    if (board[i][0] == board[i][2] && board[i][2] != COMPUTER &&
        board[i][1] == EMPTY) {
      row = i;
      col = 1;
      break;
    }
    if (board[i][1] == board[i][2] && board[i][2] != COMPUTER &&
        board[i][0] == EMPTY) {
      row = i;
      col = 0;
      break;
    }
    if (board[0][i] == board[1][i] && board[1][i] != COMPUTER &&
        board[2][i] == EMPTY) {
      row = 2;
      col = i;
      break;
    }
    if (board[0][i] == board[2][i] && board[2][i] != COMPUTER &&
        board[1][i] == EMPTY) {
      row = 1;
      col = i;
      break;
    }
    if (board[1][i] == board[2][i] && board[2][i] != COMPUTER &&
        board[0][i] == EMPTY) {
      row = 0;
      col = i;
      break;
    }
    if (board[i][0] == board[1][1] && board[1][1] != COMPUTER &&
        board[2][2] == EMPTY) {
      row = 2;
      col = 2;
      break;
    }
    if (board[i][0] == board[2][2] && board[2][2] != COMPUTER &&
        board[1][1] == EMPTY) {
      row = 1;
      col = 1;
      break;
    }
    if (board[i][2] == board[1][1] && board[1][1] != COMPUTER &&
        board[2][0] == EMPTY) {
      row = 2;
      col = 0;
      break;
    }
    if (board[0][2] == board[1][1] && board[1][1] != COMPUTER &&
        board[2][0] == EMPTY) {
      row = 0;
      col = 2;
      break;
    }
  }
  struct point p = {col, row};
  return p;
}
int main() {
  int turn = 1;
  int x = 0, y = 0;
  int board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  while (1) {
    printField(board);
    if (turn % 2 == 1) {
      scanf("%d %d", &x, &y);
      if (x < 1 || x > 3 || y < 1 || y > 3) {
        printf("\033[2J");  // 전체 화면 지우기
        printf("Out of range\n");
        continue;
      }
      if (board[y - 1][x - 1] != 0) {
        printf("\033[2J");  // 전체 화면 지우기
        printf("Already filled\n");
        continue;
      }
      board[y - 1][x - 1] = USER;
    } else {
      struct point cpuResult = cpu(board);
      board[cpuResult.y][cpuResult.x] = COMPUTER;
    }
    int result = check(board);
    if (result != 0) {
      printf("\033[2J");  // 전체 화면 지우기
      printField(board);
      if (result == USER) printf("O win!");
      if (result == COMPUTER) printf("X win!");
      if (result == 3) printf("Draw!");
      break;
    }
    turn++;
    // 사용자 대전 코드
    //  printf("%d turn-", turn);

    // if (turn % 2 != 1)
    //   printf("O\n");
    // else
    //   printf("X\n");

    // scanf("%d %d", &x, &y);

    // if (x < 1 || x > 3 || y < 1 || y > 3) {
    //   printf("\033[2J");  // 전체 화면 지우기
    //   printf("Out of range\n");
    //   continue;
    // }

    // if (board[y - 1][x - 1] != 0) {
    //   printf("\033[2J");  // 전체 화면 지우기
    //   printf("Already filled\n");
    //   continue;
    // } else {
    //   board[y - 1][x - 1] = turn % 2 + 1;
    //   turn++;
    // }

    // int result = check(board);
    // if (result != 0) {
    //   printf("\033[2J");  // 전체 화면 지우기
    //   printField(board);
    //   if (result == USER) printf("O win!");
    //   if (result == COMPUTER) printf("X win!");
    //   if (result == 3) printf("Draw!");
    //   break;
    // }
    // printf("\033[2J");  // 전체 화면 지우기
  }
}
