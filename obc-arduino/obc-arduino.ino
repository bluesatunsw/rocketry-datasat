#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <MPU9250_asukiaaa.h>

// Define pins for SD card module
#define SD_CS 5
#define MPU_CS 37
#define BMP_CS 36
#define SI_CS 7
#define SDA_PIN 4
#define SCL_PIN 21


#define LAUNCH_ARM_SECONDS 0

// Initialize SD card object
File dataFile;
File logfile;

// Initialize BMP280 sensor object
Adafruit_BMP280 bmp;

// Initialize MPU9250 sensor object
MPU9250_asukiaaa imu;

// MPU readings
float ax;
float ay;
float az;
float gx;
float gy;
float gz;
float mx;
float my;
float mz;

// SD file index
uint16_t fileIndex = 0;

void setup() {
  Serial.begin(115200);

  // Initialize SD card
  pinMode(SD_CS, OUTPUT);
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialization success.");

  // Log SD card initialization
  logfile = SD.open("/log.txt", FILE_APPEND);
  if (logfile) {
    String logmsg = String(millis()) + " SD card initialization success.";
    logfile.println(logmsg);
    logfile.close();
  } else {
    Serial.println("SD card inoperable!");
    while (1);
  }

  // Generate datafile
  String filename = "/data" + String(fileIndex) +".txt";
  dataFile = SD.open(filename, FILE_WRITE);

  // Init i2c
  Wire.begin(SDA_PIN, SCL_PIN);
  imu.setWire(&Wire);


  // Initialize BMP280 sensor
  if (!bmp.begin(0x76)) {
    log("BMP280 unresponsive!");
  } else {
    log("BMP280 sensor initialised.");
  }

  // Safety window for rocket setup.
  log("Entering launch safety window.");
  int count = LAUNCH_ARM_SECONDS / 10;
  while (count > 0) {
    String ttl = String(count*10) + " seconds remaining till system is armed";
    logMutable(ttl);
    count--;
    delay(10000);
  }

  // Initialize MPU9250 sensor
  imu.beginAccel();
  imu.beginGyro();
  imu.beginMag();

  // Log MPU9250 sensor initialization
  log("MPU9250 sensor initialization success.");

  // Wait for rocket launch
  log("Waiting for rocket launch...");
  float prev_az = 0.0;
  float curr_az = 0.0;
  while (true) {

    if (imu.accelUpdate() == 0);
      curr_az = imu.accelZ();
    // Serial.println(curr_az);
    if (curr_az > prev_az + 1.0) {
      break;
    }
    prev_az = curr_az;
    delay(250);
  }
  Serial.println("Rocket launch detected!");

  // Log rocket launch detection
  logfile = SD.open("/log.txt", FILE_APPEND);
  if (logfile) {
    String logmsg = String(millis()) + " Rocket launch detected!";
    logfile.println(logmsg);
    logfile.close();
  }

}

void loop() {
  // Read data from BMP280 sensor
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();

  // Read data from MPU9250 sensor
  if (imu.accelUpdate() == 0 && imu.gyroUpdate() == 0 && imu.magUpdate() == 0) {
    ax = imu.accelX();
    ay = imu.accelY();
    az = imu.accelZ();
    gx = imu.gyroX();
    gy = imu.gyroY();
    gz = imu.gyroZ();
    mx = imu.magX();
    my = imu.magY();
    mz = imu.magZ();
  }


  // Open a new file every 512 bytes
  if (dataFile.size() >= 500) {
    if (dataFile) {
      dataFile.close();
    }
    String filename = String("/data") + String(fileIndex) + String(".txt");
    fileIndex++;
    dataFile = SD.open(filename, FILE_WRITE);
    if (!dataFile) {
      String err = "Error opening file for writing - file "+ filename; 
      logMutable(err);
      return;
    } else {
      String msg = "File #" + String(fileIndex -1) + " finished. Starting " + filename;
      logMutable(msg);
    }
  }

  // Write data to file
  dataFile.print(temperature);
  dataFile.print(",");
  dataFile.print(pressure);
  dataFile.print(",");
  dataFile.print(millis());
  dataFile.print(": ");
  dataFile.print(ax);
  dataFile.print(",");
  dataFile.print(ay);
  dataFile.print(",");
  dataFile.print(az);
  dataFile.print(",");
  dataFile.print(gx);
  dataFile.print(",");
  dataFile.print(gy);
  dataFile.print(",");
  dataFile.print(gz);
  dataFile.print(",");
  dataFile.print(mx);
  dataFile.print(",");
  dataFile.print(my);
  dataFile.print(",");
  dataFile.println(mz);

  // Flush data to SD card
  dataFile.flush();
}


void log(const char* msg) {
  logfile = SD.open("/log.txt", FILE_APPEND);
  if (logfile) {
    String logmsg = String(millis()) +": " + msg;
    logfile.println(logmsg);
    logfile.close();
    Serial.println(logmsg);
  }
}

// Log a message to the SD card and serial, but for mutable C++ strings
void logMutable(String s) {
  logfile = SD.open("/log.txt", FILE_APPEND);
  if (logfile) {
    String logmsg = String(millis()) +": " + s;
    logfile.println(logmsg);
    logfile.close();
    Serial.println(logmsg);
  }
}