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
        switch (line[0])
        {
            case 'E':
                for (int i=2; i<line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[0].push_back(line[i]);
                    }
                }
                break;
            case 'A':
                for (int i=2; i<line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[1].push_back(line[i]);
                    }
                }
                break;
            case 'D':
                for (int i=2; i<line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[2].push_back(line[i]);
                    }
                }
                break;
            case 'G':
                for (int i=2; i<line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[3].push_back(line[i]);
                    }
                }
                break;
            case 'B':
                for (int i=2; i<line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[4].push_back(line[i]);
                    }
                }
                break;
            case 'e':
                for (int i=2; i<line.length(); i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[5].push_back(line[i]);
                    }
                }
                break;
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
    vector< vector<int> > ukulele_strings;
    note_values = get_note_values();
    ukulele_strings = get_ukulele_strings(note_values);
    write_ukulele_strings(ukulele_strings);
}

vector<int> guitar::get_note_values()
{
    // place to store tab, counting variables
    vector<int> uku_tab;
    vector<char> ns_copy[6];
    for (int i=0; i<6; i++)
    {
        ns_copy[i] = notestrings[i];
    }
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
                    // uku_tab.push_back(chord_space);
                }
                else if (ns_copy[j][i] > 47 && ns_copy[j][i] < 58 &&
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
            }
        }
        chord_space = 0;
    }
    ofstream workfile;
    workfile.open("notevalues.txt");
    for (int i=0; i<uku_tab.size(); i++)
    {
        workfile << uku_tab[i] << "\n";
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

vector< vector<int> > guitar::get_ukulele_strings(vector<int> note_values)
{
    char character;
    int value;
    vector< vector<int> > ukulele_strings(4, vector<int>(0));
    for (int j=0; j<note_values.size(); j++)
    {
        for (int i=0; i<4; i++)
        {
            while (note_values[j] < 20 && note_values[i] > 0)
            {
                note_values[j] += 12;
            }
            ukulele_strings[i].push_back(note_values[j]);
        }
    }
    return ukulele_strings;
}

void guitar::write_ukulele_strings(vector< vector<int> > ukulele_strings)
{
    char character;
    int final_value;
    ofstream workfile;
    workfile.open("test.txt");
    for (int j=0; j<4; j++)
    {
        switch (j) {
            case 0: workfile << "A|--";
                    break;
            case 1: workfile << "E|--";
                    break;
            case 2: workfile << "C|--";
                    break;
            case 3: workfile << "G|--";
                    break;
        }
        for (int i=0; i<ukulele_strings[0].size(); i++)
        {
            final_value = ukulele_strings[j][i]-get_ukulele_offset(3-j);
            if (final_value < 0)
            {
                workfile << "---";
            }
            else if (final_value < 10)
            {
                workfile << final_value;
                workfile << "--";
            }
            else if (final_value < 48 - get_ukulele_offset(3-j))
            {
                workfile << final_value;
                workfile << '-';
            }
            else
            {
                character = ukulele_strings[j][i];
                workfile << character <<  '-' << '-';
            }
        }
        workfile << "|\n";
    }
    workfile.close();
}
