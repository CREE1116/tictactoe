#include <stdio.h>
void printField(int arr[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      switch (arr[i][j]) {
        case 1:
          printf("O");
          break;
        case 2:
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
int check(int arr[3][3]) {
  if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != 0)
    return arr[0][0];
  if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[0][0] != 0)
    return arr[0][2];
  for (int i = 0; i < 3; i++) {
    if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != 0)
      return arr[i][0];
    if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] != 0)
      return arr[0][i];
  }
  return 0;
}
int main() {
  int turn = 1;
  int x = 0, y = 0;
  int arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  while (1) {
    printField(arr);
    printf("%d turn-", turn);

    if (turn % 2 != 1)
      printf("O\n");
    else
      printf("X\n");

    scanf("%d %d", &x, &y);
    if (x < 1 || x > 3 || y < 1 || y > 3) {
      printf("\033[2J");  // 전체 화면 지우기
      printf("Out of range\n");
      continue;
    }

    if (arr[y - 1][x - 1] != 0) {
      printf("\033[2J");  // 전체 화면 지우기
      printf("Already filled\n");
      continue;
    } else {
      arr[y - 1][x - 1] = turn % 2 + 1;
      turn++;
    }

    int result = check(arr);
    if (result != 0) {
      printf("\033[2J");  // 전체 화면 지우기
      printField(arr);
      if (result == 1) printf("O win!");
      if (result == 2) printf("X win!");
      break;
    }
    printf("\033[2J");  // 전체 화면 지우기
  }
}
