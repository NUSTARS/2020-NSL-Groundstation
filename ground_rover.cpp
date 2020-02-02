// include files
#include "SerialPort.h"
#include <iostream>
#include <string>
//#include "SerialPort.cpp"
using namespace std;

// macros
#define DATA_LENGTH 255

// Data types
struct go_car{
   //make bytes for each motor/servo (5 total)
  // potentially one byte for checksum
  char left_side;
  char right_side;
  char lift_arm;
  char ice_hand;
  char lock;
  char checksum;
};




//Functions 
void keyboard_io(){
 //accepts input/output from keyboard
  // ex: if hit up arrow, direction should be forward until stop key is hit
   // assuming left/right motors have a forward/backward function: left turn: right_side is forward and left_side is backward
 //if super long make translation from io into data its own function 
  
  //nathan
}

void arduino_connect(SerialPort* arduino, char* port_name){
  // connecting
  arduino = new SerialPort(port_name);
  cout << "is connected: " << arduino->isConnected() << endl;

}

void send_data(SerialPort* arduino){
 //send the data to the serial radio
  //optionally create a checksum
  string test = "hello world\n";
  if (arduino->isConnected()){
    bool has_written = arduino->writeSerialPort(test, DATA_LENGTH);
    if (has_written){
      cout << "Data written successfully" << endl;
    }
    else {
      cout << "Data was not written" << endl;
    }
  }
}

void recv_data(){
 //send the data to the serial radio
  //optionally create a checksum
  
}



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


int main(){
  // Global Variables
  char* port_name"\\\\.\\COM20";
  SerialPort *arduino;
  
  //connecting to arduino
  arduino_connect(SerialPort* arduino, char* port_name);

  // for testing can make it end
  while(1)
  {
    // check keyboard

    //send data to radio
    
  }

}


