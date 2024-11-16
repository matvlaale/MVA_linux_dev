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

int have_pass(int maze[][max], int i, int j) {
  if (i < 0 || j < 0 || i >= may || j >= max)
    return 1;
  return maze[i + 1][j] != 0 || maze[i - 1][j] != 0 
         || maze[i][j + 1] != 0 || maze[i][j - 1] != 0;
}

int all_tryed(int try[]) {
  return try[0] && try[1] && try[2] && try[3];
}

int main(/*int argc, char** argv*/) {
  int maze[max][may]/* = {'#'}*/;
  srand(time(NULL));
  for (int i = 0; i < may; ++i) {
    for (int j = 0; j < max; ++j) {
      if (i % 2 == 1 && j % 2 == 1)
        maze[i][j] = 1;
      else
        maze[i][j] = 0;
  	}
  }
  int x, y, next, prev, first, nx, ny/*, to_break = 0, to_end*/;
  for (int ix = 1, iy = 1; iy < may;) {
    x = ix;
    y = iy;
    if (!have_pass(maze, y, x)) {
      next = rand() % 4;
      prev = -1;
      first = -1;
      int try[4] = {0};
      // to_end = 0;
      for (;1;) {
        try[next] = 1;
        if (next == prev) {
          next = rand() % 4;
          continue;
        }
        switch(next) {
          case 0: {nx = x; ny = y - 2; break;}
          case 1: {nx = x + 2; ny = y; break;}
          case 2: {nx = x; ny = y + 2; break;}
          case 3: {nx = x - 2; ny = y; break;}
        }
        // printf("%d-%d -> %d-%d\n", x, y, nx, ny);
        if (!have_pass(maze, ny, nx)) {
          maze[(y + ny) / 2][(x + nx) / 2] = 1;
          x = nx;
          y = ny;
          prev = (next + 2) % 4;
          next = rand() % 4;
          if (first == -1)
            first = (prev + 2) % 4;
        } else if (all_tryed(try) && nx > 0 && ny > 0 && nx < max && ny < may) {
          maze[(y + ny) / 2][(x + nx) / 2] = 1;
          break;
        } /* else if (all_tryed(try)) {
          switch(prev) {
            case 0: {y = y - 2; break;}
            case 1: {x = x + 2; break;}
            case 2: {y = y + 2; break;}
            case 3: {x = x - 2; break;}
            default: {maze[(y + ny) / 2][(x + nx) / 2] = 1; to_break = 1; break;}
          }
          try[0] = 0; try[1] = 0; try[2] = 0; try[3] = 0;
          prev = (prev + 2) % 4;
          next = rand() % 4;
          if (to_break) {
            to_break = 0;
            maze[(y + ny) / 2][(x + nx) / 2] = 1;
            break;
          }
          to_end = 1;
        } */else {
          next = rand() % 4;
        }
      }
    }
    ix += 2;
    if (ix >= max) {
      ix = 1;
      iy += 2;
    }
  }
  out_maze(maze, max, may);
  /*for (int i = 0; i < may; ++i) {
    for (int j = 0; j < max; ++j) {
      
  	}
  }*/
  return 0;
}
