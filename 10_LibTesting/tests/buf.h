/* buf.h --- growable memory buffers for C99
 * This is free and unencumbered software released into the public domain.
 *
 *   buf_size(v)     : return the number of elements in the buffer (size_t)
 *   buf_capacity(v) : return the total capacity of the buffer (size_t)
 *   buf_free(v)     : destroy and free the buffer
 *   buf_push(v, e)  : append an element E to the end
 *   buf_pop(v)      : remove and return an element E from the end
 *   buf_grow(v, n)  : increase buffer capactity by (ptrdiff_t) N elements
 *   buf_trunc(v, n) : set buffer capactity to exactly (ptrdiff_t) N elements
 *   buf_clear(v, n) : set buffer size to 0 (for push/pop)
 *
 * Note: buf_push(), buf_grow(), buf_trunc(), and buf_free() may change
 * the buffer pointer, and any previously-taken pointers should be
 * considered invalidated.
 *
 * Example usage:
 *
 *     float *values = 0;
 *     for (size_t i = 0; i < 25; i++)
 *         buf_push(values, rand() / (float)RAND_MAX);
 *     for (size_t i = 0; i < buf_size(values); i++)
 *         printf("values[%zu] = %f\n", i, values[i]);
 *     buf_free(values);
 */
#include <stddef.h>
#include <stdlib.h>

#ifndef BUF_INIT_CAPACITY
#  define BUF_INIT_CAPACITY 8
#endif

#ifndef BUF_ABORT
#  define BUF_ABORT abort()
#endif

struct buf {
    size_t capacity;
    size_t size;
    char buffer[];
};

#define buf_ptr(v) \
    ((struct buf *)((char *)(v) - offsetof(struct buf, buffer)))

#define buf_free(v) \
    do { \
        if (v) { \
            free(buf_ptr((v))); \
            (v) = 0; \
        } \
    } while (0)

#define buf_size(v) \
    ((v) ? buf_ptr((v))->size : 0)

#define buf_capacity(v) \
    ((v) ? buf_ptr((v))->capacity : 0)

#define buf_push(v, e) \
    do { \
        if (buf_capacity((v)) == buf_size((v))) { \
            (v) = buf_grow1(v, sizeof(*(v)), \
                            !buf_capacity((v)) ? \
                              BUF_INIT_CAPACITY : \
                              buf_capacity((v))); \
        } \
        (v)[buf_ptr((v))->size++] = (e); \
    } while (0)

#define buf_pop(v) \
    ((v)[--buf_ptr(v)->size])

#define buf_grow(v, n) \
    ((v) = buf_grow1((v), sizeof(*(v)), n))

#define buf_trunc(v, n) \
    ((v) = buf_grow1((v), sizeof(*(v)), n - buf_capacity(v)))

#define buf_clear(v) \
    ((v) ? (buf_ptr((v))->size = 0) : 0)


static void *
buf_grow1(void *v, size_t esize, ptrdiff_t n)
{
    struct buf *p;
    size_t max = (size_t)-1 - sizeof(struct buf);
    if (v) {
        p = buf_ptr(v);
        if (n > 0 && p->capacity + n > max / esize)
            goto fail; /* overflow */
        p = realloc(p, sizeof(struct buf) + esize * (p->capacity + n));
        if (!p)
            goto fail;
        p->capacity += n;
        if (p->size > p->capacity)
            p->size = p->capacity;
    } else {
        if ((size_t)n > max / esize)
            goto fail; /* overflow */
        p = malloc(sizeof(struct buf) + esize * n);
        if (!p)
            goto fail;
        p->capacity = n;
        p->size = 0;
    }
    return p->buffer;
fail:
    BUF_ABORT;
    return 0;
}

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x) \
    do { \
        if (x) { \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++; \
        } else { \
            printf(C_RED("FAIL") " %s\n", s); \
            count_fail++; \
        } \
    } while (0)

static uint32_t
pcg32(uint64_t *s)
{
    uint64_t m = 0x5851f42d4c957f2d;
    uint64_t a = 0x8b260b70b8e98891;
    uint64_t p = *s;
    uint32_t x = ((p >> 18) ^ p) >> 27;
    uint32_t r = p >> 59;
    *s = p * m + a;
    return (x >> r) | (x << (-r & 31u));
}

static unsigned long
bench(uint64_t *rng)
{
    unsigned long r = 0;
    uint32_t n = 1000000 + pcg32(rng) % 4000000;
    float *buf = 0;

    for (uint32_t i = 0; i < n; i++)
        buf_push(buf, pcg32(rng) / (double)UINT32_MAX);

    float threshold = pcg32(rng) / (double)UINT32_MAX;
    for (uint32_t i = 0; i < n; i++)
        r += buf[i] > threshold;

    buf_free(buf);
    return r;
}

#ifdef _WIN32
#include <windows.h>
uint64_t
uepoch(void)
{
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t tt = ft.dwHighDateTime;
    tt <<= 32;
    tt |= ft.dwLowDateTime;
    tt /=10;
    tt -= UINT64_C(11644473600000000);
    return tt;
}
#else
#include <sys/time.h>
uint64_t
uepoch(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif
