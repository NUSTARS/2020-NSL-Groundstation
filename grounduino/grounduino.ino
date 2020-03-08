#include <SPI.h>
#include <RH_RF95.h>

#define RF95_FREQ 915.0
#define RFM95_RST 4

RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95 

void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  };
  rf95.setTxPower(23, false);
  

}

uint8_t data[10] = {0};

void loop()
{
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server

  if (Serial.available()) {
    String in = Serial.readString();
    in.toCharArray((char*)data, 10);
  }
  
  rf95.send(data, sizeof(data));
  
  rf95.waitPacketSent();
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  delay(400);
}
