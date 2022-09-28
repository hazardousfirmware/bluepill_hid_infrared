#include <stddef.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    const void* end = src + n;
    while (src < end)
    {
        *(char*) dest = *(char*) src;
        dest++;
        src++;
    }
    return NULL;
}

size_t strlen(const char *s)
{
    const char *end = s;
    while (*end != '\x00')
    {
        end++;
    }
    return end - s;
}
