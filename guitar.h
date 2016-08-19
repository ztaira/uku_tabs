#ifndef GUITAR
#define GUITAR
using namespace std;
// guitar object
class guitar
{
public:
    // constructor
    guitar(int x, int y, int wheight, int wwidth);
    // where to store the notes
    vector<char> Estr;
    vector<char> Astr;
    vector<char> Dstr;
    vector<char> Gstr;
    vector<char> Bstr;
    vector<char> estr;
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
    void draw();
    void move();
    // write ukulele tab
    void to_ukulele();
};
#endif
