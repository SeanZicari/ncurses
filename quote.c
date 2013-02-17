#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>

void init_curses();
void print_main_menu();
void display_ui(WINDOW *);
void handle_terminal_resize(int issued_signal);
void set_up_resize_handler();
void main_loop(WINDOW *);

int main()
{
    WINDOW * quote_window = NULL;

    /* Initialization */
    init_curses();
    //print_main_menu();

    display_ui(quote_window);

    /* Handle terminal resizing */
    set_up_resize_handler();

    refresh();

    /* The main event loop */
    main_loop(quote_window);

    /* We're done */
    endwin();
    return 0;
}

void main_loop(WINDOW * quote_window)
{
    int input;

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
}

void init_curses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide the cursor

    if (has_colors())
        start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void print_main_menu()
{
    int y, x;

    getmaxyx(stdscr, y, x);
    mvprintw(0, 0, "Max y: %d, max x: %d.", y, x);

    mvprintw(y - 3, 0, "Press <R> to get another quote.");
    mvchgat(y - 3, 7, 1, A_BOLD, 1, NULL);
    mvprintw(y - 2, 0, "Press <Q> to quit.");
    mvchgat(y - 2, 7, 1, A_BOLD, 2, NULL);

    refresh();
}

void display_ui(WINDOW * quote_window)
{
    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);

    /* Create the window where the quotes will be displayed */
    quote_window = newwin(25, max_x, 2, 1);
    box(quote_window, 0, 0);

    wrefresh(quote_window);
}

void set_up_resize_handler()
{
    struct sigaction sig_int_handler;

    sig_int_handler.sa_handler = &handle_terminal_resize;
    sigemptyset(&sig_int_handler.sa_mask);
    sig_int_handler.sa_flags = 0;
    sigaction(SIGWINCH, &sig_int_handler, NULL);
}

void handle_terminal_resize(int issued_signal)
{
    print_main_menu();
}
