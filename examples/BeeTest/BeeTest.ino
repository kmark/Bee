#include <Bee.h>

Bee XBee(&Serial3, 19200);

void setup() {
  Serial.begin(115200);
  XBee.setCallback(beeCallback);
  XBee.begin();
  //XBee.sendData("Hello world!");
}

void beeCallback(BeePointerFrame *frame) {
  Serial.write(frame->data, frame->dataLength);
}

void loop() {
  XBee.tick();
}
