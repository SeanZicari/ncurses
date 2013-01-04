#include <panel.h>

void main()
{
    WINDOW * my_wins[3];
    PANEL  * my_panels[3];
    int      lines = 10,
             cols = 40,
             y = 2,
             x = 4,
             i;
    
    initscr();
    cbreak();
    noecho();

    for (i = 0; i < 3; ++i)
    {
        /* Create windows for the panels */
        my_wins[i] = newwin(lines, cols, y + i, x + (i * 5));

        /*
         * Create borders around the windows so that you can see the effect
         * of panels
         */
        box(my_wins[i], 0, 0);

        /* Attach a panel to each window */
        my_panels[i] = new_panel(my_wins[i]);
    }

    update_panels();

    /* Show it on screen */
    doupdate();

    getch();
    endwin();
}
