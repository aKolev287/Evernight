#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LINES 1000
#define MAX_COLS 256

typedef struct {
    char **lines;
    int num_lines;
    int capacity;
    int cursor_row;
    int cursor_col;
    char filename[256];
    int state;
} Editor;

struct termios orig_termios;

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

void read_file(Editor *e){
    FILE *file;

    printf("File opened: %s\n", e->filename);
    file = fopen(e->filename, "r");

    // allocate memory, read and check for null
    while(fgets(e->lines[e-> num_lines] = malloc(MAX_COLS * sizeof(char)), MAX_COLS, file) != NULL){
        //printf("%d. %s\r", e->num_lines, e->lines[e -> num_lines]);
        e->num_lines++;
    }
    fclose(file);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// void clear_screen() { 
//     printf("\x1b[2J");
//     printf("\x1b[H");
//     fflush(stdout);
// }
void clear_screen() { 
    printf("\x1b[H\x1b[2J\x1b[3J");
    fflush(stdout);
}
int main(int argc, char *argv[]) {
    enable_raw_mode();
    clear_screen();
    Editor editor = {.num_lines = 0, .cursor_col = 0, .cursor_row = 0};

    if (argc > 1) {
        strncpy(editor.filename, argv[1], 254);
        editor.filename[254] = '\0';
    }

    editor.lines = malloc(MAX_LINES * sizeof(char *));
    char c;
    read_file(&editor);
    printf("Enter a mode\nquit - q\nread - r\n");
    while(1) {
        clear_screen();
        fflush(stdout);
        for(int i = 0; i < editor.num_lines; i++){
            printf("%s\r\n", editor.lines[i]);
        }
        printf("row:%d col:%d\r\n", editor.cursor_row, editor.cursor_col);
        printf("\x1b[%d;%dH", editor.cursor_row + 1, editor.cursor_col + 1);
        
        fflush(stdout); // update now
        read(STDIN_FILENO, &c, 1);
        char special_c = read_key(c);

        //printf("\nThe position of the cursor\nrow:%d\ncol:%d\n", editor.cursor_row, editor.cursor_col);
        
        if (special_c == 'U' && editor.cursor_row > 0) {
            editor.cursor_row--;
        }
        if (special_c == 'D' && editor.cursor_row >= 0) {
            editor.cursor_row++;
        }
        if (special_c == 'L' && editor.cursor_col > 0) {
            editor.cursor_col--;
        } 
        if (special_c == 'R' && editor.cursor_col >= 0) {
            editor.cursor_col++;
        }

        


    }
    printf("\n");
    free(editor.lines);
    editor.lines = NULL;
    return 0;
}