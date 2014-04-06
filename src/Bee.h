/*
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

#ifndef _Bee_h
#define _Bee_h

#include "Arduino.h"
#include "SoftwareSerial.h"

struct BeePointerFrame {
    char *frameType;
    uint16_t packetLength;
    uint64_t *source64;
    uint16_t *source16;
    uint16_t dataLength;
    char *data;
};

struct BeeCurrentPacket {
    uint16_t offset;
    uint16_t size;
    uint16_t checksum;
    char data[255];
    bool isEscaped;
};

typedef void (*BeeCallback)(BeePointerFrame *);

class Bee {
public:
    Bee(HardwareSerial *serial, uint32_t baud);
    Bee(SoftwareSerial *serial, uint32_t baud);
    void tick();
    void sendLocalAT(char command[2]);
    void sendData(String data);
    void sendData(char *data, uint16_t size);
    void setCallback(BeeCallback);
    void begin();
    void end();
private:
    // Prevent heap allocation
    void * operator new   (size_t);
    void * operator new[] (size_t);
    void   operator delete   (void *);
    void   operator delete[] (void *);

    uint8_t _checksum(char *packet, uint16_t size);
    void _processFrame();
    bool _escapeRequired(char c);
    uint16_t _available();
    char _read();
    void _write(char c);
    void _write(char *c, uint16_t size);
    HardwareSerial *_serial;
    SoftwareSerial *_serialSoft;
    uint32_t _baud;
    BeeCurrentPacket _currentPacket;
    BeePointerFrame _pointerFrame;
    BeeCallback _callback;
};

enum DigiMeshFrames {
    ATCommand = 0x08,
    ATCommandQRV = 0x09,
    TransferRequest = 0x10,
    ExplicitAddrCmd = 0x11,
    RemoteATCommand = 0x17,
    ATCommandResp = 0x88,
    ModemStatus = 0x8A,
    TransmitStatus = 0x8B,
    RouteInfo = 0x8D,
    AggrAddrUpdate = 0x8E,
    ZigBeeRecv = 0x90,
    ExpRxIndicator = 0x91,
    ZigBeeIODataRx = 0x92,
    NodeIdIndicator = 0x95,
    RemoteATCommandResp = 0x97
};

#endif
