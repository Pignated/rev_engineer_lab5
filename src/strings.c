/* Lab 5, Part 2C: two kinds of string */
#include <stdio.h>
#include <stdlib.h>

char *msg    = "hello, world";
char  name[] = "analyst";

void show(void) {
    printf("msg  = %s\n", msg);
    printf("name = %s\n", name);
}

int main(int argc, char **argv) {
    int mode = 0;
    if (argc == 2)
        mode = atoi(argv[1]);

    if (mode == 1)
        name[0] = 'A';
    if (mode == 2)
        msg[0] = 'J';

    show();
    return 0;
}
