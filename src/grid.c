/* Lab 5, Part 1B: a 2D array and one lookup */
#include <stdio.h>

short cell(short t[][6], int r, int c) {
    return t[r][c];
}

int main(void) {
    short t[4][6] = {{ 11,  12,  13,  14,  15,  16},
                     { 21,  22,  23,  24,  25,  26},
                     { 31,  32,  33,  34,  35,  36},
                     { 41,  42,  43,  44,  45,  46}};

    printf("cell(2, 3) = %d\n", cell(t, 2, 3));
    return 0;
}
