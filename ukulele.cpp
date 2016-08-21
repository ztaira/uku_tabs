#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
#include "ukulele.h"

ukulele::ukulele(int y, int x, int wheight, int wwidth)
{
    ul_x = x;
    ul_y = y;
    win_height = wheight;
    win_width = wwidth;
    height = 6;
    width = 120;
}

void ukulele::add_notes(string notes_file)
{
    note_pos = 0;
    Gstr.clear();
    Cstr.clear();
    Estr.clear();
    Astr.clear();
    string line;
    ifstream workfile (notes_file);
    while (getline(workfile, line))
    {
        if (line[0] == 'G')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Gstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'C')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Cstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'E')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Estr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'A')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Astr.push_back(line[i]);
                }
            }
        }
    }
    workfile.close();
}

void ukulele::draw(bool flag)
{
    for (int mult=0; mult<3; mult++)
    {
        // print A string
        draw_string(Astr, mult, 'A', 0, flag);
        // print E string
        draw_string(Estr, mult, 'E', 1, flag);
        // print C string
        draw_string(Cstr, mult, 'C', 2, flag);
        // print G string
        draw_string(Gstr, mult, 'G', 3, flag);
    }
}

void ukulele::move()
{
    draw(false);
    note_pos+=1;
    draw(true);
}

void ukulele::draw_string(vector<char> &notestring, int mult, char stringname,
        int offset, bool flag)
{
    mvaddch(ul_y+mult*height+offset, ul_x, stringname);
    addch('|');
    for (int i=note_pos+mult*width; i<note_pos+mult*width+width; i++)
    {
        if (i<notestring.size() && flag == true)
        {
            addch(notestring[i]);
        }
        else
        {
            addch(' ');
        }
    }
    addch('|');
    addch(' ');
}
