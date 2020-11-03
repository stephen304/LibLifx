#ifndef LibLifx_h
#define LibLifx_h

#include "Arduino.h"
#include <Udp.h>

#define LX_BROADCAST_PORT 56700
#define LX_PACKET_BUFFER_LENGTH 300
#define LX_ADDRESS_LENGTH 6

// #define LX_TYPE_GET_SERVICE 2
// #define LX_TYPE_STATE_SERVICE 3
// #define LX_TYPE_GET_POWER 20
// #define LX_TYPE_SET_POWER 21
// #define LX_TYPE_STATE_POWER 22

#define LX_TYPE_LIGHT_SETCOLOR 102
#define LX_TYPE_LIGHT_SETPOWER 117

#define LX_POWER_LEVEL_ON 65535
#define LX_POWER_LEVEL_OFF 0

#pragma pack(push, 1)
typedef struct {
  /* FRAME */
  uint16_t size:16;
  uint16_t protocol:12;
  uint8_t  addressable:1;
  uint8_t  tagged:1;
  uint8_t  origin:2;
  uint32_t source:32;
  /* FRAME ADDRESS */
  uint8_t  target[8];
  uint8_t  reserved_a[6];
  uint8_t  res_required:1;
  uint8_t  ack_required:1;
  uint8_t  reserved_b:6;
  uint8_t  sequence:8;
  /* PROTOCOL */
  uint64_t reserved_c:64;
  uint16_t type:16;
  uint16_t reserved_d:16;
  /* PAYLOAD FOLLOWS */
} lx_header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  uint16_t level:16;
  uint32_t duration:32;
} lx_payload_setPower;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  uint8_t  reserved_a:8;
  uint16_t hue:16;
  uint16_t saturation:16;
  uint16_t brightness:16;
  uint16_t kelvin:16;
  uint32_t duration:32;
} lx_payload_setColor;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  uint16_t level:16;
} lx_payload_statePower;
#pragma pack(pop)

class LifxDevice {
  public:
    LifxDevice(UDP& udp, uint8_t *target);
    void setPower(uint16_t level, uint32_t duration);
    void setColor(uint16_t hue,
      uint16_t saturation,
      uint16_t brightness,
      uint16_t kelvin,
      uint32_t duration);

  private:
    void init();

    UDP*        _udp;
    boolean     _broadcasting;
    lx_header   _header;
    int         _timeout;
};
#endif
