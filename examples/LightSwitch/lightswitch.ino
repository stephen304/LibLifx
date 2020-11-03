#include <ESP8266WiFi.h>

// WifiManager: https://github.com/tzapu/WiFiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// OneButton: https://github.com/mathertel/OneButton
#include <OneButton.h>

#include <LibLifx.h>

WiFiManager wifiManager;

uint8_t targetMac[] = {0xD0, 0x73, 0xD5, 0x00, 0x00, 0x00};

WiFiUDP Udp;
LifxDevice device(Udp, targetMac);

#define BTN_DOWN 0
#define BTN_UP   2

OneButton btnDown = OneButton(BTN_DOWN, true, true);
OneButton btnUp = OneButton(BTN_UP, true, true);

void setup() {
  Serial.begin(115200);
  //wifiManager.resetSettings();
  wifiManager.autoConnect();

  btnDown.attachClick([]() {
    Serial.println("Off");
    device.setPower(0, 750);
    device.setColor(0, 0, 18*65535/100, 2500, 750);
  });

  btnDown.attachDoubleClick([]() {
    Serial.println("Dim");
    device.setPower(1, 750);
    device.setColor(0, 0, 18*65535/100, 2500, 750);
  });

  btnUp.attachClick([]() {
    Serial.println("On");
    device.setPower(1, 750);
    device.setColor(0, 0, 65535, 2750, 750);
  });

  btnUp.attachDoubleClick([]() {
    Serial.println("Bright");
    device.setPower(1, 750);
    device.setColor(0, 0, 65535, 3500, 750);
  });
}

void loop() {
  btnDown.tick();
  btnUp.tick();
}
