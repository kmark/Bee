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

struct ExpRxIndFrame {
    uint16_t packetLength;
    uint64_t source64;
    uint16_t source16;
    uint16_t dataLength;
    uint8_t data[];
};

struct BeeCurrentPacket {
    uint16_t offset;
    uint16_t size;
    uint16_t checksum;
    char *data;
    bool isEscaped;
};

typedef void (*BeeCallback)();

class Bee {
public:
    Bee(HardwareSerial *serial, unsigned long baud);
    void tick();
    void sendLocalAT(char command[2]);
    void sendData(String data);
    void setCallback(BeeCallback);
    void end();
private:
    uint8_t _checksum(char *packet, uint16_t size);
    void _processFrame(BeeCurrentPacket *packet);
    HardwareSerial *_serial;
    uint16_t _frameByte;
    ExpRxIndFrame _currentFrame;
    BeeCurrentPacket _currentPacket;
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
