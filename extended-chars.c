#include <ncurses.h>

typedef struct character
{
    char string[30];
    char special_char;
} PrintedChar;

void main(int argc, char * argv[])
{
    PrintedChar chars[31] = { {"Upper Left Corner", ACS_ULCORNER},
                              {"Lower Left Corner", ACS_LLCORNER},
                              {"Lower Right Corner", ACS_LRCORNER},
                              {"Tee Pointing Right", ACS_LTEE},
                              {"Tee Pointing Left", ACS_RTEE},
                              {"Tee Pointing Up", ACS_BTEE},
                              {"Tee Pointing Down", ACS_TTEE},
                              {"Horizontal Line", ACS_HLINE},
                              {"Vertical Line", ACS_VLINE},
                              {"Large Plus or Cross Over", ACS_PLUS},
                              {"Scan Line 1", ACS_S1},
                              {"Scan Line 3", ACS_S3},
                              {"Scan Line 7", ACS_S7},
                              {"Scan Line 9", ACS_S9},
                              {"Diamond", ACS_DIAMOND},
                              {"Checker Board (Stipple)", ACS_CKBOARD},
                              {"Degree Symbol", ACS_DEGREE},
                              {"Plus/Minus Symbol", ACS_PLMINUS},
                              {"Bullet", ACS_BULLET},
                              {"Arrow Pointing Left", ACS_LARROW},
                              {"Arrow Pointing Right", ACS_RARROW},
                              {"Arrow Pointing Down", ACS_DARROW},
                              {"Arrow Pointing Up", ACS_UARROW},
                              {"Board of Squares", ACS_BOARD},
                              {"Lantern Symbol", ACS_LANTERN},
                              {"Solid Square Block", ACS_BLOCK},
                              {"Less/Equal Sign", ACS_LEQUAL},
                              {"Greater/Equal Sign", ACS_GEQUAL},
                              {"Pi", ACS_PI},
                              {"Not Equal", ACS_NEQUAL},
                              {"UK Pound Sign", ACS_STERLING} };
    size_t chars_size = sizeof(chars) / sizeof(chars[0]);
    int i = 0;

    initscr();

    for (i = 0; i < chars_size; i++)
    {
        printw("%30s: ", chars[i].string);
        addch(chars[i].special_char);
        printw("\n");
    }

    refresh();
    getch();
    endwin();
}
