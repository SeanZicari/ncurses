/*
 * =====================================================================================
 *
 *       Filename:  panel_resizing.c
 *
 *    Description:  Part of the ncurses howto tutorials.
 *
 *        Version:  1.0
 *        Created:  01/05/13 06:19:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sean Zicari (sean.zicari@gmail.com)
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <panel.h>

#define NLINES 0
#define NCOLS 0

#include "curses_tutorials.h"

void main()
{
    WINDOW     *my_wins[3];
    PANEL      *my_panels[3];
    PANEL_DATA *top;
    PANEL      *stack_top;
    WINDOW     *temp_win, *old_win;
    int         ch, newx, newy, neww, newh, size = false, move = false, i = 0;
    size_t      num_wins = sizeof my_wins / sizeof(my_wins[0]);

    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, true);

    /* Initialize all the colors */
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    init_wins(my_wins, num_wins);

    for (i = 0; i < num_wins; i++)
        my_panels[i] = new_panel(my_wins[i]);

    set_user_ptrs(my_panels, num_wins);
    /* Update the stacking order */
    update_panels();

    /* Show it on the screen */
    attron(COLOR_PAIR(4));
    mvprintw(LINES - 3, 0, "Use 'm' for moving, 'r' for resizing");
    mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to exit)");
    attroff(COLOR_PAIR(4));
    doupdate();

    stack_top = my_panels[2];
    top = (PANEL_DATA *)panel_userptr(stack_top);
    newx = top->x;
    newy = top->y;
    neww = top->w;
    newh = top->h;

    while((ch = getch()) != KEY_F(1))
    {
        switch(ch)
        {
            case 9: /* Tab key */
                top = (PANEL_DATA *)panel_userptr(stack_top);
                top_panel(top->next);
                stack_top = top->next;
                top = (PANEL_DATA *)panel_userptr(stack_top);
                newx = top->x;
                newy = top->y;
                neww = top->w;
                newh = top->h;
                break;
            case 'r': /* Resize */
                size = true;
                attron(COLOR_PAIR(4));
                mvprintw(LINES - 4, 0, "Entered Resizing: Use arrow keys to resize and press <ENTER> to end resizing");
                refresh();
                attroff(COLOR_PAIR(4));
                break;
            case 'm': /* Move */
                attron(COLOR_PAIR(4));
                mvprintw(LINES - 4, 0, "Entered moving: Use arrow keys to move and press <ENTER> to end moving.");
                refresh();
                attroff(COLOR_PAIR(4));
                move = true;
                break;
            case KEY_LEFT:
                if (size == true)
                {
                    --newx;
                    --neww;
                }
                if (move == true)
                    --newx;
                break;
            case KEY_RIGHT:
                if (size == true)
                {
                    --newy;
                    --neww;
                }
                if (move == true)
                    --newy;
                break;
            case KEY_UP:
                if (size == true)
                {
                    --newy;
                    ++newh;
                }
                if (move == true)
                    --newy;
                break;
            case KEY_DOWN:
                if (size == true)
                {
                    ++newy;
                    --newh;
                }
                if (move == true)
                    ++newy;
                break;
            case 10: /* Enter key */
                mvprintw(0, 0, "DEBUG: Before resize operations");
                getch();
                move(LINES - 4, 0);
                clrtoeol();
                refresh();

                if (size == true)
                {
                    mvprintw(0, 0, "DEBUG: Before panel_window");
                    clrtoeol();
                    refresh();
                    getch();
                    old_win = panel_window(stack_top);
                    move(0, 0);
                    clrtoeol();
                    mvprintw(0, 0, "DEBUG: Before temp_win");
                    refresh();
                    getch();
                    temp_win = newwin(newh, neww, newy, newx);
                    move(0, 0);
                    clrtoeol();
                    mvprintw(0, 0, "DEBUG: Before replace_panel");
                    refresh();
                    getch();
                    replace_panel(stack_top, temp_win);
                    move(0, 0);
                    clrtoeol();
                    mvprintw(0, 0, "DEBUG: Before win_show");
                    refresh();
                    getch();
                    win_show(temp_win, top->label, top->label_color);
                    move(0, 0);
                    clrtoeol();
                    mvprintw(0, 0, "DEBUG: Before delete window");
                    refresh();
                    getch();
                    delwin(old_win);
                    size = false;
                }
                if (move == true)
                {
                    move_panel(stack_top, newy, newx);
                    move = false;
                }
                break;
        }

        attron(COLOR_PAIR(4));
        mvprintw(LINES - 3, 0, "Use 'm' for moving, 'r' for resizing");
        mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to exit)");
        attroff(COLOR_PAIR(4));
        refresh();
        update_panels();
        doupdate();
    }

    endwin();
}
