#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 2
#define COLS_NUMS 5

int main(int argc, char** argv) {
  if (argc <= 1) {
    printf("No input file.\nUsage: ./Shower file.glob\n");
    return 0;
  }
  // Read file in RAM
  FILE *inp = fopen(argv[1], "r");
  int lineCount = 0, charCount = 0, allocCount = 16, fileAllocCount = 128, isEnd = 0;
  int *strLens = (int *) malloc(fileAllocCount * sizeof(int));
  char **RAMfile, *nextString = (char *) malloc(allocCount * sizeof(char));
  RAMfile = (char **) malloc(fileAllocCount * sizeof(char *));
  while (1) {
    nextString[charCount] = (char) fgetc(inp);
    if (nextString[charCount] == EOF)
      isEnd = 1;
    if (nextString[charCount] == '\n' || isEnd) {
      nextString[charCount] = '\0';
      (RAMfile + lineCount++)[0] = nextString;
      strLens[lineCount - 1] = charCount;
      if (isEnd)
        break;
      if (lineCount >= fileAllocCount - 2) {
        fileAllocCount *= 2;
        RAMfile = (char **) realloc(RAMfile, fileAllocCount * sizeof(char **));
        strLens = (int *) realloc(strLens, fileAllocCount * sizeof(int));
      }
      charCount = 0;
      allocCount = 16;
      nextString = (char *) malloc(allocCount * sizeof(char));
      continue;
    }
    if (++charCount >= allocCount - 2) {
      allocCount *= 2;
      nextString = (char *) realloc(nextString, allocCount * sizeof(char));
    }
  }
  fclose(inp);

  // printf("File %s, %d lines\n\n", argv[1], lineCount);

  // for (int i = 0; i < lineCount; ++i) {
  //   printf("%s\n", RAMfile[i]);
  //   free(RAMfile[i]);
  // }

  int max_base_col = 0;
  for (int i = 0; i < lineCount; ++i) {
    if (strLens[i] > max_base_col)
      max_base_col = strLens[i];
  }

  WINDOW *win;
  int c = 0;

  initscr();
  noecho();
  cbreak();
  printw("File: %s, %d lines", argv[1], lineCount);
  refresh();

  int lines = LINES - 2 * DX, cols = COLS - 2 * DX;
  int base_num = 0, outNum = 0, col_num = 0;
  win = newwin(lines, cols, DX, DX);
  keypad(win, TRUE);
  scrollok (win, TRUE);
  box(win, 0, 0);
  wmove(win, 1, 0);
  int max_l, max_c;
  getmaxyx(win, max_l, max_c);
  max_l -= DX;
  max_c -= DX;
  int shift = COLS_NUMS + 2;
  do {
    // wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));
    if (!strcmp(keyname(c), "KEY_DOWN")) {
      if (base_num <= lineCount - 15)
        ++base_num;
    } else if (!strcmp(keyname(c), "KEY_UP")) {
      if (base_num > 0)
        --base_num;
    } else if (!strcmp(keyname(c), "KEY_RIGHT")) {
      if (col_num <= max_base_col - 15)
        ++col_num;
    } else if (!strcmp(keyname(c), "KEY_LEFT")) {
      if (col_num > 0)
        --col_num;
    }
    werase(win);
    outNum = base_num;
    wprintw(win, "\n");
    for (int i = base_num; i < lineCount; ++i) {
      wprintw(win, "%*d: ", COLS_NUMS, ++outNum);

      int start = 0;
      if (col_num >= strLens[outNum - 1])
        wprintw(win, "\n");
      else
        wprintw(win, "%.*s\n", max_c - shift, RAMfile[outNum - 1] + col_num);

      start += max_c - shift;
      if (i + 1 >= max_l + base_num)
        break;
    }
    box(win, 0, 0);
    wrefresh(win);
  } while ((c = wgetch(win)) != 27);
  endwin();

// KEY_UP 259 KEY_DOWN 258

  // Free the memory
  for (int i = 0; i < lineCount; ++i)
    free(RAMfile[i]);

  return 0;
}
