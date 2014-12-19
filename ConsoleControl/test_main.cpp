#include <iostream>
#include "ConsoleControl.h"

int main() {
    ConsoleControl cc;

    cc.setCurPos(0, 0);

    // start screen
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if ((i == 0 && j == 0) || (i == 24 && j == 79))
                cc.putChar('/');
            else if ((i == 24 && j == 0) || (i == 0 && j == 79))
                cc.putChar('\\');
            else if ((i == 0 || i == 24 || i == 21) && (j > 0 && j < 79))
                cc.putChar('-');
            else if ((i>0 && i < 24) && (j == 0 || j == 79))
                cc.putChar('|');
            else
                cc.putChar(' ');
        }
    }

    cc.setCurPos(0, 0);
    cc.setCurPos(2, 22);
    cc.putString("Send-> ");
    cc.setCurPos(2, 23);
    cc.putString("Server: ");

    cc.setCurPos(9, 22);

    Sleep(60000);

    cc.setCurPos(10, 10);
    cc.putString("Hello World");
    Sleep(3000);
    cc.putChar('A');

    Sleep(1000);
    cc.putString("Hello WOW! I love it!!");

    Sleep(3000);

    cc.clearScr();

    cc.setCurPos(10, 10);
    int key;
    while (true)
    {
        key = cc.getChar();
        if (key == 'x')
            break;
        cc.putChar(key);
    }

    return 0;
}