#ifndef NOTESTRING
#define NOTESTRING
using namespace std;
// notestring object
class notestring
{
public:
    // constructor
    notestring(char basenote);
    // the base string note
    char base_note;
    // where to store the notes
    vector<char> notes;
    // add notes to the solo
    void add_notes(string new_notes);
    // draw function
    void draw(bool flag);
    void move();
};
#endif
