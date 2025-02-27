#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Wall.h"


int* Wall(int x, int y) {
    lcd.drawRect(x, y, 2, 2, FILL_BLACK);
    static int wall[4];
    wall[0] = x;
    wall[1] = y;
    wall[2] = x + 1;
    wall[3] = y + 1;
    return wall;
}