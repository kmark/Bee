# Bee
A simple DigiMesh XBee library for Arduino. Because it doesn't really need to be that hard. Oh, and it's nowhere near done.

## Features
* Ability to use any available `HardwareSerial`
* Extremely simple `loop()` hook, `XBee->tick()`
* Can send local AT commands
* API frame checksum verification
* Event-driven, `XBee->setCallback(myCallback)`
* Broadcasting string data very easily, `XBee->sendData("Hello world!")` (POC, needs to be rewritten)
* Terminate at any time to use the `HardwareSerial` elsewhere, `XBee->end()`
* Processes incoming Explicit Rx Indicators `0x91` (data) but do absolutely nothing with it

## The problem
Comprehensive XBee interface libraries [already](https://github.com/tomlogic/xbee_ansic_library) [exist](https://github.com/attie/libxbee3). But for embedded applications, especially Arduino, they're not an option. Their multiple layers of abstraction and internal complexity barely allow them to fit within the entirety of allowable SRAM. It was far easier (and more effective) to start from scratch rather than heavily refactor existing libraries that had no chance of being pushed back upstream.

## The solution
Bee defines simple not by *easy to use* but by *easy to understand*. By keeping the codebase small and efficient we are not only optimizing for embedded platforms (i.e. Arduino) but lowering the barrier to extension. If you want to do something Bee can't do (or philosophically won't) you'll need to extend it. Reliably modifying code you did not write requires a significant portion of time spent on familiarizing yourself with the code that's already there. The simpler the library, the sooner you get back to your project. Since Bee is built directly for Arduino users, there's no need to understand Makefiles, build scripts, linking, or dependencies. 

## Compatibility
Bee has only been compiled/tested on version 1.5.6-r2 of the Arduino IDE and up. The directory structure can be adapted to work on earlier revisions of the IDE. It'll definitely work (has been tested) on an Arduino Mega 2560. Should theoretically work on any Arduino that has HardwareSerial support. Tested with XBee PRO 900HP 200K (XBP9B-DM) modules on firmware 0x806A with AP=2.

## Examples
Please refer to the examples sketch directory.

## Licensing
Bee is licensed under the GNU LGPLv3, a supplement to the GNU GPLv3. Please see `COPYING.md` and `COPYING.LESSER.md` for licensing details.
