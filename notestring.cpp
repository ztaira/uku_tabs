#include <ncurses.h>
using namespace std;

notestring::notestring(char basenote)
{
    base_note = basenote;
}

notestring::add_notes(string new_notes)
{
    if (new_notes[0] == base_note)
    {
        for (int i=1; i<new_notes.length(); i++)
        {
            notes.push_back(new_notes[i]);
        }
    }
}
