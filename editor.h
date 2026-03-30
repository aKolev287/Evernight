#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>

#define MAX_LINES 1000
#define MAX_COLS 256


// Editor State
struct editor_config {
    char **lines;
    int num_lines;
    int capacity;
    int cursor_row;
    int cursor_col;
    char filename[256];
    char state;
    char key;
    struct termios orig_termios;
};

extern struct editor_config E;

// terminal.c
void disable_raw_mode(void);
void enable_raw_mode(void);
void clear_screen(void);

// void enter_cmd_mode(void);
// void exit_mode(void);
// void edit_mode(void);
// void commands(void);


// file.c
void read_file(void);
void file_open(char *filename);
void refresh_screen(void);
void die(void);

// input.c
char read_key(char c);
void read_command(void);
void insert(void);
void move_cursor(char c);


#endif