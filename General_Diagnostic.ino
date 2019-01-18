#include <MacRocketry_LED_Diagnostics.h>
#include <MacRocketry_GPS_Shield.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <MacRocketry_SD_Logger.h>

MacRocketry_GPS_Shield gps; //create gps object
MacRocketry_LED_Diagnostics LED; //create LED object
Adafruit_BMP085 bmp; //create bmp object
MacRocketry_SD_Logger SDcard;

void setup() {
  Serial.begin(115200); //for serial monitor
  Serial.println("Start GPS...");
  /*if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }*/
}

void loop() {
  bool gpsdata = gps.readData();
  Serial.print("GPS status: ");
  Serial.println(gpsdata);
  if (gpsdata){ //need to call function readData() every loop. if there is new data, the function returns true
    //gps.displayData();
    Serial.print("UTC: ");
    Serial.print(gps.utc); //access UTC [float]
    Serial.print(" Fix: ");
    Serial.print(gps.fix); //acess fix [int]
    Serial.print(" Altitude ");
    Serial.println(gps.altitude); //acess altitude [float]
  }
  Serial.print("BMP Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");
  
  Serial.print("SD status: ");
  Serial.println(SDcard.writeFile("testing"));
  
  Serial.print("Error code: ");
  Serial.println(LED.StatusCheck(true, gps.fix, SDcard.writeFile("testing")));
  //Serial.println(LED.StatusCheck(true, 1, true));
  
  delay(500);
}
