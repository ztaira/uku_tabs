# uku\_tabs
Hack-A-Week 5: A program to conveniently display guitar and ukulele tabs
Hack-A-Week 6: A function to convert guitar tabs to ukulele

The solution to, "Why are ukulele tabs so hard to find?"

### Usage:
- Executable is named "uku\_tabs" by default (see makefile)
- To run it, execute it as follows from the uku\_tabs directory:

`./uku_tabs`

- Ukulele tabs are prefixed with a 'u', and guitar tabs are prefixed with a 'g'
- To add a tab to the UI, add the filename to the list 'choices' and recompile
using the makefile 
- Menu options can be selected using the keys 'j', 'k', and 'Enter'

### Features:
- Store and load both guitar and ukulele tabs from text files
- Both manual and autoscroll options
- Works well with all possible characters in tab notation
- Option to convert from a guitar tab to an ukulele tab

### What it does:
- Reads in notes/characters from guitar/ukulele tabs in a text file
- Displays instantaneously in the terminal
- Outputs ukulele tab file when the "Convert to Utab" option is selected
- Default ukulele tab file name is "ukulele\_output.txt"

### What it doesn't do:
- Automatically load the created ukulele tab into the UI
- Adjust UI based on the terminal window size (Tested on a window with
height=48, rows=170)
- Decide which string you should play notes on in the created ukulele tab

### Included files:
README.md....................This readme file
conversion.txt...............A reference for converting notes to a numerical value
guitar.cpp...................Guitar class file
guitar.h.....................Guitar header file
main.cpp.....................Main file
makefile.....................Makefile
ukulele.cpp..................Ukulele class file
ukulele.h....................Ukulele header file
uku\_tabs....................Default executable
g(something).txt.............Guitar tab files
u(something).txt.............Ukulele tab files

### Example Output:

![alt text][outputimage]
[outputimage]: https://github.com/ztaira14/uku_tabs/blob/master/diagrams/UI.png "UI Example"
