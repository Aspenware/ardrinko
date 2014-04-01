#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <stdint.h>

// Pin layout:
//  A0: Temperature reading (from TMP36 probe)

const int temperaturePin = 0;
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
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" degrees Celcius\n");
  Udp.beginPacket(remote_ip, 54369);
  Udp.write("Hello from arduino!");
  //uint8_t *buf = (uint8_t*)temp;
  //Udp.write(buf, sizeof(int32_t));
  //Udp.write(buf, sizeof(int32_t));
  //Udp.write(buf, sizeof(int32_t));
  //Udp.write(buf, sizeof(int32_t));
  Udp.endPacket();
  delay(1000);
}

int32_t getTemp() {
  int raw = analogRead(A0);
  float voltage = raw * (5.0 / 1023.0);
  // 0.75V at 25 deg Celcius, 0.01V change per deg Celcius
  float temp = (voltage - 0.5) * 100;
  return (int32_t)(temp * 100);
}

