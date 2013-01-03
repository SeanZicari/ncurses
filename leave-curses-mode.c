#include <ncurses.h>

int main(int argc, char * argv[])
{
    initscr();
    printw("Hello world !!!\n");
    refresh();
    def_prog_mode();
    endwin();
    system("/bin/bash");
    reset_prog_mode();

    refresh();

    printw("Another string.\n");
    refresh();
    getch();
    endwin();
    return 0;
}
