#include <iostream>
#include "ConsoleControl.h"

int main() {
    ConsoleControl cc;

    cc.setCurPos(10, 10);
    
    int x, y;

    cc.getCurPos(&x, &y);
    std::cout << "x: " << x << " y: " << y << std::endl;

    Sleep(1000);

    cc.clearScr();

    cc.drawFrame(0, 0, 22, 80, "++++-|");
    cc.drawFrame(21, 0, 3, 80, "++++-|");
    cc.refresh();

    cc.putChar('a', 10, 10);
    
    cc.putString("Hello world", 12, 15);
    
    cc.refresh();

    Sleep(1 * 1000);

    cc.setCurPos(11, 10);
    cc.putChar('A');
    cc.setCurPos(13, 15);
    cc.putString("This is working?");

    Sleep(1 * 1000);

    cc.setCurPos(1, 1);
    cc.putChar('J');



    Sleep(60 * 1000);

    return 0;
}