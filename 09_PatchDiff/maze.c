#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int max = 13;
int may = 13;

void out_maze(int maze[][max], int max, int may) {
  for (int i = 0; i < may; ++i) {
    for (int j = 0; j < max; ++j) {
      printf("%c", ((maze[i][j] == 0) ? '#' : '.'));
  	}
  	printf("\n");
  }
}

int main(/*int argc, char** argv*/) {
  int maze[may][max]/* = {'#'}*/;
  srand(time(NULL));
  for (int i = 0; i < may; ++i) {
    for (int j = 0; j < max; ++j) {
      if (i % 2 == 1 && j % 2 == 1)
        maze[i][j] = 1;
      else if (i == 1)
        maze[i][j] = 1;
      else
        maze[i][j] = 0;
  	}
  }
  maze[1][0] = 0;
  maze[1][max - 1] = 0;
  int x = 1, y = 3, next;
  int group[max], iter = 0;
  for (;1;) {
    next = rand() % 2;
    if (x == max - 2) {
      if (iter == 0) {
        maze[y - 1][x] = 1;
        x += 2;
      } else {
        group[iter++] = x;
        maze[y - 1][group[rand() % iter]] = 1;
        x += 2;
        iter = 0;
      }
    } else if ((next < 1 || iter == 0)) {
      maze[y][x + 1] = 1;
      group[iter++] = x;
      x += 2;
    } else {
      maze[y - 1][group[rand() % iter]] = 1;
      x += 2;
      iter = 0;
    }
    if (x >= max) {
      if (iter != 0) {
        maze[y - 1][group[rand() % iter]] = 1;
        iter = 0;
      }
      x = 1;
      y += 2;
    }
    if (y >= may)
      break;
  }
  out_maze(maze, max, may);
  /*for (int i = 0; i < may; ++i) {
    for (int j = 0; j < max; ++j) {
    
  	}
  }*/
  return 0;
}
