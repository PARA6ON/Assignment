#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Wall.h"

N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

int* Wall(int x, int y) {
    lcd.drawRect(x, y, 2, 2, FILL_BLACK);
    static int wall[4];
    wall[0] = x;
    wall[1] = y;
    wall[2] = x + 1;
    wall[3] = y + 1;
    return wall;
}