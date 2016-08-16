#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
#include "guitar.h"

guitar::guitar(int y, int x, int wheight, int wwidth)
{
    ul_x = x;
    ul_y = y;
    win_height = wheight;
    win_width = wwidth;
    height = 6;
    width = win_width - 40;
}

void guitar::add_notes(string notes_file)
{
    note_pos = 0;
    Estr.clear();
    Astr.clear();
    Dstr.clear();
    Gstr.clear();
    Bstr.clear();
    estr.clear();
    string line;
    ifstream workfile (notes_file);
    while (getline(workfile, line))
    {
        if (line[0] == 'E')
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
        else if (line[0] == 'D')
        {
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Dstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'G')
        {
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Gstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'B')
        {
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    Bstr.push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'e')
        {
            for (int i=1; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    estr.push_back(line[i]);
                }
            }
        }
    }
    workfile.close();
}

void guitar::draw()
{
    // print e string
    mvprintw(ul_y, ul_x, "e|");
    for (int i=note_pos; i<note_pos+win_width-ul_x-2; i++)
    {
        addch(estr[i]);
    }
    // print B string
    mvprintw(ul_y+1, ul_x, "B|");
    for (int i=note_pos; i<note_pos+win_width-ul_x-2; i++)
    {
        addch(Bstr[i]);
    }
    // print G string
    mvprintw(ul_y+2, ul_x, "G|");
    for (int i=note_pos; i<note_pos+win_width-ul_x-2; i++)
    {
        addch(Gstr[i]);
    }
    // print D string
    mvprintw(ul_y+3, ul_x, "D|");
    for (int i=note_pos; i<note_pos+win_width-ul_x-2; i++)
    {
        addch(Dstr[i]);
    }
    // print A string
    mvprintw(ul_y+4, ul_x, "A|");
    for (int i=note_pos; i<note_pos+win_width-ul_x-2; i++)
    {
        addch(Astr[i]);
    }
    // print E string
    mvprintw(ul_y+5, ul_x, "E|");
    for (int i=note_pos; i<note_pos+win_width-ul_x-2; i++)
    {
        addch(Estr[i]);
    }
}

void guitar::move()
{
    note_pos+=1;
    draw();
}
