#include "editor.h"
#include <unistd.h>
#include <string.h>

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

void read_command(){

    read(STDIN_FILENO, &E.key, 1);
    char special_c = read_key(E.key);

    if (E.key == 'i'){
        E.state = 'i';
        insert();
    }

    if (special_c == 'U' || special_c == 'D' || 
        special_c == 'L' || special_c == 'R') {
        move_cursor(special_c);
    }
}

void insert() {
    while(1) {
        char new_char;
        read(STDIN_FILENO, &new_char, 1);
        char special_c = read_key(new_char);
        
        if (special_c == '\x1b') {
            E.state = 'n';
            break;
        }
        if (special_c == 'U' || special_c == 'D' || 
            special_c == 'L' || special_c == 'R') {
            move_cursor(special_c);
            refresh_screen();
            continue;
        }
        
        char *line = E.lines[E.cursor_row];
        memmove(&line[E.cursor_col + 1], &line[E.cursor_col], strlen(line) - E.cursor_col + 1);
        line[E.cursor_col] = new_char;
        E.cursor_col++;
        refresh_screen();
    }
}

void move_cursor(char direction) {
    if (direction == 'U' && E.cursor_row > 0) {
        E.cursor_row--;
        int len = strlen(E.lines[E.cursor_row]);
        if (E.cursor_col > len) E.cursor_col = len;
    }
    if (direction == 'D' && E.cursor_row < E.num_lines - 1) {
        E.cursor_row++;
        int len = strlen(E.lines[E.cursor_row]);
        if (E.cursor_col > len) E.cursor_col = len;
    }
    if (direction == 'L' && E.cursor_col > 0) {
            E.cursor_col--;
    } 
    if (direction == 'R' && E.cursor_col <= strlen(E.lines[E.cursor_row]) - 1) {
        E.cursor_col++;
    }

}