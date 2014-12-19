#include "ConsoleControl.h"

void ConsoleControl::clrMemScr() {
    for (int i = 0; scrbuf&&i < bufRows*bufCols; scrbuf[i] = ' ', i++);
}

ConsoleControl::ConsoleControl() {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &bufinfo);
    SMALL_RECT scrSize = bufinfo.srWindow;
    if (scrSize.Bottom != 25 || scrSize.Right != 79) {
        scrSize.Left = scrSize.Top = 0;
        scrSize.Bottom = 25;
        scrSize.Right = 79;
        SetConsoleWindowInfo(hStdout, true, &scrSize);
    }
    bufRows = (int)scrSize.Bottom + 1;
    bufCols = (int)scrSize.Right + 1;
    COORD bufSize = { bufCols, bufRows };
    SetConsoleScreenBufferSize(hStdout, bufSize);
    scrbuf = (char*)malloc(bufRows*bufCols);
    clearScr();
}

ConsoleControl::~ConsoleControl() {
    free(scrbuf);
}

void ConsoleControl::clearScr() {
    DWORD length = bufRows*bufCols;
    DWORD nCharsWritten;
    COORD coordScr = { 0, 0 };
    FillConsoleOutputCharacter(hStdout, ' ', length, coordScr, &nCharsWritten);
    setCurPos(0, 0);
    clrMemScr();
}

void ConsoleControl::getCurPos(int* x, int* y) {
    *x = bufinfo.dwCursorPosition.X;
    *y = bufinfo.dwCursorPosition.Y;
}

void ConsoleControl::setCurPos(int x, int y) {
    COORD coord;
    coord.X = curRows = x;
    coord.Y = curCols = y;
    SetConsoleCursorPosition(hStdout, coord);
}

int ConsoleControl::getChar() {
    int key = _getch();
    return key;
}

void ConsoleControl::putChar(int c) {
    _putch(c);
}

void ConsoleControl::putString(const char* str) {
    for (int i = 0; str[i]; i++)
        _putch(str[i]);
}

char* ConsoleControl::captureScr() {
    capbuf = (char*)malloc(bufRows*bufCols);
    if (capbuf) {
        for (int i = 0; i < bufRows; i++) {
            for (int j = 0; j < bufCols; j++) {
                capbuf[i + j] = scrbuf[i + j];
            }
        }
    }
    return capbuf;
}

void ConsoleControl::restoreScr() {
    for (int i = 0; i < bufRows; i++) {
        for (int j = 0; j < bufCols; j++) {
            scrbuf[i + j] = capbuf[i + j];
            setCurPos(i, j);
            putChar(scrbuf[i + j]);
        }
    }
    free(capbuf);
}