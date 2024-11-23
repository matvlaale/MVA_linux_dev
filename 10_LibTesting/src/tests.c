#include <stdio.h>
#include <stdint.h>
// #include <setjmp.h>

/* static jmp_buf escape;

static void
test_abort(void)
{
    longjmp(escape, 1);
} */

/* #define BUF_ABORT test_abort() */
#include "buf.h"

int
main(int argc, char **argv)
{
    /* Benchtest? */
    /*if (argc > 1) {
        uint64_t rng = strtoull(argv[1], 0, 16);
        unsigned long r = 0;
        uint64_t start = uepoch();
        for (int i = 0; i < 300; i++)
            r += bench(&rng);
        double t = (uepoch() - start) / 1e6;
        printf("%.6gs : actual %lu, expect 428859598\n", t, r);
        return 0;
    }

    // volatile due to setjmp() / longjmp()
    volatile int count_pass = 0;
    volatile int count_fail = 0;

//     if (setjmp(escape))
//         abort();

    // initialization, buf_free()
    float *a = 0;
    TEST("capacity init", buf_capacity(a) == 0);
    TEST("size init", buf_size(a) == 0);
    buf_push(a, 1.3f);
    TEST("size 1", buf_size(a) == 1);
    TEST("value", a[0] == (float)1.3f);
    buf_clear(a);
    TEST("clear", buf_size(a) == 0);
    TEST("clear not-free", a != 0);
    buf_free(a);
    TEST("free", a == 0);

    // Clearing an NULL pointer is a no-op
    buf_clear(a);
    TEST("clear empty", buf_size(a) == 0);
    TEST("clear no-op", a == 0);

    // buf_push(), [] operator
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    TEST("size 10000", buf_size(ai) == 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    TEST("match 10000", match == 10000);
    buf_free(ai);

    // buf_grow(), buf_trunc()
    buf_grow(ai, 1000);
    TEST("grow 1000", buf_capacity(ai) == 1000);
    TEST("size 0 (grow)", buf_size(ai) == 0);
    buf_trunc(ai, 100);
    TEST("trunc 100", buf_capacity(ai) == 100);
    buf_free(ai);

    // buf_pop()
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    TEST("size 4", buf_size(a) == 4);
    TEST("pop 3", buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    TEST("size 3", buf_size(a) == 3);
    TEST("pop 2", buf_pop(a) == (float)1.3f);
    TEST("pop 1", buf_pop(a) == (float)1.2f);
    TEST("pop 0", buf_pop(a) == (float)1.1f);
    TEST("size 0 (pop)", buf_size(a) == 0);
    buf_free(a); */

    // Memory allocation failures

    /* volatile int aborted;

    {
        int *volatile p = 0;
        aborted = 0;
        if (!setjmp(escape)) {
            size_t max = (PTRDIFF_MAX - sizeof(struct buf)) / sizeof(*p) + 1;
            buf_grow(p, max);
            buf_grow(p, max);
        } else {
            aborted = 1;
        }
        buf_free(p);
        TEST("out of memory", aborted);
    }

    {
        int *volatile p = 0;
        aborted = 0;
        if (!setjmp(escape)) {
            buf_trunc(p, PTRDIFF_MAX);
        } else {
            aborted = 1;
        }
        buf_free(p);
        TEST("overflow init", aborted);
    }

    {
        int *volatile p = 0;
        aborted = 0;
        if (!setjmp(escape)) {
            buf_trunc(p, 1); // force realloc() use next
            buf_trunc(p, PTRDIFF_MAX);
        } else {
            aborted = 1;
        }
        buf_free(p);
        TEST("overflow grow", aborted);
    } */

    /* printf("%d fail, %d pass\n", count_fail, count_pass);
    return count_fail != 0; */
}
