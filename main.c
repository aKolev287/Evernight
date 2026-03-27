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

void read_file(Editor *e){
    FILE *file;

    printf("File opened: %s\n", e->filename);
    file = fopen(e->filename, "r");

    // allocate memory, read and check for null
    while(fgets(e->lines[e-> num_lines] = malloc(MAX_COLS * sizeof(char)), MAX_COLS, file) != NULL){
        printf("%d. %s\r", e->num_lines, e->lines[e -> num_lines]);
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

void clear_screen() { 
    printf("\x1b[2J");
    printf("\x1b[H");
}

int main(int argc, char *argv[]) {
    enable_raw_mode();
    clear_screen();
    Editor editor = {.num_lines = 1};
    if (argc > 1) {
        strncpy(editor.filename, argv[1], 254);
        editor.filename[254] = '\0';
    }

    editor.lines = malloc(MAX_LINES * sizeof(char *));
    char c;

    clear_screen();
    printf("Enter a mode\nquit - q\nread - r\n");
    while(1) {
        
        read(STDIN_FILENO, &c, 1);
        if (c == 'q'){
            break;
        } else if (c == 'r') {
            read_file(&editor);
            break;
        }
    }
    printf("\n");
    free(editor.lines);
    editor.lines = NULL;
    return 0;
}