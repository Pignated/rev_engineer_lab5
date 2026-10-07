/* Lab 5, Part 3: who gets in? */

// gcc -O0 -fno-stack-protector -o mystery_bin mystery.c
#include <stdio.h>
#include <string.h>

int check(const char *input) {
    char name[16];
    int  level = 0;

    strcpy(name, input);
    printf("hello, %s\n", name);
    return level;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s your_name_please\n", argv[0]);
        return 1;
    }
    if (check(argv[1]))
        puts("access: granted");
    else
        puts("access: denied");
    return 0;
}
