#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct _PANEL_DATA
{
    int x, y, w, h;
    char label[80];
    int label_color;
    PANEL * next;
} PANEL_DATA;

/*
 * =====================================================================================
 *
 *       Filename:  curses_tutorials.h
 *
 *    Description:  A header file to conveniently collect all of the repeated functions
 *                  I would normally have to type over and over.
 *
 *        Version:  1.0
 *        Created:  01/05/13 06:24:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sean Zicari
 *   Organization:  
 *
 * =====================================================================================
 */

void init_wins(WINDOW *wins[], size_t n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void set_user_ptrs(PANEL *panels[], int n);

/* Put all the windows */
void init_wins(WINDOW * wins[], size_t n)
{
    int  x, y, i;
    char label[80];

    y = 2;
    x = 10;

    for (i = 0; i < n; ++i)
    {
        wins[i] = newwin(NLINES, NCOLS, y, x);
        sprintf(label, "Window Number %d", i + 1);
        win_show(wins[i], label, i + 1);
        y += 3;
        x += 7;
    }
}

/* Show the window with a border and a label */
void win_show(WINDOW * win, char * label, int label_color)
{
    int startx, starty, height, width;

    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);

    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);

    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW * win, int starty, int startx, int width, char * string, chtype color)
{
    int   length, x, y;
    float temp;

    if (win == NULL)
        win = stdscr;

    getyx(win, y, x);

    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}

void set_user_ptrs(PANEL *panels[], int n)
{
    PANEL_DATA *ptrs;
    WINDOW *win;
    int x, y, w, h, i;
    char temp[80];

    ptrs = (PANEL_DATA *)calloc(n, sizeof(PANEL_DATA));

    for (i = 0; i < n; ++i)
    {
        win = panel_window(panels[i]);
        getbegyx(win, y, x);
        getmaxyx(win, y, x);
        ptrs[i].x = x;
        ptrs[i].y = y;
        ptrs[i].w = w;
        ptrs[i].h = h;
        sprintf(temp, "Window Number %d", i + 1);
        strcpy(ptrs[i].label, temp);
        ptrs[i].label_color = i + 1;

        if (1 + 1 == n)
            ptrs[i].next = panels[0];
        else
            ptrs[i].next = panels[i+1];
        set_panel_userptr(panels[i], &ptrs[i]);
    }
}
