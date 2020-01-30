#include <iostream>
#include <cstddef>
#include <ncurses.h>
using namespace std;

// IMPORTANT:
// must compile using:
//          g++ -lncurses ground_rover.cpp -o ground_rover
// to link ncurses.h

#define ARM_UP 119          // 'w'
#define ARM_DOWN 115        // 's'
#define HAND_UP 114         // 'r'
#define HAND_DOWN 102       // 'f
#define UNLOCK 117          // 'u'
#define FORWARD_UP 0x1      // 0000 0001
#define BACKWARD_DOWN 0x2   // 0000 0010

struct go_car{
   //make bytes for each motor/servo (5 total)
  // potentially one byte for checksum
  // maybe can combine left_side and right_side into one byte
  //      two bits each: 1 move forward, 1 move backwards

  // move motor forward: 0000 0001
  // move motor backwards: 0000 0010
  char left_side;
  char right_side;
  char lift_arm;
  char ice_hand;
  char lock;
  char checksum;
};


void keyboard_io(go_car vroom, int c){
 //accepts input/output from keyboard
  // ex: if hit up arrow, direction should be forward until stop key is hit
   // assuming left/right motors have a forward/backward function: left turn: right_side is forward and left_side is backward
 //if super long make translation from io into data its own function 
        // c=getchar();
        // putchar(c);
    switch(c) {
        case KEY_UP:
            vroom.right_side = FORWARD_UP;
            vroom.left_side = FORWARD_UP;
            printw("Up\n");
            break;
        case KEY_DOWN:
            vroom.right_side = BACKWARD_DOWN;
            vroom.left_side = BACKWARD_DOWN;
            printw("Down\n");
            break;
        case KEY_LEFT:
            vroom.right_side = FORWARD_UP;
            vroom.left_side = BACKWARD_DOWN;
            printw("Left\n");
            break;
        case KEY_RIGHT:
            vroom.left_side = FORWARD_UP;
            vroom.right_side = BACKWARD_DOWN;
            printw("Right\n");
            break;
        case ARM_UP:
            vroom.lift_arm = FORWARD_UP;
            printw("Arm Up\n");
            break;
        case ARM_DOWN:
            vroom.lift_arm = BACKWARD_DOWN;
            printw("Arm Down\n");
            break;
        case HAND_UP:
            vroom.ice_hand = FORWARD_UP;
            printw("Hand Up\n");
            break;
        case HAND_DOWN:
            vroom.ice_hand = BACKWARD_DOWN;
            printw("Hand Down\n");
            break;
        case UNLOCK:
            vroom.lock = 0x1;
            printw("Unlock\n");
            break;
        default:
            vroom.left_side = 0x0;
            vroom.right_side = 0x0;
            vroom.lift_arm = 0x0;
            vroom.ice_hand = 0x0;
            // printw("Stop\n"); // prints every time button not being pressed, so commented out
            break;
    }

  //nathan
}



void send_data_radio(){
 //send the data to the serial radio
  //optionally create a checksum
  //kendall
}


void create_checksum(){
   //if this takes a few lines put here
   
   //kendall

}

void check_checksum(){
 //checks checksum from the ack message from rover 
  
  //kendall
}

int main() {
    // MUST INCLUDE these lines to set up curses.h
    initscr(); // initializes ncurses
    cbreak(); // disables buffering, takes char-at-a-time input
    noecho(); // suppress auto echoing of typed chars
    keypad(stdscr, TRUE); // allows us to capture special key strokes (arrow keys)
    nodelay(stdscr, TRUE); // does not pause program to wait for typed char
    scrollok(stdscr, TRUE); // window will scroll when full

    go_car car;
    int c;
    // LOOP:
    do {
        c = getch();
        keyboard_io(car, c);

        // ... rest of loop ...
    } while (c != '9'); // Pressing '9' ends the loop

    // MUST INCLUDE this to return control to terminal
    endwin(); // restores terminal settings

    return 0;
}


