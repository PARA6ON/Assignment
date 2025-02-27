#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Wall.h"
#include <math.h>
#define PI 3.1415926535



//                  y     x
Joystick joystick(PC_3, PC_2);  //attach and create joystick object
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
//ray function
void drawRays();

void boundary(int x, int y);
//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  

float play_pos_x = 60;
float play_pos_y = 34;
float play_pos_angle_x = 0;
float play_pos_angle_y = 0;
float play_angle = 0;

int main(){
    joystick.init();
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    while(1){
        //map function
        lcd.clear();
        lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);
        int *wall1 = Wall(30,30);
        lcd.drawRect(play_pos_x, play_pos_y, 2, 2, FILL_BLACK);
        lcd.drawLine(play_pos_x,play_pos_y, play_pos_x + 2 * play_pos_angle_x, play_pos_y + 2 * play_pos_angle_y, 1);
        //manually draw map can have some function that then randomises the position of the walls
        //using rndom number generators
         if(joystick.get_direction() == N){
            play_pos_y = play_pos_y + play_pos_angle_y;
            play_pos_x = play_pos_x + play_pos_angle_x;

        }else if(joystick.get_direction() == S){
            play_pos_y = play_pos_y - play_pos_angle_y;
            play_pos_x = play_pos_x - play_pos_angle_x;
        
        }else if(joystick.get_direction() == E){
            play_angle = play_angle + 0.2; 
            if (play_angle > 2*PI) {
                play_angle = play_angle - 2*PI;
            }
            play_pos_angle_x = 5 * cos(play_angle);
            play_pos_angle_y = 5 * sin(play_angle);

        }else if(joystick.get_direction() == W){
            play_angle = play_angle - 0.2; 
            if (play_angle < 0) {
                play_angle = play_angle + 2*PI;
            }
            play_pos_angle_x = 5 * cos(play_angle);
            play_pos_angle_y = 5 * sin(play_angle);

        }else if(joystick.get_direction() == NE){
            play_angle = play_angle + 0.2 ; 
            if (play_angle > 2*PI) {
                play_angle =  play_angle - 2*PI;
            }
            play_pos_angle_x = 5 * cos(play_angle);
            play_pos_angle_y = 5 * sin(play_angle);

        }else if(joystick.get_direction() == NW){
            play_angle = play_angle - 0.2; 
            if (play_angle < 0) {
                play_angle = play_angle + 2*PI;
            }
            play_pos_angle_x = 5 * cos(play_angle);
            play_pos_angle_y = 5 * sin(play_angle);

        }else if(joystick.get_direction() == SE){
            play_angle = play_angle + 0.2; 
            if (play_angle > 2*PI) {
                play_angle = play_angle - 2*PI;
            }
            play_pos_angle_x = 5 * cos(play_angle);
            play_pos_angle_y = 5 * sin(play_angle);

        }else if(joystick.get_direction() == SW){
            play_angle = play_angle - 0.2; 
            if (play_angle < 0) {
                play_angle = play_angle + 2*PI;
            }
            play_pos_angle_x = 5 * cos(play_angle);
            play_pos_angle_y = 5 * sin(play_angle);
        } 

        boundary(play_pos_x,play_pos_y);


        lcd.refresh();
        ThisThread::sleep_for(30ms);
    }
}
void drawRays() {
    int r, mx, my, mp, dof;
    float rx,ry,ra,xo,yo;
    ra = play_angle;
    for (r = 0; r<1; r++) {
        dof = 0;
        float aTan = -1/tan(ra);
        //looking down
        if (ra>PI){
            ry = (((int)play_pos_y>>6)<<6)-0.0001;
            rx = (play_pos_y - ry) * aTan + play_pos_x;
            yo = -64;
            xo = -yo*aTan;
        }
        //looking up
        if (ra<PI){
            ry = (((int)play_pos_y>>6)<<6)+64;
            rx = (play_pos_y - ry) * aTan + play_pos_x;
            yo = 64;
            xo = -yo*aTan;
        }
        //looking straight left or right
        if (r == 0) {
            rx = play_pos_x;
            ry = play_pos_y;
            dof = 8;
        }
        while(dof < 8) {

        }
    }
}
void boundary(int x, int y){
    if (x < 1 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        play_pos_x = 1;
    }else if (x > 81){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        play_pos_x  = 81;
    }

    if(y < 1){          //ensure that the point doesnt pass beyond the top of the screen
        play_pos_y  = 1;
    }else if(y > 45){   //ensure that the point doesnt pass beyond the bottom of the screen
        play_pos_y  = 45;
    } 
}

