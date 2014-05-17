/*
 * Copyright © 2014 Kevin Mark
 *
 * This file is part of Bee.
 *
 * Bee is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bee is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Bee.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SoftwareSerial.h> // Workaround
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
