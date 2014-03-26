#include <Bee.h>

Bee *XBee;

void setup() {
  Serial.begin(115200);
  XBee = new Bee(&Serial3, 19200);
  delay(1000);
  XBee->setCallback(beeCallback);
  //XBee->sendData("Hello world!");
}

void beeCallback() {
  //
}

void loop() {
  XBee->tick();
}
