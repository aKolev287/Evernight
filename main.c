#include <string.h>

#include "editor.h"

struct editor_config E;

void initEditor(void){
    E.num_lines = 0;
    E.cursor_col = 0; E.cursor_row = 0;
}

int main(int argc, char *argv[]) {
    enable_raw_mode();
    clear_screen();
    initEditor();

    if (argc > 1) {
        strncpy(E.filename, argv[1], 254);
        E.filename[254] = '\0';
        file_open(E.filename);
    }

    while(1) {
        refresh_screen();
    }
    
    die();
    return 0;
}