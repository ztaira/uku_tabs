#ifndef GUITAR
#define GUITAR

#define GUITAR_DISPLAY_ROWS 3
#define GUITAR_NUM_STRINGS 6

using namespace std;

// guitar object
class guitar
{
public:
    // constructor
    guitar(int x, int y, int wheight, int wwidth);
    // where to store the notes
    // strings go E=0, e=5
    vector<char> notestrings[6];
    // where you are in the song
    int note_pos;
    // where the guitar will be located in the terminal and how big it'll be
    int ul_x;
    int ul_y;
    int height;
    int width;
    int win_height;
    int win_width;
    // add notes to the solo
    void add_notes(string notes_file);
    // draw function
    void draw(bool flag);
    void move();
    void draw_string(vector<char> &notestring, int mult, char stringname,
            int offset, bool flag);
    // write ukulele tab
    void to_ukulele();
    vector<int> get_note_values();
    vector< vector<int> > get_ukulele_strings(vector<int> note_values);
    void write_ukulele_strings(vector< vector<int> > ukulele_strings);
    int get_guitar_offset(int stringnum);
    int get_ukulele_offset(int stringnum);
};
#endif
