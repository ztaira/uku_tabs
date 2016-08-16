#ifndef GUITAR
#define GUITAR
using namespace std;
// guitar object
class guitar
{
public:
    // constructor
    guitar();
    // where to store the notes
    vector<char> Estr;
    vector<char> Astr;
    vector<char> Dstr;
    vector<char> Gstr;
    vector<char> Bstr;
    vector<char> estr;
    // add notes to the solo
    void add_notes(string new_notes);
    // draw function
    void draw(bool flag);
    void move();
};
#endif
