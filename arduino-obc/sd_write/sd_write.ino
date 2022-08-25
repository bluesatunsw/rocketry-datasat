/*
 * 25/08/2022
 * Priyanta Islam, Liam Ng
 */


#include <SD.h>
#define PIN_SPI_CS 2

uint64_t test[] = {1,2,3,4,5};

/*Takes in the cs signal and buffer as input
*writes binary file to sd card
*/
void sd_wr(int cs, uint64_t buf[]){
  
  File myFile;
  //change this if buffer size changes
  int buffer_size = 5;
  
  if (!SD.begin(cs)) {
    Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
    while (1); // don't do anything more:
  }

  Serial.println(F("SD CARD INITIALIZED."));

  // create new file by opening file for writing
  //SD.remove("data1"); // delete the file if existed
  myFile = SD.open("data1", FILE_WRITE);

  if (myFile) {
    
    for(int i = 0; i < buffer_size; i++) {
       
       myFile.write(buf[i] >> 56);
       myFile.write(buf[i] >> 48);
       myFile.write(buf[i] >> 40);
       myFile.write(buf[i] >> 32);
       myFile.write(buf[i] >> 24);
       myFile.write(buf[i] >> 16);
       myFile.write(buf[i] >> 8);
       myFile.write(buf[i]);
    }
    
     
    

    myFile.close();
  } else {
    Serial.print(F("SD Card: error on opening file arduino.txt"));
  }

}


void setup() {
  Serial.begin(9600);

  sd_wr(PIN_SPI_CS, test);
  
}

void loop() {
}
