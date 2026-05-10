#include <Wire.h>
#include <Adafruit_BNO08x.h>

Adafruit_BNO08x bno08x;
sh2_SensorValue_t sensorValue;

#define PSOC_ADDR 0x08

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!bno08x.begin_I2C()) {
    Serial.println("BNO08x ikke fundet!");
    while (1);
  }

  if (!bno08x.enableReport(SH2_ACCELEROMETER)) {
    Serial.println("Kunne ikke aktivere accelerometer");
    while (1);
  }
}

void loop() {
  if (bno08x.getSensorEvent(&sensorValue)) {

    if (sensorValue.sensorId == SH2_ACCELEROMETER) {

      float x = sensorValue.un.accelerometer.x;
      float y = sensorValue.un.accelerometer.y;
      float z = sensorValue.un.accelerometer.z;

      // Konverter til int (skaleret)
      int16_t xi = (int16_t)(x * 100);
      int16_t yi = (int16_t)(y * 100);
      int16_t zi = (int16_t)(z * 100);

      // Debug
      Serial.print("X: "); Serial.print(xi);
      Serial.print(" Y: "); Serial.print(yi);
      Serial.print(" Z: "); Serial.println(zi);

      // Send til PSoC
      Wire.beginTransmission(PSOC_ADDR);

      Wire.write(0xAA); // start byte
      Wire.write((uint8_t*)&xi, 2);
      Wire.write((uint8_t*)&yi, 2);
      Wire.write((uint8_t*)&zi, 2);

      Wire.endTransmission();
    }
  }

  delay(10);
}