// include files
#include <iostream>
using namespace std;


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



void send_data_radio(){
 //send the data to the serial radio
  //optionally create a checksum
  //kendall
}


void create_checksum(go_car car){
   //if this takes a few lines put here
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



int main() {
  
}
