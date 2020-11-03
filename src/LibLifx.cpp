#include "Arduino.h"
#include "LibLifx.h"
#include <Ethernet.h>

IPAddress lx_broadcastIP(255, 255, 255, 255);

LifxDevice::LifxDevice(UDP& udp, uint8_t *target) {
  this->_udp = &udp;

  memset(&this->_header, 0, sizeof(lx_header));
  memcpy(this->_header.target, target, sizeof(uint8_t) * LX_ADDRESS_LENGTH);
  this->_header.tagged = 0;
  this->_header.addressable = 1;
  this->_header.protocol = 1024;
  this->_header.source = 0;
  this->_header.sequence = 1;
  this->_header.ack_required = false;
  this->_header.res_required = false;
}

void LifxDevice::init() {
  if (this->_broadcasting) { return; }

  this->_udp->stop();
  this->_udp->begin(LX_BROADCAST_PORT);
  this->_broadcasting = true;
  delay(60);
}

void LifxDevice::setPower(uint16_t level, uint32_t duration) {
  init();

  lx_payload_setPower payload;
  memset(&payload, 0, sizeof(payload));

  this->_header.size = sizeof(lx_header) + sizeof(lx_payload_setPower);
  this->_header.type = LX_TYPE_LIGHT_SETPOWER;

  if (level != 0) {
    payload.level = LX_POWER_LEVEL_ON;
  } else {
    payload.level = LX_POWER_LEVEL_OFF;
  }
  payload.duration = duration;

  _udp->beginPacket(lx_broadcastIP, LX_BROADCAST_PORT);
  _udp->write((uint8_t *)&_header, sizeof(lx_header));
  _udp->write((uint8_t *)&payload, sizeof(lx_payload_setPower));
  _udp->endPacket();

  this->_header.sequence++;
}

void LifxDevice::setColor(
    uint16_t hue,
    uint16_t saturation,
    uint16_t brightness,
    uint16_t kelvin,
    uint32_t duration) {
  init();

  lx_payload_setColor payload;
  memset(&payload, 0, sizeof(payload));

  this->_header.size = sizeof(lx_header) + sizeof(lx_payload_setColor);
  this->_header.type = LX_TYPE_LIGHT_SETCOLOR;

  payload.hue = hue;
  payload.saturation = saturation;
  payload.brightness = brightness;
  payload.kelvin = kelvin;
  payload.duration = duration;

  _udp->beginPacket(lx_broadcastIP, LX_BROADCAST_PORT);
  _udp->write((uint8_t *)&_header, sizeof(lx_header));
  _udp->write((uint8_t *)&payload, sizeof(lx_payload_setColor));
  _udp->endPacket();

  this->_header.sequence++;
}
