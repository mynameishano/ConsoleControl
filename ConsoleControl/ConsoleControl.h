#include <Windows.h>
#include <conio.h>

#define MAX_ROWS 29
#define MAX_COLS 79

class ConsoleControl {
private:
    HANDLE hStdout; // holds standard output handle
    CONSOLE_SCREEN_BUFFER_INFO bufInfo; // holds console information

    const int bufRows; // holds number of rows and cols of console window and
    const int bufCols; // buffer screen 

    char* scrBuf; // holds characters of current screen
    char* bakBuf; // for backup of scrBuf

    // to reset scrBuf
    void clearScrBuf();
public:
    // constructor and destructor
    ConsoleControl();
    ~ConsoleControl();

    // basic methods
    void clearScr(); // clear current screen
    // get and set cursor position
    void getCurPos(int*, int*);
    void setCurPos(int, int);
   
    // Console GUI methods
    // refresh screen with scrBuf
    void refresh();
    // drawing frames (only border)
    int drawFrame(int, int, int, int, char*);
    // I-O methods
    void putChar(const int);
    void putString(const char*);
    int getChar();
    char* getString(int, int, int);
};

//#include <windows.h>
//#include <conio.h>
//
//class consolecontrol
//{
//private:
//    handle hstdout;
//    console_screen_buffer_info bufinfo;
//    int currows;
//    int curcols;
//    int bufrows;
//    int bufcols;
//    char* scrbuf;
//    char* capbuf;
//    void clrmemscr();
//public:
//    consolecontrol();
//    ~consolecontrol();
//    void clearscr();
//    void getcurpos(int*, int*);
//    void setcurpos(int, int);
//    int getchar();
//    void putchar(int);
//    void putstring(const char*);
//    char* capturescr();
//    void restorescr();
//};