/* Lab 5, Part 2A/2B: where do globals live? */
#include <stdio.h>

long       ticks      = 90000;
int        visits     = 7;
short      rates[5]   = {3, 5, 8, 13, 21};
int        buckets[6];
const int  version    = 12;
static int calls;
char      *motto      = "keep digging";

void touch(void) {
    ticks++;
    visits += 2;
    calls++;
}

short rate_at(int i) {
    return rates[i];
}

int main(void) {
    touch();
    printf("visits is at %p\n", (void *)&visits);
    printf("rates  is at %p\n", (void *)&rates);
    printf("rate_at(3) = %d, calls = %d, buckets[1] = %d, version = %d\n",
           rate_at(3), calls, buckets[1], version);
    printf("motto = %s\n", motto);
    return 0;
}
