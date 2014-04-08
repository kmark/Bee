# Bee
A simple DigiMesh XBee library for Arduino. Because it doesn't really need to be
that hard. Oh, and it's not done yet.

## Features
* Ability to use any available `HardwareSerial` or `SoftwareSerial` instance
* Extremely simple `loop()` hook, `Bee::tick()`
* Can send local AT commands
* API frame checksum verification
* Proper explicit escaping (requires AP=2)
* Event-driven, i.e.: `Bee::setCallback(myCallback)`
* Broadcasting string data very easily, `Bee::sendData("Hello world!")`
(POC, needs to be rewritten)
* Super easy, supposedly bulletproof, fire-and-forget, escaped, raw byte
broadcasting: `Bee::sendData(myCharArray, sizeof myCharArray)`
* Terminate at any time `XBee::end()`
* Statically initialized, predictable memory usage, no heap fragmentation
* Callback parameter includes a struct with correctly typed pointers to the
internal data array instead of providing a copy. Minimizes memory usage.

## Why Bee?
Comprehensive XBee interface libraries
[already](https://github.com/tomlogic/xbee_ansic_library)
[exist](https://github.com/attie/libxbee3). But for embedded applications,
especially Arduino, they're not an option. Their multiple layers of abstraction
and internal complexity barely allow them to fit within the entirety of
allowable SRAM. It was far easier (and more effective) to start from scratch
rather than heavily refactor existing libraries that had no chance of being
pushed back upstream.

Bee is written with embedded platforms, specifically Arduino, in mind. It needs
to be have small footprint in both compiled size and memory. It also needs to
stay out of the way. This means having as little supporting code in your sketch
as possible. Bee's tick operation must be quick as to not noticeably impact
the average speed of your loop. Dynamic memory allocation should never be
utilized as we risk fragmenting the fragile and tiny heap.

The BeeTest sketch compiles for the Mega 2560 in just 4934 bytes (1%) and 691
bytes (8%) of memory. This includes supporting Arduino platform code. On the Uno
that's about 26% of memory. Both of these are using the default 255 byte buffer
size. By adjusting the buffer (technically the max frame size) you can get these
numbers down considerably. If you never expect to receive a packet over 100
bytes in size that's 155 more bytes of memory you have to work with when
compared to the default.

## Compatibility
Bee has only been compiled/tested on version 1.5.6-r2 of the Arduino IDE and up.
The directory structure can be adapted to work on earlier revisions of the IDE.
It'll definitely work (has been tested) on an Arduino Uno R3 and
Arduino Mega 2560 R3. Should theoretically work on any Arduino. Tested with
XBee PRO 900HP 200K (XBP9B-DM) modules on firmware 0x806A with AP=2 (explicit
escapes).

## Examples
Basic Bee implementations can be found in the example sketch directory. A more
involved usage of Bee is the
[Captain project](https://github.com/kmark/Captain). The two modules use it to
communicate with each other (Uno <-XBee-> Mega).

## TODO
* Refactor or remove the String overload of `sendData`
* Process other frame types like AT Command Responses.
* Determine if the checksum needs to be escaped
* Provide a way to send frames with custom parameters. e.g.: Changing the
destination address of a Transmit Request
* Refactor frame types to their own namespace
* Find a way to change the size of the buffer on compile without having to edit
`Bee.h`
* Optimize `tick` by removing unnecessary operations. Do we really need to zero
the entire data array?

## Licensing
Bee is licensed under the GNU LGPLv3, a supplement to the GNU GPLv3.
Please see `COPYING.md` and `COPYING.LESSER.md` for licensing details.
