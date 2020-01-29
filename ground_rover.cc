
struct go_car{
   //make bytes for each motor/servo (5 total)
  // potentially one byte for checksum
  std::byte left_side;
  std::byte right_side;
  std::byte lift_arm;
  std::byte ice_hand;
  std::byte lock;
  std::byte checksum;
};


void keyboard_io(){
 //accepts input/output from keyboard
  // ex: if hit up arrow, direction should be forward until stop key is hit
 //if super long make translation from io into data its own function 
  
  //nathan
}



void send_data_radio(){
 //send the data to the serial radio
  //optionally create a checksum
  //kendall
}


void send_data_rover(){
 //see foundation code from last year
  // might not be in c++
  //sends data from radio to car
 //kendall 
}

void check_checksum(){
 //checks checksum from the ack message from rover 
  
  //kendall
}


