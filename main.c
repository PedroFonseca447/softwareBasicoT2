#include <stdio.h>
#include "mymemory.h"

int main()
{
    // int v[100];
    //int *v = malloc(sizeof(int)*100);
    mymemory_t *m = mymemory_init(10000);
    int *v = mymemory_alloc(m, sizeof(int)*100);
    for (int i = 0; i < 100; i++)
        v[i] = i + 1;

    char *str = mymemory_alloc(m, sizeof(char)*32);
    sprintf(str, "Ola mundo");

    int *v1 = mymemory_alloc(m, sizeof(int)*10);

    printf("str=%s\n", str);

    // free(str);
    mymemory_free(m, v);

    char *str1 = mymemory_alloc(m, sizeof(char)*16);

    //memory_cleanup(m);

    mymemory_display(m);

    //mymemory_release(m);

   mymemory_stats(m);

   // mymemory_free(m, str);

    return 0;
}
