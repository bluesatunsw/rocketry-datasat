#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_Si7021.h"
#include <Wire.h>
#include <SPI.h>

/* BMP280 variables (tempurature/altitude/pressure) */
#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp; // I2C

/* MPU variables (accel/gyro/mag)*/
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

/* TODO: si7021 code to be ignored!!!!    */

/* Si7021 variables (temp/humidity) */
// bool enableHeater = false;
// uint8_t loopCount = 0;
// Adafruit_Si7021 sensor = Adafruit_Si7021();


void setup() {
  Serial.begin(19200);
  
  // activate pins :)
  pinMode(6,OUTPUT); // adjust if not 6
  digitalWrite(6,HIGH);
  
  while (!Serial);
  
  // bmp status check
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS);
  if (!status) {
    Serial.println("BMP280 is unfound :( check wires!");
  }

  // // si7021 sensor check 
  // if (!sensor.begin()) {
  //   Serial.println("Si7021 is unfound :( check wires!");
  //   while (true)
  //   ;
  // }

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(22, 21);
  mySensor.setWire(&Wire);
#else
  Wire.begin();
  mySensor.setWire(&Wire);
#endif

  bmp.begin();
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

}

void loop() {

  /*
  *   MPU READINGS
  */
  if (mySensor.accelUpdate() == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    Serial.print("accelX: " + String(aX));
    Serial.print("\taccelY: " + String(aY));
    Serial.print("\taccelZ: " + String(aZ));
    Serial.print("\taccelSqrt: " + String(aSqrt));
  }

  if (mySensor.gyroUpdate() == 0) {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    gZ = mySensor.gyroZ();
    Serial.print("\tgyroX: " + String(gX));
    Serial.print("\tgyroY: " + String(gY));
    Serial.print("\tgyroZ: " + String(gZ));
  }

  if (mySensor.magUpdate() == 0) {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();
    Serial.print("\tmagX: " + String(mX));
    Serial.print("\tmaxY: " + String(mY));
    Serial.print("\tmagZ: " + String(mZ));
    Serial.print("\thorizontalDirection: " + String(mDirection));
  }

  /* 
  *   BMP READINGS
  */
  Serial.print("\tTemperature(*C): ");
  Serial.print(bmp.readTemperature());

  Serial.print("\tPressure(Inches(Hg)): ");
  Serial.print(bmp.readPressure()/3377);


  Serial.print("\tApproxAltitude(m): ");
  Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase

  Serial.println(""); // Add an empty line

  /*
  * Si7021 READINGS (do not work currently)
  // */
  // Serial.print("\tHumidity: ");
  // Serial.print(sensor.readHumidity(), 2);

}
