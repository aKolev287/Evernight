#include "editor.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void read_file(){
    FILE *file;

    printf("File opened: %s\n", E.filename);
    file = fopen(E.filename, "r");

    // allocate memory, read and check for null
    while(fgets(E.lines[E.num_lines] = malloc(MAX_COLS * sizeof(char)), MAX_COLS, file) != NULL){
        //printf("%d. %s\r", e->num_lines, e->lines[e -> num_lines]);
        E.num_lines++;
    }
    fclose(file);
}

void file_open(char *filename){
    clear_screen();
    E.lines = malloc(MAX_LINES * sizeof(char *));

    fflush(stdout);
    printf("Opened: %s", filename);

    read_file();
}

void refresh_screen() {
    clear_screen();
    for(int i = 0; i < E.num_lines; i++){
            printf("%s\r\n", E.lines[i]);
    }
    printf("\x1b[%d;%dH", E.cursor_row + 1, E.cursor_col + 1);
    fflush(stdout);
    read(STDIN_FILENO, &E.key, 1);
    char special_c = read_key(E.key);

    if (special_c == 'U' && E.cursor_row > 0) {
            E.cursor_row--;
    }
    if (special_c == 'D' && E.cursor_row >= 0) {
            E.cursor_row++;
    }
    if (special_c == 'L' && E.cursor_col > 0) {
            E.cursor_col--;
    } 
    if (special_c == 'R' && E.cursor_col >= 0) {
            E.cursor_col++;
    }
}

void die(){
    printf("\n");
    free(E.lines);
    E.lines = NULL;
}

