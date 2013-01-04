#include <panel.h>

#define NLINES 10
#define NCOLS 40

void init_wins(WINDOW * wins[], int n);
void win_show(WINDOW * win, char * label, int label_color);
void print_in_middle(WINDOW * win, int starty, int startx, int width, char * string, chtype color);

int main(int argc, char * argv[])
{
    WINDOW * my_wins[3];
    PANEL  * my_panels[3];
    PANEL  * top;
    int      ch;

    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad();
}
