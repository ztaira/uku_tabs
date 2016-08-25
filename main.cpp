#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ncurses.h>
#include <menu.h>
#include "guitar.h"
#include "ukulele.h"
using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void configure_settings();
void draw_border(WINDOW *win, bool flag);
void configure_main_menu(MENU *my_menu, WINDOW *menu_win, WINDOW *menu_sub);
void moveguitar(char *name, guitar &myguitar);
void moveukulele(char *name, ukulele &myukulele);
void guitarload(char *name, guitar &myguitar);
void ukuleleload(char *name, ukulele &myukulele);

string choices[] = {
    "Scroll Guitar",
    "Scroll Ukulele",
    "Autoscroll",
    "Convert to UTab",
    "gheaven.txt",
    "ghotelintro.txt",
    "ghotelsolo1.txt",
    "ghotelsolo2.txt",
    "ghotelend.txt",
    "udoiwannaknow.txt",
    "uimyours.txt",
    "usanteria.txt"
};

string descriptions[100] = {" "};

int main()
{
    int ch, win_height, win_width;
    bool autoscroll = false;
    // create a screen and configure it
    // get the screen's height and width
    initscr();
    configure_settings();
    getmaxyx(stdscr, win_height, win_width);
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
    main_menu_win = newwin(choicenum+2, 32, 3, 0);
    main_menu_sub = derwin(main_menu_win, choicenum, 30, 1, 1);
    // configure the main menu
    configure_main_menu(my_menu, main_menu_win, main_menu_sub);

    // making the instruments
    guitar myguitar = guitar(4, 35, win_height, win_width);
    myguitar.add_notes("ghotelintro.txt");
    myguitar.draw(true);
    ukulele myukulele = ukulele(29, 35, win_height, win_width);
    myukulele.add_notes("udoiwannaknow.txt");
    myukulele.draw(true);

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
                else if (strcmp(choices[1].c_str(), selection_name) == 0)
                {
                    moveukulele(selection_name, myukulele);
                }
                else if (strcmp(choices[2].c_str(), selection_name) == 0)
                {
                    if (autoscroll == true)
                    {
                        autoscroll = false;
                    }
                    else
                    {
                        autoscroll = true;
                    }
                }
                else if (strcmp(choices[3].c_str(), selection_name) == 0)
                {
                    myguitar.to_ukulele();
                }
                else if (selection_name[0] == 'g')
                {
                    guitarload(selection_name, myguitar);
                }
                else if (selection_name[0] == 'u')
                {
                    ukuleleload(selection_name, myukulele);
                }
                pos_menu_cursor(my_menu);
                break;
            }
            default:
            {
                if (autoscroll == true)
                {
                    myguitar.move();
                    myukulele.move();
                }
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
    timeout(250);
    wbkgd(stdscr, COLOR_PAIR(1));
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
    // print a title
    wattron(stdscr, COLOR_PAIR(8));
    mvprintw(0, 0, "+------------------------------+");
    mvprintw(2, 0, "+------------------------------+");
    mvprintw(1, 0, "|");
    mvprintw(1, 31, "|");
    wattron(stdscr, A_BOLD);
    mvprintw(1, 14, "MENU");
    wattroff(stdscr, A_BOLD);
    wattroff(stdscr, COLOR_PAIR(8));
}

void moveguitar(char *name, guitar &myguitar)
{   
    myguitar.move();
    mvprintw(40, 1, "Item selected is: %s", name);
    wrefresh(stdscr);
}

void moveukulele(char *name, ukulele &myukulele)
{
    myukulele.move();
    mvprintw(40, 1, "Item selected is: %s", name);
    wrefresh(stdscr);
}

void guitarload(char *name, guitar &myguitar)
{
    myguitar.add_notes(name);
    myguitar.draw(false);
    myguitar.draw(true);
    mvprintw(40, 1, "Item selected is: %s", name);
    wrefresh(stdscr);
}

void ukuleleload(char *name, ukulele &myukulele)
{
    myukulele.add_notes(name);
    myukulele.draw(false);
    myukulele.draw(true);
    mvprintw(40, 1, "Item selected is: %s", name);
    wrefresh(stdscr);
}
