#include <Bee.h>

Bee XBee(&Serial3, 19200);

void setup() {
  Serial.begin(115200);
  XBee.begin();
  XBee.setCallback(beeCallback);
  //XBee.sendData("Hello world!");
}

void beeCallback() {
  //
}

void loop() {
  XBee.tick();
}
