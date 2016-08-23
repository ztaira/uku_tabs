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


void guitar::to_ukulele()
{
    vector<int> note_values;
    note_values = get_note_values(notestrings);
    write_ukulele_file(note_values);
}

vector<int> guitar::get_note_values(vector<char> ns_copy[6])
{
    // place to store tab, counting variables
    vector<int> uku_tab;
    int value;
    char chord_space;
    // iterate through each column and row of the 2d array
    // if the first two characters are numbers, add their value to uku_tab
    // else if the first character is a number, add its value to uku_tab
    // else if the first character is a letter, add it to uku_tab
    //      note: letter values are outside of the possible note value range
    //      therefore, you can add the letter values as-is
    // else if the first char is |, add it to uku_tab
    // space the values out with '-' if they happen at the same time
    // values for each note are calculated with conversion.txt
    //
    // summary of included characters:
    // 0-99: added as their value as shown in conversion.txt
    // a-z: added as their value
    // |: added as its value
    // everything else: added as '?'
    for (int i=0; i<ns_copy[0].size();i++)
    {
        for (int j=0; j<6; j++)
        {
            if (ns_copy[j][i] != '-')
            {
                if (chord_space != 0)
                {
                    uku_tab.push_back(chord_space);
                }
                if (ns_copy[j][i] > 47 && ns_copy[j][i] < 58 &&
                        ns_copy[j][i+1] > 47 && ns_copy[j][i+1] < 58)
                {
                    value = (ns_copy[j][i]-48)*10 + ns_copy[j][i]-48 + 
                        get_guitar_offset(j);
                    uku_tab.push_back(value);
                    ns_copy[j][i] = '-';
                    ns_copy[j][i+1] = '-';
                    chord_space = '-';
                }
                else if (ns_copy[j][i] > 47 && ns_copy[j][i] < 58)
                {
                    uku_tab.push_back(ns_copy[j][i]-48 + get_guitar_offset(j));
                    ns_copy[j][i] = '-';
                    chord_space = '-';
                }
                else if (ns_copy[j][i] > 96 && ns_copy[j][i] < 123)
                {
                    uku_tab.push_back(ns_copy[j][i]);
                    ns_copy[j][i] = '-';
                    chord_space = '-';
                }
                else if (ns_copy[j][i] == '|')
                {
                    uku_tab.push_back('|');
                    chord_space = '-';
                }
                else
                {
                    uku_tab.push_back('?');
                    chord_space = '-';
                }
            }
        }
        uku_tab.push_back(-1);
        chord_space = 0;
    }
    return uku_tab;
}

int guitar::get_guitar_offset(int stringnum)
{
    if (stringnum == 0)
    {
        return 0;
    }
    else if (stringnum == 1)
    {
        return 5;
    }
    else if (stringnum == 2)
    {
        return 10;
    }
    else if (stringnum == 3)
    {
        return 15;
    }
    else if (stringnum == 4)
    {
        return 19;
    }
    else if (stringnum == 5)
    {
        return 24;
    }
    return 0;
}

int guitar::get_ukulele_offset(int stringnum)
{
    if (stringnum == 0)
    {
        return 27;
    }
    else if (stringnum == 1)
    {
        return 20;
    }
    else if (stringnum == 2)
    {
        return 24;
    }
    else if (stringnum == 3)
    {
        return 29;
    }
    return 0;
}

void guitar::write_ukulele_file(vector<int> note_values)
{
    char character;
    ofstream workfile;
    workfile.open("test.txt");
    for (int i=0; i<note_values.size(); i++)
    {
        if (note_values[i] == 45 || note_values[i] > 48)
        {
            character = note_values[i];
            workfile << character;
        }
        else if (note_values[i] == -1)
        {
            workfile << "\n";
        }
        else
        {
            workfile << note_values[i];
            workfile << ' ';
        }
    }
    workfile.close();
}
