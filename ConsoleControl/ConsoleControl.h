#include <Windows.h>
#include <conio.h>

class ConsoleControl
{
private:
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO bufinfo;
    int curRows;
    int curCols;
    int bufRows;
    int bufCols;
    char* scrbuf;
    char* capbuf;
    void clrMemScr();
public:
    ConsoleControl();
    ~ConsoleControl();
    void clearScr();
    void getCurPos(int*, int*);
    void setCurPos(int, int);
    int getChar();
    void putChar(int);
    void putString(const char*);
    char* captureScr();
    void restoreScr();
};