/**
 * Author: Dennis Ruigrok
 * There seems to be a bug with the x axes. so i don't use them
 * use the sodaq explorer with nbiot shield as a badge, so that u use the y and z axes
 * then it works fine
 * */
 

#include <sodaq_compass.h>

NBIOT_Compass compass;
#include <Wire.h>

void setup() {
  SerialUSB.begin(9600);
  compass.setup();  
}
float X,Y,Z;
float heading, headingDegrees, headingFiltered, geo_magnetic_declination_deg;

void loop() {
  float xguass, yguass, zguass;
  
    compass.getNewValues();
    xguass = compass.getXGauss();    
   yguass = compass.getYGauss();
   zguass = compass.getZGauss();

  
  
  SerialUSB.println("The fieldstrengths are:");
  SerialUSB.print("X: ");
  SerialUSB.print(xguass, 6);
  SerialUSB.println(" Guass.");
  SerialUSB.print("Y: ");
  SerialUSB.print(yguass, 6);
  SerialUSB.println(" Guass.");
  SerialUSB.print("Z: ");
  SerialUSB.print(zguass, 6);
  SerialUSB.println(" Guass.");
  X = xguass / 32768; // 2^15 because one of the 16 bits is for positive negative
  Y = yguass / 32768;
  Z = zguass / 32768;
  
  // Correcting the heading with the geo_magnetic_declination_deg angle depending on your location
  // You can find your geo_magnetic_declination_deg angle at: http://www.ngdc.noaa.gov/geomag-web/
  // At zzz location it's 4.2 degrees => 0.073 rad
  // Haarlem                    2017-10-20  1° 4' E  ± 0° 22'  changing by  0° 9' E per year
  // Amsterdam                  2017-10-20  1° 9' E  ± 0° 22'  changing by  0° 9' E per year
  // Alkmaar 52.6324 4.7534     2017-10-20  1.09° E  ± 0.38°  changing by  0.14° E per year
  geo_magnetic_declination_deg = 1.09; // for our location
  
  headingDegrees = 180*atan2(Y, Z)/PI;  // assume pitch, roll are 0
 
  if (headingDegrees <0)
    headingDegrees += 360;
 
  //Sending the heading value through the Serial Port 
  
  SerialUSB.println(headingDegrees,6);
  
delay(1000);
}


