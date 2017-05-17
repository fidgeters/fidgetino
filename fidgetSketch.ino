#include <TheThingsNetwork.h>

#include <TheThingsNetwork.h>
    
#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
const char *appEui = "70B3D57EF0004D4E";
const char *appKey = "0178E98DC4DAB2D46A5DEDA2F2E82F99";
byte prevValue;

void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  pinMode(6, INPUT);
    
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);

    
  debugSerial.println("-- STATUS");
  ttn.showStatus();

  ttn.join(appEui, appKey);

  prevValue = 0;
}


void loop() {    
  // Prepare array of 1 byte to indicate LED status
  byte value = digitalRead(6);

  if (value != prevValue) {
    byte data[1];
    data[0] = value;
    
    ttn.sendBytes(data, sizeof(data));

    prevValue = value;
  }
    
      
  delay(100);
}
