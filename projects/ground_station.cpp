// include files
//#include "SerialPort.h"
#include <iostream>
#include <string>
#include <cstddef>
#include <ncurses.h>
#include <curses.h>
// NOTE: MAY NEED TO CHANGE YOUR PATH TO WHERE Python.h IS INCLUDED
#include <C:\cygwin64\usr\include\python3.6m\Python.h>
// #include <C:\users\Kendall Kuzminskas\appdata\local\programs\python\python36\include\Python.h>
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

// int check_open_pw()

go_car keyboard_io(go_car car, int c) {
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
    return car;
  //nathan
}

int send_to_serial(go_car car){
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue, *pGlobals;
    // to do
    pName = PyUnicode_FromString("send_data");
        /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "run_func");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(5);
            // PyLong_FromSize_t()
            pValue = PyLong_FromLong(car.lock);
            PyTuple_SetItem(pArgs, 4, pValue);

            pValue = PyLong_FromLong(car.ice_hand);
            PyTuple_SetItem(pArgs, 3, pValue);

            pValue = PyLong_FromLong(car.lift_arm);
            PyTuple_SetItem(pArgs, 2, pValue);

            pValue = PyLong_FromLong(car.right_side);
            PyTuple_SetItem(pArgs, 1, pValue);

            pValue = PyLong_FromLong(car.left_side);
            PyTuple_SetItem(pArgs, 0, pValue);
            // char hello[] = "hello";
            // pValue = PyLong_FromLong(atoi(hello));
            // if (!pValue) {
            //     Py_DECREF(pArgs);
            //     Py_DECREF(pModule);
            //     printf( "Cannot convert argument\n");
            //     return 1;
            
            // /* pValue reference stolen here: */
            
            
            // }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            // if (pValue != NULL) {
            //     printf("Result of call: %ld\n", PyLong_AsLong(pValue));
            //     Py_DECREF(pValue);
            // }
            // else {
            //     Py_DECREF(pFunc);
            //     Py_DECREF(pModule);
            //     PyErr_Print();
            //     fprintf(stderr,"Call failed\n");
            //     return 1;
            // }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        // fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    return 1;
}

// int check_password(char input_pw[],go_car car, char real_pw[]){
//     int inp_size = sizeof(input_pw)/sizeof(*input_pw);
//     int real_size = sizeof(real_pw)/sizeof(*real_pw);
//     if (inp_size < real_size){
//         return 0;
//     }
//     for (int i=0; i<real_size; i++)
//     {   
//         if(input_pw[i] != real_pw[i]){
//             printw("Not equal: attempt - %s, real -%s", input_pw[i], real_pw[i]);
//             return 0;
//         }
//     }
//     keyboard_io(car, UNLOCK);
//     printw("Car is unlocked\n");
//     return 1;
// }


int main() {
    // MUST INCLUDE these lines to set up curses.h
    initscr(); // initializes ncurses
    cbreak(); // disables buffering, takes char-at-a-time input
    noecho(); // suppress auto echoing of typed chars
    keypad(stdscr, TRUE); // allows us to capture special key strokes (arrow keys)
    nodelay(stdscr, TRUE); // does not pause program to wait for typed char
    scrollok(stdscr, TRUE); // window will scroll when full
    
    char filename[] =  "send_data.py";
    char module[] = "main";
    FILE* fp;
    // PyObject *pName, *pModule, *pDict, *pFunc;
    // PyObject *pArgs, *pValue, *pGlobals;

	Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");
    // // fp = _Py_fopen(filename, "r");
    // PyRun_SimpleString("print('Hello World from Embedded Python!!!')");
    // // PyRun_SimpleFile(fp, filename);
    // // pArgs = PyUnicode_FromString("Hello");
    // // PyRun_File(fp, filename, 1, pGlobals, pArgs);
	// PyRun_SimpleString("print('Hello World 2 from Embedded Python!!!')");
	// pName = PyUnicode_FromString(module);
    // pModule = PyImport_Import(pName);
    go_car car2;
    // car2.ice_hand = 0x1;
    car2.lock = 0x2;
    // car2.left_side = 0x0;
    car2.right_side = 0x0;
    // car2.lift_arm = 0x0;
    printf("car2: %d\n", car2.lock);
    send_to_serial(car2);

    go_car car;
    int c;
    char real_pw[] = {'h', 'e','\0'};
    int n = 3;
    int c_pw_i = 0;
    int password_lock = 0;
    int pw_check = 0;
    // send_to_serial(car);
    // LOOP:
    // do {
    //     c = getch(); // gets keyboard input
    //     if (c != 0xffffffff){
    //         if (password_lock){
    //             // car = keyboard_io(car, c);
    //             send_to_serial(car);
    //         }else if (password_lock==0){
    //             if (c == 0xa){
    //                 if(pw_check == 2){
    //                     password_lock = 1;
    //                 }
    //                 c_pw_i = 0;
    //                 pw_check = 0; 
    //             } else{
    //                 if(c_pw_i >= n){
    //                     printw("Error\n");
    //                     pw_check =0;
    //                     c_pw_i = 0;
    //                 }
    //                 if (c == (real_pw[c_pw_i])&0xFF){
    //                     pw_check ++;
    //                 }
    //                 // printw("Test: c - %x\n", c);
    //                 // printw("Real pw[%d]: %x\n", c_pw_i,real_pw[c_pw_i]);
    //                 // printw("Real pw: %s\n", real_pw);
    //                 // printw("Pw check: %d\n\n", pw_check);
    //                 c_pw_i ++;
    //             }
    
    //         }
    //     }
    //     // ... rest of loop ...
    // } while (c != '9'); // Pressing '9' ends the loop

    // // MUST INCLUDE this to return control to terminal
    // endwin(); // restores terminal settings

    Py_Finalize();
    return 0;
}


