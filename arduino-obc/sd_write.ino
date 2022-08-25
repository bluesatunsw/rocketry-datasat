/*
 * 25/08/2022
 * Priyanta Islam, Liam Ng
 */

#include <SD.h>

#define PIN_SPI_CS 2

File myFile;

String myString = "SD 6.0";


void sd_wr(int pin, String msg){
  
  if (!SD.begin(pin)) {
    Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
    while (1); // don't do anything more:
  }

  Serial.println(F("SD CARD INITIALIZED."));

  // create new file by opening file for writing
  myFile = SD.open("arduino.txt", FILE_WRITE);

  if (myFile) {
    
    myFile.println(msg); // write String variable to SD card in line
    myFile.write("\n"); // new line

    myFile.close();
  } else {
    Serial.print(F("SD Card: error on opening file arduino.txt"));
  }

}


void setup() {
  Serial.begin(9600);

  sd_wr(PIN_SPI_CS, myString);
  

}

void loop() {
}
