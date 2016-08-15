#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <string>
#include <vector>
using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void open_screen(int y, int x);
vector<string> get_choices();

string choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3"
};

int main()
{
    int ch, win_height, win_width;
    // create a screen
    // get the screen's height and width
    initscr();
    getmaxyx(stdscr, win_height, win_width);
    // we don't want to print input characters
    noecho();
    // we want the cursor to be invisible
    curs_set(0);
    // make all keystrokes immediately available to the program
    cbreak();
    // print the opening screen, which won't go away until a key is pressed
    open_screen(win_height/2, win_width/2);
    refresh();
    getch();
    werase(stdscr);
    refresh();

    // Making the menu!
    MENU *my_menu;
    ITEM **my_items;
    int choicenum;
    choicenum = ARRAY_SIZE(choices);
    // get the menu choices and make them into menu items
    my_items = (ITEM **)calloc(choicenum+1, sizeof(ITEM *));
    for (int i = 0; i < choicenum; i++)
    {
        my_items[i] = new_item(choices[i].c_str(), choices[i].c_str());
    }
    my_items[choicenum+1] = (ITEM *)NULL;
    // create the menu
    my_menu = new_menu((ITEM **)my_items);
    post_menu(my_menu);
    // cout << post_menu(my_menu);
    refresh();
    while((ch = getch()) != 'q')
    {
        switch(ch)
        {
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                refresh();
                break;
            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                refresh();
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

void open_screen(int y, int x)
{
    mvprintw(y, x-17, "You are driving through a field...");
    mvprintw(y+2, x-20, "Suddenly: Donkeys! Dodge them to survive!");
    mvprintw(y+4, x-27, "Use the WASD keys or their dvorak counterparts to steer");
    mvprintw(y*2-1, 1, " ");
}
