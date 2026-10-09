#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "imu_data.hpp"

Adafruit_MPU6050 mpu;

const int DT = 2;
Data* dataList;

void setup(void) {
  Serial.begin(9600);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;

    mpu.getEvent(&a, &g, &temp);

    Data data(a.acceleration.x, a.acceleration.y, a.acceleration.z, g.gyro.x, g.gyro.y, g.gyro.z, millis());

    delay(DT);

    Serial.println(data.toString());
}

// void derivative()