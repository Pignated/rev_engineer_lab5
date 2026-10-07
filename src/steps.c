/* Lab 5, Part 1A: how far does p + 1 move? */
#include <stdio.h>

int main(void) {
    char  c[6]    = "abcde";
    short s[6]    = {1, 2, 3, 4, 5, 6};
    int   n[6]    = {10, 20, 30, 40, 50, 60};
    long  l[6]    = {100, 200, 300, 400, 500, 600};
    short g[3][5] = {{11, 12, 13, 14, 15},
                     {21, 22, 23, 24, 25},
                     {31, 32, 33, 34, 35}};

    char  *pc = c;
    short *ps = s;
    int   *pn = n;
    long  *pl = l;
    short (*pr)[5] = g;

    printf("char  *       : p+1 is %ld bytes past p\n", (long)((char *)(pc + 1) - (char *)pc));
    printf("short *       : p+1 is %ld bytes past p\n", (long)((char *)(ps + 1) - (char *)ps));
    printf("int   *       : p+1 is %ld bytes past p\n", (long)((char *)(pn + 1) - (char *)pn));
    printf("long  *       : p+1 is %ld bytes past p\n", (long)((char *)(pl + 1) - (char *)pl));
    printf("short (*)[5] : p+1 is %ld bytes past p\n", (long)((char *)(pr + 1) - (char *)pr));
    return 0;
}
