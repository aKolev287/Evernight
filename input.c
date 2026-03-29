#include "editor.h"
#include <unistd.h>

char read_key(char c) {
    if (c == '\x1b'){
        read(STDIN_FILENO, &c, 1);
        if (c == '['){
            read(STDIN_FILENO, &c, 1);
            if (c == 'A'){
                return 'U';
            } else if (c == 'B'){
                return 'D';
            } else if (c == 'C'){
                return 'R';
            } else {
                return 'L';
            }
        }
    }
    return c;
}