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
    height = 4;
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
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Gstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'C')
        {
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Cstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'E')
        {
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Estr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'A')
        {
            for (int i=1; i<line.length(); i++)
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

void ukulele::draw()
{
    // print A string
    mvprintw(ul_y, ul_x, "A|");
    for (int i=note_pos; i<note_pos+width; i++)
    {
        if (i<Astr.size())
        {
            addch(Astr[i]);
        }
    }
    addch('|');
    // print E string
    mvprintw(ul_y+1, ul_x, "E|");
    for (int i=note_pos; i<note_pos+width; i++)
    {
        if (i<Astr.size())
        {
            addch(Estr[i]);
        }
    }
    addch('|');
    // print C string
    mvprintw(ul_y+3, ul_x, "C|");
    for (int i=note_pos; i<note_pos+width; i++)
    {
        if (i<Astr.size())
        {
            addch(Cstr[i]);
        }
    }
    addch('|');
    // print G string
    mvprintw(ul_y+2, ul_x, "G|");
    for (int i=note_pos; i<note_pos+width; i++)
    {
        if (i<Astr.size())
        {
            addch(Gstr[i]);
        }
    }
    addch('|');
}

void ukulele::move()
{
    note_pos+=1;
    draw();
}