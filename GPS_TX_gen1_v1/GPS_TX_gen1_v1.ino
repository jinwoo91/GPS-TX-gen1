#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <SPI.h>
#include <SD.h>

SoftwareSerial gpsSerial(4, 3); // RX, TX
TinyGPSPlus gps;
File dataFile;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  int chipSelect = 10; // pin D10
  SD.begin(chipSelect);

  // Additional setup code here
  Serial.println("GPS_TX_gen1_v1");
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        long timestamp = millis();
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        // Construct data string
        String dataString = String(timestamp) + "," + String(latitude, 6) + "," + String(longitude, 6);

        // Write to SD
        dataFile = SD.open("gps_data.txt", FILE_WRITE);
        if (dataFile) {
          dataFile.println(dataString);
          dataFile.close();
        } else {
          // Handle error
        }
      }
    }
  }

  // Additional loop code here
  
}
