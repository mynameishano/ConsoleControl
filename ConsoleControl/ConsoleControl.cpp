#include "ConsoleControl.h"

// private method
void ConsoleControl::clearScrBuf() {
    // loop to fill space into each elements of scrBuf
    for (int i = 0; scrBuf&&i < bufRows*bufCols; scrBuf[i] = ' ', i++);
}

ConsoleControl::ConsoleControl()
    // use initializer to initialize const variables
    :bufRows(MAX_ROWS + 1), bufCols(MAX_COLS + 1) {

    // get standard handle
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // declair SMALL_RECT to re-size console's window and buffer screen
    SMALL_RECT scrSize = { 0, 0, bufCols - 1, bufRows - 1 };
    COORD bufSize = { bufCols, bufRows };
    // set window's size
    SetConsoleWindowInfo(hStdout, TRUE, &scrSize);
    // set buffer screen's size
    SetConsoleScreenBufferSize(hStdout, bufSize);
    
    // allocate memory to scrBuf
    scrBuf = (char*)malloc(bufCols*bufRows);
    
    // clear screen for next step
    clearScr();
}

ConsoleControl::~ConsoleControl() {
    // free memory
    if (scrBuf)
        free(scrBuf);
}

void ConsoleControl::clearScr() {
    DWORD nCharsWritten;
    // fill space from the first cell to the end
    FillConsoleOutputCharacter(hStdout, ' ', bufRows*bufCols, { 0, 0 }, &nCharsWritten);
    // move cursor to {0, 0}
    setCurPos(0, 0);
    // reset scrBuf
    clearScrBuf();
}

void ConsoleControl::getCurPos(int *y, int *x) {
    // get screen buffer info
    GetConsoleScreenBufferInfo(hStdout, &bufInfo);
    // get cursor position
    *x = (int)bufInfo.dwCursorPosition.X;
    *y = (int)bufInfo.dwCursorPosition.Y;
}

void ConsoleControl::setCurPos(int y, int x) {
    // set cursor position
    SetConsoleCursorPosition(hStdout, { x, y });
}

void ConsoleControl::refresh() {
    setCurPos(0, 0);
    for (int i = 0; i < bufRows*bufCols -1; i++) {
        _putch(scrBuf[i]);
    }
}

// this method will draw a frame but only border, and character of border
// will be passed as paramater ( char* border )
// x and y is coord that where frame will be drawn
// width and height is a size of the frame
int ConsoleControl::drawFrame(int x, int y, int height, int width, char* border = "++++-|") {
    int flag = true;;
    
    // validate frame position and size
    if (x + height > bufRows || y + width > bufCols)
        flag = false; // set flag as ERROR
    else { // put frame into scrBuf variable
        for (int row = x; row < height + x; row++) {
            for (int col = y; col < width + y; col++) {
                if (row == x && col == y) // top-left
                    scrBuf[row*bufCols + col] = border[0];
                else if (row == x && col == width + y - 1) // top-right
                    scrBuf[row*bufCols + col] = border[1];
                else if (row == height + x - 1 && col == y) // bottom-left
                    scrBuf[row*bufCols + col] = border[2];
                else if (row == height + x - 1 && col == width + y - 1) // bottom-right
                    scrBuf[row*bufCols + col] = border[3];
                else if ((row == x || row == height + x - 1) && (col != y && col != width + y - 1)) // top and bottom except corner
                    scrBuf[row*bufCols + col] = border[4];
                else if ((row != x && row != height + x - 1) && (col == y || col == width + y - 1)) // left and right except corner
                    scrBuf[row*bufCols + col] = border[5];
                else // inside of frame
                    scrBuf[row*bufCols + col] = ' ';
            }
        }
    }
    return flag;
}

// get char and print it out
void ConsoleControl::putChar(int c) {
    _putch(c);
}

// get char and put it into scrBuf
void ConsoleControl::putChar(int c, int x, int y) {
    scrBuf[x*bufCols + y] = c;
}

// get string and print it out
void ConsoleControl::putString(const char* str) {
    for (int i = 0; str[i]; i++)
        putChar(str[i]);
}

// get string and put into scrBuf
void ConsoleControl::putString(const char* str, int x, int y) {
    if (getStrLen(str) + y <= bufCols) {
        for (int i = 0; str[i]; i++)
            scrBuf[x*bufCols + y + i] = str[i];
    }
}

int ConsoleControl::getChar() {
    int key = _getch();
    return key;
}

char* ConsoleControl::getString(int x, int y, int len) {
    // ...
    return 0;
}

int getStrLen(const char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}