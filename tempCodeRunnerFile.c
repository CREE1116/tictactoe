   if (result != 0) {
      printf("\033[2J");  // 전체 화면 지우기
      printField(board);
      if (result == USER) printf("O win!");
      if (result == COMPUTER) printf("X win!");
      if (result == 3) printf("Draw!");
      break;
    }
    printf("\033[2J");  // 전체 화면 지우기