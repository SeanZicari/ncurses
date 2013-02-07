#include <form.h>

int main()
{
    FIELD *field[3];
    FORM  *my_form;
    int ch;

    /* Initialize curses */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Initialize the fields */
    field[0] = new_field(1, 10, 4, 18, 0, 0);
    field[1] = new_field(1, 10, 6, 18, 0, 0);
    field[2] = NULL;

    /* Set field options */
    set_field_back(field[0], A_UNDERLINE);
    field_opts_off(field[0], O_AUTOSKIP);

    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_AUTOSKIP);

    my_form = new_form(field);
    post_form(my_form);
    refresh();

    mvprintw(4, 9, "Value 1: ");
    mvprintw(6, 9, "Value 2: ");
    refresh();

    while ((ch = getch()) != KEY_F(1))
    {
        switch(ch)
        {
            case KEY_DOWN:
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP:
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            default:
                form_driver(my_form, ch);
        }
    }

    unpost_form(my_form);
    free_form(my_form);
    free_field(field[0]);
    free_field(field[1]);

    endwin();

    return 0;
}