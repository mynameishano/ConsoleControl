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

void ConsoleControl::getCurPos(int *x, int *y) {
    // get screen buffer info
    GetConsoleScreenBufferInfo(hStdout, &bufInfo);
    // get cursor position
    *x = (int)bufInfo.dwCursorPosition.X;
    *y = (int)bufInfo.dwCursorPosition.Y;
}

void ConsoleControl::setCurPos(int x, int y) {
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

void ConsoleControl::putChar(const int c) {
    _putch(c);
}

void ConsoleControl::putString(const char* str) {
    for (int i = 0; str[i]; i++)
        _putch(str[i]);
}

int ConsoleControl::getChar() {
    int key = _getch();
    return key;
}

char* ConsoleControl::getString(int x, int y, int len) {
    // ...
    return 0;
}

//void ConsoleControl::clrMemScr() {
//    for (int i = 0; scrbuf&&i < bufRows*bufCols; scrbuf[i] = ' ', i++);
//}
//
//ConsoleControl::ConsoleControl() {
//    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//    GetConsoleScreenBufferInfo(hStdout, &bufinfo);
//    SMALL_RECT scrSize = bufinfo.srWindow;
//    if (scrSize.Bottom != 25 || scrSize.Right != 79) {
//        scrSize.Left = scrSize.Top = 0;
//        scrSize.Bottom = 25;
//        scrSize.Right = 79;
//        SetConsoleWindowInfo(hStdout, true, &scrSize);
//    }
//    bufRows = (int)scrSize.Bottom + 1;
//    bufCols = (int)scrSize.Right + 1;
//    COORD bufSize = { bufCols, bufRows };
//    SetConsoleScreenBufferSize(hStdout, bufSize);
//    scrbuf = (char*)malloc(bufRows*bufCols);
//    clearScr();
//}
//
//ConsoleControl::~ConsoleControl() {
//    free(scrbuf);
//}
//
//void ConsoleControl::clearScr() {
//    DWORD length = bufRows*bufCols;
//    DWORD nCharsWritten;
//    COORD coordScr = { 0, 0 };
//    FillConsoleOutputCharacter(hStdout, ' ', length, coordScr, &nCharsWritten);
//    setCurPos(0, 0);
//    clrMemScr();
//}
//
//void ConsoleControl::getCurPos(int* x, int* y) {
//    *x = bufinfo.dwCursorPosition.X;
//    *y = bufinfo.dwCursorPosition.Y;
//}
//
//void ConsoleControl::setCurPos(int x, int y) {
//    COORD coord;
//    coord.X = curRows = x;
//    coord.Y = curCols = y;
//    SetConsoleCursorPosition(hStdout, coord);
//}
//
//int ConsoleControl::getChar() {
//    int key = _getch();
//    return key;
//}
//
//void ConsoleControl::putChar(int c) {
//    _putch(c);
//}
//
//void ConsoleControl::putString(const char* str) {
//    for (int i = 0; str[i]; i++)
//        _putch(str[i]);
//}
//
//char* ConsoleControl::captureScr() {
//    capbuf = (char*)malloc(bufRows*bufCols);
//    if (capbuf) {
//        for (int i = 0; i < bufRows; i++) {
//            for (int j = 0; j < bufCols; j++) {
//                capbuf[i + j] = scrbuf[i + j];
//            }
//        }
//    }
//    return capbuf;
//}
//
//void ConsoleControl::restoreScr() {
//    for (int i = 0; i < bufRows; i++) {
//        for (int j = 0; j < bufCols; j++) {
//            scrbuf[i + j] = capbuf[i + j];
//            setCurPos(i, j);
//            putChar(scrbuf[i + j]);
//        }
//    }
//    free(capbuf);
//}