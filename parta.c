#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        printf("ERROR: No arguments");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (i > 1) {
            putchar(',');
        }

        const char* current = argv[i];
        while (*current != '\0') {
            unsigned char ch = (unsigned char)(*current);
            putchar(toupper(ch));
            ++current;
        }
    }

    return 0;
}
