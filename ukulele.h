#ifndef UKULELE
#define UKULELE
using namespace std;
// ukulele object
class ukulele
{
public:
    // constructor
    ukulele(int x, int y, int wheight, int wwidth);
    // where to store the notes
    vector<char> Gstr;
    vector<char> Cstr;
    vector<char> Estr;
    vector<char> Astr;
    // where you are in the song
    int note_pos;
    // where the ukulele will be located in the terminal and how big it'll be
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
};
#endif
