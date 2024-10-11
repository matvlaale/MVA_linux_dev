#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 4) {
        printf("Usage: %s [start] [end] [step]\n", argv[0]);
        return 0;
    }
    int M = 0, N, S = 1;

    if (argc == 2) {
        N = atoi(argv[1]);
    } else if (argc == 3) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
    } else if (argc == 4) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        S = atoi(argv[3]);
    }
    for (int i = M; i < N; i += S) {
        printf("%d\n", i);
    }

    return 0;
}
