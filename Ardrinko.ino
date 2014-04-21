#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <stdint.h>

// Pin layout:
//  A0: Temperature reading (from TMP36 probe)
//  A1: Photo resistor (SEN-09088)

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xB8, 0x93 };
IPAddress ip(10, 5, 0, 10);
IPAddress remote_ip(10, 5, 0, 1);
EthernetUDP Udp;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Udp.begin(54369);
}

void loop() {
  int32_t temp = getTemp();
  int32_t door = getDoor();
  Udp.beginPacket(remote_ip, 54369);
  Udp.write((uint8_t*)&temp, sizeof(int32_t));
  Udp.write((uint8_t*)&temp, sizeof(int32_t));
  Udp.write((uint8_t*)&temp, sizeof(int32_t));
  Udp.write((uint8_t*)&temp, sizeof(int32_t));
  Udp.write((uint8_t*)&door, sizeof(int32_t));
  Udp.endPacket();
  delay(100);
}

float readVoltage(int pin) {
  return analogRead(pin) * (5.0 / 1023.0);
}

int32_t getTemp() {
  float voltage = readVoltage(A0);
  // 0.75V at 25 deg Celcius, 0.01V change per deg Celcius
  float temp = (100 * voltage) - 75;
  return (int32_t)(temp * 100);
}

int32_t getDoor() {
  return (int32_t)analogRead(A1) > 700;
}

