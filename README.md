# LibLifx
A practical Arduino library for controlling Lifx devices over LAN

## Installation
Clone the repo to your Arduino library folder

## Usage
Tl;dr:

```
#include <LibLifx.h>

uint8_t targetMac[] = {0xD0, 0x73, 0xD5, 0x00, 0x00, 0x00};

WiFiUDP Udp;
LifxDevice device(Udp, targetMac);

// Power on in 750ms
device.setPower(1, 750);

// White, 18% brightness, 2500 kelvin, in 750ms
device.setColor(0, 0, 18*65535/100, 2500, 750);

// Power off in 750ms
device.setPower(0, 750);
```

## License
GPLv3
