// Pin layout:
//  A0: Temperature reading (from TMP36 probe)

const int temperaturePin = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp = getTemp();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" degrees Celcius\n");
  delay(1000);
}

float getTemp() {
  int raw = analogRead(A0);
  float voltage = raw * (5.0 / 1023.0);
  // 0.75V at 25 deg Celcius, 0.01V change per deg Celcius
  float temp = (voltage - 0.5) * 100;
  return temp;
}

