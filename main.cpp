#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <string>
#include <vector>
#include "notestring.h"
using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void configure_settings();
void open_screen();
void draw_border(WINDOW *win, bool flag);
void configure_main_menu(MENU *my_menu, WINDOW *menu_win, WINDOW *menu_sub);

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

int main()
{
    int ch;
    // create a screen
    // get the screen's height and width
    initscr();
    configure_settings();
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
        my_items[i] = new_item(choices[i].c_str(), choices[i].c_str());
    }
    my_items[choicenum+1] = (ITEM *)NULL;
    // create the main menu, as well as its main and sub windows
    my_menu = new_menu((ITEM **)my_items);
    main_menu_win = newwin(22, 32, 0, 0);
    main_menu_sub = derwin(main_menu_win, 20, 30, 1, 1);
    // configure the main menu
    configure_main_menu(my_menu, main_menu_win, main_menu_sub);
    wrefresh(main_menu_win);
    while((ch = getch()) != 'q')
    {
        switch(ch)
        {
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                draw_border(main_menu_win, true);
                touchwin(main_menu_win);
                wrefresh(main_menu_win);
                break;
            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                draw_border(main_menu_win, false);
                touchwin(main_menu_win);
                wrefresh(main_menu_win);
                break;
        }
    }   

    free_item(my_items[0]);
    free_item(my_items[1]);
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
