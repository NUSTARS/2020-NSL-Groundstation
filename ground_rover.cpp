// include files
#include "SerialPort.h"
#include <iostream>
#include <string>
#include <cstddef>
#include <ncurses.h>
#include <Python.h>
//#include "SerialPort.cpp"
using namespace std;

// IMPORTANT:
// must compile using:
//          g++ -lncurses ground_rover.cpp -o ground_rover
// to link ncurses.h

// macros
#define DATA_LENGTH 255
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


void create_checksum(go_car car){
   char checksum;
   checksum = car.left_side ^ car.right_side;
   checksum ^= car.lift_arm;
   checksum ^= car.ice_hand;
   checksum ^= car.lock;

   car.checksum = checksum;
}

int check_checksum(go_car car, char ret_checksum){
 //checks checksum from the ack message from rover 
  return car.checksum == ret_checksum;
}

void keyboard_io(go_car car, int c) {
        // c=getchar();
        // putchar(c);
    switch(c) {
        case KEY_UP:
            car.right_side = FORWARD_UP;
            car.left_side = FORWARD_UP;
            printw("Up\n");
            break;
        case KEY_DOWN:
            car.right_side = BACKWARD_DOWN;
            car.left_side = BACKWARD_DOWN;
            printw("Down\n");
            break;
        case KEY_LEFT:
            car.right_side = FORWARD_UP;
            car.left_side = BACKWARD_DOWN;
            printw("Left\n");
            break;
        case KEY_RIGHT:
            car.left_side = FORWARD_UP;
            car.right_side = BACKWARD_DOWN;
            printw("Right\n");
            break;
        case ARM_UP:
            car.lift_arm = FORWARD_UP;
            printw("Arm Up\n");
            break;
        case ARM_DOWN:
            car.lift_arm = BACKWARD_DOWN;
            printw("Arm Down\n");
            break;
        case HAND_UP:
            car.ice_hand = FORWARD_UP;
            printw("Hand Up\n");
            break;
        case HAND_DOWN:
            car.ice_hand = BACKWARD_DOWN;
            printw("Hand Down\n");
            break;
        case UNLOCK:
            car.lock = 0x1;
            printw("Unlock\n");
            break;
        default:
            car.left_side = 0x0;
            car.right_side = 0x0;
            car.lift_arm = 0x0;
            car.ice_hand = 0x0;
            // printw("Stop\n"); // prints every time button not being pressed, so commented out
            break;
    }

  //nathan
}

void send_to_serial(go_car car){
  // to do
  return;
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
        c = getch(); // gets keyboard input
        keyboard_io(car, c);

        send_to_serial(car);
        // ... rest of loop ...
    } while (c != '9'); // Pressing '9' ends the loop

    // MUST INCLUDE this to return control to terminal
    endwin(); // restores terminal settings

    return 0;
}


