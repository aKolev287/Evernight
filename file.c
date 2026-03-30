#include "editor.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void read_file(){
    FILE *file;

    printf("File opened: %s\n", E.filename);
    file = fopen(E.filename, "r");

    // allocate memory, read and check for null
    while(fgets(E.lines[E.num_lines] = malloc(MAX_COLS * sizeof(char)), MAX_COLS, file) != NULL){
        int len = strlen(E.lines[E.num_lines]);
        if (len > 0 && E.lines[E.num_lines][len-1] == '\n')
            E.lines[E.num_lines][len-1] = '\0';
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

}



void die(){
    printf("\n");
    free(E.lines);
    E.lines = NULL;
}

