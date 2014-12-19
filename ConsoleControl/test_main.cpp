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

    cc.drawFrame(0, 0, 25, 80, "++++-|");
    cc.refresh();
    Sleep(60 * 1000);

    return 0;
}