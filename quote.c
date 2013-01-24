#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>

void init_screen();
void init_curses();
void print_main_menu();
void handle_terminal_resize(int issued_signal);

int main()
{
    int input;

    /* Initialization */
    init_screen();

    /* Handle terminal resizing */
    signal(SIGWINCH, handle_terminal_resize);

    /* The main event loop */
    while ((input = getch()) != 'q' && input != 'Q')
    {
        switch (input)
        {
            case 'R':
            case 'r':
                mvprintw(5, 0, "You pressed R!!");
                clrtoeol();
                break;
        }
    }

    /* We're done */
    endwin();
    return 0;
}

void init_curses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide the cursor
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void print_main_menu()
{
    mvprintw(LINES - 3, 0, "Press <R> to get another quote.");
    mvchgat(LINES - 3, 7, 1, A_BOLD, 1, NULL);
    mvprintw(LINES - 2, 0, "Press <Q> to quit.");
    mvchgat(LINES - 2, 7, 1, A_BOLD, 2, NULL);
    refresh();
}

void init_screen()
{
    init_curses();
    print_main_menu();
}

void handle_terminal_resize(int issued_signal)
{
    print_main_menu();
}
