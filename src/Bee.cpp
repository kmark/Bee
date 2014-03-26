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

#include "Bee.h"

Bee::Bee(HardwareSerial *serial, unsigned long baud) {
    _serial = serial;
    _serial->begin(baud);
    _frameByte = 0;
    _currentPacket.offset = _currentPacket.size = 0;
}

void Bee::tick() {
    if(!_serial->available()) {
        return;
    }
    
    char c = _serial->read();
    
    if(c == 0x7E) {
        _currentPacket.offset = 0;
        _currentPacket.size = 0;
        _currentPacket.checksum = 0;
        _currentPacket.isEscaped = false;
        delete[] _currentPacket.data;
        _currentPacket.data = NULL;
        return;
    }
    switch(++_currentPacket.offset) {
        case 1:
            _currentPacket.size = c << 8;
            return;
        case 2:
            _currentPacket.size = (_currentPacket.size | c) + 3;
            _currentPacket.data = new char[_currentPacket.size];
            _currentPacket.data[0] = 0x7E;
            _currentPacket.data[1] = ((_currentPacket.size - 3) >> 8) & 0xFF;
            _currentPacket.data[2] = c;
            return;
    }
    if(_currentPacket.isEscaped) {
        _currentPacket.isEscaped = false;
        c ^= 0x20;
    }
    else if(c == 0x7D) {
        _currentPacket.isEscaped = true;
        _currentPacket.offset--;
        return;
    }
    
    _currentPacket.data[_currentPacket.offset] = c;
    
    if(_currentPacket.offset == _currentPacket.size) {
        _currentPacket.checksum = 0xFF - (_currentPacket.checksum & 0xFF);
        Serial.println(_currentPacket.checksum == (uint8_t)c ? "PASSED" : "FAILED");
        
        if(_currentPacket.checksum == c) {
            // Process contents of frame
        }
        return;
    }
    
    _currentPacket.checksum += c;
}

void Bee::_processFrame(BeeCurrentPacket *packet) {
    
}

uint8_t Bee::_checksum(char *packet, uint16_t size) {
    unsigned int sum = 0;
    for(uint16_t i = 3; i < size; i++) {
        sum += packet[i];
    }
    return 0xFF - (sum & 0xFF);
}

void Bee::sendLocalAT(char command[2]) {
    char at[8] = { 0x7E, 0x00, 0x04, 0x08, 0x01, command[0], command[1], 0x00 };
    at[7] = _checksum(at, sizeof at);
    _serial->write(at, sizeof at);
}

void Bee::sendData(String s) {
    int len = s.length();
    char packet[len + 18];
    memset(packet, 0x00, sizeof packet);
    packet[0] = 0x7E;
    packet[1] = 0x00;
    packet[2] = 0x00;
    packet[3] = 0x10;
    packet[4] = 0x01;
    packet[5] = 0x00;
    packet[6] = 0x00;
    packet[7] = 0x00;
    packet[8] = 0x00;
    packet[9] = 0x00;
    packet[10] = 0x00;
    packet[11] = 0xFF;
    packet[12] = 0xFF;
    packet[13] = 0xFF;
    packet[14] = 0xFE;
    packet[15] = 0x00;
    packet[16] = 0x00;
    char *p = packet;
    p += sizeof(char) * 17;
    s.toCharArray(p, len + 1);
    uint16_t packetLength = 14 + len;
    packet[1] = packetLength >> 8;
    packet[2] = packetLength & 0xFF;
    packet[len + 17] = _checksum(packet, sizeof packet);
    for(int i = 0; i < sizeof packet; i++) {
        //Serial.println(packet[i], HEX);
    }
    _serial->write(packet, sizeof packet);
}

void Bee::setCallback(BeeCallback callback) {
    _callback = callback;
}

void Bee::end() {
    _serial->end();
}
