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
    // load notes from a tab into the guitar object
    // the characters from the tab are stored in vector<char> notestrings
    //
    // notestrings[0] is the low E string
    // notestrings[5] is the high e string
    //
    // don't include trailing whitespaces
    note_pos = 0;
    for (int i = 0; i < GUITAR_NUM_STRINGS; i++)
    {
        notestrings[i].clear();
    }
    string line;
    ifstream workfile (notes_file);
    int length;
    while (getline(workfile, line))
    {
        length = line.length();
        switch (line[0])
        {
            case 'E':
                for (int i = 2; i < length; i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[0].push_back(line[i]);
                    }
                }
                break;
            case 'A':
                for (int i = 2; i < length; i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[1].push_back(line[i]);
                    }
                }
                break;
            case 'D':
                for (int i = 2; i < length; i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[2].push_back(line[i]);
                    }
                }
                break;
            case 'G':
                for (int i = 2; i < length; i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[3].push_back(line[i]);
                    }
                }
                break;
            case 'B':
                for (int i = 2; i < length; i++)
                {
                    if (line[i] != ' ')
                    {
                        notestrings[4].push_back(line[i]);
                    }
                }
                break;
            case 'e':
                for (int i = 2; i < length; i++)
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
    // draw the guitar, with GUITAR_DISPLAY_ROWS rows in the tab
    for (int mult = 0; mult < GUITAR_DISPLAY_ROWS; mult++)
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
    // scroll through the tab
    draw(false);
    note_pos += 1;
    draw(true);
}

void guitar::draw_string(vector<char> &notestring, int mult, char stringname,
        int offset, bool flag)
{
    // function to draw a single string of the guitar
    int start_note = note_pos + mult * width;
    int end_note = note_pos + mult * width + width;
    mvaddch(ul_y + mult * height + offset, ul_x, stringname);
    addch('|');
    for (int i = start_note; i < end_note; i++)
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
    // convert the guitar tab into an equivalent ukulele tab
    // print said tab to file
    vector<int> note_values;
    vector< vector<int> > ukulele_strings;

    // get the note values in the guitar tab
    note_values = get_note_values();
    // create a mock ukulele with said note values
    ukulele_strings = get_ukulele_strings(note_values);
    // write said ukulele to file
    write_ukulele_strings(ukulele_strings);
}

vector<int> guitar::get_note_values()
{
    // iterate through each column and row of the 2d notestring array
    // return the values it finds
    //
    // summary of included characters:
    // 0-99: added as their note value as shown in conversion.txt
    // everything else: added as its char value
    // 
    // i is the column of the tab, j is the string
    // iterates through each time step
    // then, for each time step, iterates through each string and grabs
    // the first note it finds
    //
    // Ex: It would grab the notes 1-2-4-5 in the following tab:
    // e|-1--------------------------------
    // A|----------------------------------
    // D|----2--3--5-----------------------
    // G|----------------------------------
    // B|-------4--------------------------
    // E|----------------------------------
    vector<int> uku_tab;
    vector<char> ns_copy[4];
    for (int i = 0; i < 4; i++)
    {
        ns_copy[i] = notestrings[i];
    }
    int value;
    bool chord;
    for (int i = 0; i < ns_copy[0].size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (ns_copy[j][i] != '-')
            {
                if (chord == true)
                {
                }
                // if there are two digits, calculate their note value
                // 48-57 are the digits 0-9 in ascii and unicode
                else if (ns_copy[j][i] > 47 && ns_copy[j][i] < 58 &&
                        ns_copy[j][i+1] > 47 && ns_copy[j][i+1] < 58)
                {
                    value = (ns_copy[j][i]-48)*10 + ns_copy[j][i]-48 +
                        get_guitar_offset(j);
                    uku_tab.push_back(value);
                    ns_copy[j][i] = '-';
                    ns_copy[j][i+1] = '-';
                    chord = true;
                }
                // if there is only one digit, calculate its note value
                else if (ns_copy[j][i] > 47 && ns_copy[j][i] < 58)
                {
                    uku_tab.push_back(ns_copy[j][i]-48 + get_guitar_offset(j));
                    ns_copy[j][i] = '-';
                    chord = true;
                }
                // otherwise add its char value
                else
                {
                    uku_tab.push_back(ns_copy[j][i]);
                    chord = true;
                }
            }
        }
        chord = false;
    }
    return uku_tab;
}

int guitar::get_guitar_offset(int stringnum)
{
    // function to return the offset of a given guitar string
    // for reasoning behind this, see conversion.txt
    switch (stringnum)
    {
        case 0:
            return 0;
            break;
        case 1:
            return 5;
            break;
        case 2:
            return 10;
            break;
        case 3:
            return 15;
            break;
        case 4:
            return 19;
            break;
        case 5:
            return 24;
            break;
    }
    return 0;
}

int guitar::get_ukulele_offset(int stringnum)
{
    // function to return the offset of a given ukulele string
    // for reasoning behind this, see conversion.txt
    switch (stringnum)
    {
        case 0:
            return 27;
            break;
        case 1:
            return 20;
            break;
        case 2:
            return 24;
            break;
        case 3:
            return 29;
            break;
    }
    return 0;
}

vector< vector<int> > guitar::get_ukulele_strings(vector<int> note_values)
{
    // convert the given note values into a mock ukulele and return it
    char character;
    int value;
    vector< vector<int> > ukulele_strings(4, vector<int>(0));
    for (int j = 0; j < note_values.size(); j++)
    {
        for (int i = 0; i < 4; i++)
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
    // write the values in ukulele_strings to a file
    char character;
    int final_value;
    int position = 0;
    ofstream workfile;
    workfile.open("ukulele_output.txt");
    while (position < ukulele_strings[0].size())
    {
        for (int j = 0; j < 4; j++)
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
            for (int i = position; i < position + 20 && i < ukulele_strings[j].size(); i++)
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
        position += 20;
        workfile << "\n";
    }
    workfile.close();
}
