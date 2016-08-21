#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <algorithm>
#include "guitar.h"

guitar::guitar(int y, int x, int wheight, int wwidth)
{
    ul_x = x;
    ul_y = y;
    win_height = wheight;
    win_width = wwidth;
    height = 7;
    width = 120;
}

void guitar::add_notes(string notes_file)
{
    note_pos = 0;
    for (int i=0; i<6; i++)
    {
        notestrings[i].clear();
    }
    string line;
    ifstream workfile (notes_file);
    while (getline(workfile, line))
    {
        if (line[0] == 'E')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    notestrings[0].push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'A')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    notestrings[1].push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'D')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    notestrings[2].push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'G')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    notestrings[3].push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'B')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    notestrings[4].push_back(line[i]);
                }
            }
        }
        else if (line[0] == 'e')
        {
            for (int i=2; i<line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    notestrings[5].push_back(line[i]);
                }
            }
        }
    }
    workfile.close();
}

void guitar::draw(bool flag)
{
    for (int mult=0; mult<3; mult++)
    {
        // print e string
        draw_string(notestrings[5], mult, 'e', 0, flag);
        // print B string
        draw_string(notestrings[4], mult, 'B', 1, flag);
        // print G string
        draw_string(notestrings[3], mult, 'G', 2, flag);
        // print D string
        draw_string(notestrings[2], mult, 'D', 3, flag);
        // print A string
        draw_string(notestrings[1], mult, 'A', 4, flag);
        // print E string
        draw_string(notestrings[0], mult, 'E', 5, flag);
    }
}

void guitar::move()
{
    draw(false);
    note_pos+=1;
    draw(true);
}

void guitar::to_ukulele()
{
    vector<char> uku_tab;
    char notes[6];
    int notecount;
    for (int i=0; i<notestrings[0].size();i++)
    {
        for (int i=0; i<6; i++)
        {
            notes[i] = notestrings[i][0];
        }
    }
}

void guitar::draw_string(vector<char> &notestring, int mult, char stringname,
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
