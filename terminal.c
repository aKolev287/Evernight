#include "editor.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &E.orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = E.orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void clear_screen() { 
    printf("\x1b[H\x1b[2J\x1b[3J");
    fflush(stdout);
}