#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ncurses.h>
#include <menu.h>
#include "guitar.h"
using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void configure_settings();
void open_screen();
void draw_border(WINDOW *win, bool flag);
void configure_main_menu(MENU *my_menu, WINDOW *menu_win, WINDOW *menu_sub);
void moveguitar(char *name, guitar &myguitar);

string choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Choice 5",
    "Choice 6",
    "Choice 7",
    "Choice 8",
    "Choice 9",
    "Choice 10",
    "Choice 11",
    "Choice 12",
    "Choice 13",
    "Choice 14",
    "Choice 15",
};

string descriptions[] = {
    "Description 1",
    "Description 2",
    "Description 3",
    "Description 4",
    "Description 5",
    "Description 6",
    "Description 7",
    "Description 8",
    "Description 9",
    "Description 10",
    "Description 11",
    "Description 12",
    "Description 13",
    "Description 14",
    "Description 15",
};

int main()
{
    int ch, win_height, win_width;
    // create a screen and configure it
    // get the screen's height and width
    initscr();
    configure_settings();
    getmaxyx(stdscr, win_height, win_width);
    // print the opening screen, which won't go away until a key is pressed
    open_screen();
    refresh();
    getch();
    werase(stdscr);
    refresh();

    // Making the menu!
    MENU *my_menu;
    ITEM **my_items;
    WINDOW *main_menu_win;
    WINDOW *main_menu_sub;
    int choicenum;
    choicenum = ARRAY_SIZE(choices);
    // get the menu choices and make them into menu items
    my_items = (ITEM **)calloc(choicenum+1, sizeof(ITEM *));
    for (int i = 0; i < choicenum; i++)
    {
        my_items[i] = new_item(choices[i].c_str(), descriptions[i].c_str());
    }
    my_items[choicenum+1] = (ITEM *)NULL;
    // create the main menu, as well as its main and sub windows
    my_menu = new_menu((ITEM **)my_items);
    main_menu_win = newwin(win_height, 32, 0, 0);
    main_menu_sub = derwin(main_menu_win, win_height-2, 30, 1, 1);
    // configure the main menu
    configure_main_menu(my_menu, main_menu_win, main_menu_sub);

    // making the instruments
    guitar myguitar = guitar(5, 40, win_height, win_width);
    myguitar.add_notes("hotelintro.txt");
    myguitar.draw();

    wrefresh(main_menu_win);
    while((ch = getch()) != 'q')
    {
        switch(ch)
        {
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                touchwin(main_menu_win);
                wrefresh(main_menu_win);
                break;
            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                touchwin(main_menu_win);
                wrefresh(main_menu_win);
                break;
            // enter key is pressed. The user has selected something.
            case 10:
            {
                ITEM *cur;
                char *selection_name;
                // find the name of the selected item
                cur = current_item(my_menu);
                selection_name = (char *)item_name(cur);
                if (strcmp(choices[0].c_str(), selection_name) == 0)
                {
                    moveguitar(selection_name, myguitar);
                }
                pos_menu_cursor(my_menu);
                break;
            }
        }
    }   

    for (int i = 0; i < choicenum; i++)
    {
        free_item(my_items[i]);
    }
    free_menu(my_menu); 

    // end curses mode
    endwin();

    return 0;
}

void configure_settings()
{
    // we don't want to print input characters
    noecho();
    // we want the cursor to be invisible
    curs_set(0);
    // make all keystrokes immediately available to the program
    cbreak();
    // we want to turn colors on
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
}

void open_screen()
{
    int y, x;
    getmaxyx(stdscr, y, x);
    y = y/2;
    x = x/2;
    string str;
    str = "Ukulele Tab Converter";
    mvprintw(y-2, x-str.length()/2, str.c_str());
    str = "by Zachary Taira";
    mvprintw(y+0, x-str.length()/2, str.c_str());
    str = "Hack-A-Week 6";
    mvprintw(y+2, x-str.length()/2, str.c_str());
    mvprintw(y*2-1, 1, " ");
}

void draw_border(WINDOW *win, bool flag)
{
    if (flag == true)
    {
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    }
    else
    {
        wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    }
    wrefresh(win);
}

void configure_main_menu(MENU *my_menu, WINDOW *main_menu_win,
        WINDOW *main_menu_sub)
{
    // set the border color and draw a border
    wattron(main_menu_win, COLOR_PAIR(8));
    draw_border(main_menu_win, true);
    // set the color of selected and unselected items
    set_menu_fore(my_menu, COLOR_PAIR(8) | A_REVERSE);
    set_menu_back(my_menu, COLOR_PAIR(8));
    // enable keypad
    keypad(main_menu_win, true);
    // set the main and sub windows
    set_menu_win(my_menu, main_menu_win);
    set_menu_sub(my_menu, main_menu_sub);
    // post the menu
    post_menu(my_menu);
}

void moveguitar(char *name, guitar &myguitar)
{   
    myguitar.move();
    mvprintw(40, 40, "Item selected is : %s", name);
    wrefresh(stdscr);
}
