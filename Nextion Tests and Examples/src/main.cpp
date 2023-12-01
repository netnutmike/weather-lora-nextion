#include <Arduino.h>
#include <WeatherNextion.h>

/*
This is a test program to test the WeatherNextion class and the nextion display

*/

void setup() {
  Serial.begin(38400);
}

void loop() {

  WeatherNextion weatherDisplay;

  for (int i=1; i<=360; i++)
  {
    weatherDisplay.setWindDirection(i);
    weatherDisplay.setWindSpeed(i);
    weatherDisplay.setWindGust(i);
    weatherDisplay.setPressure(i);
    weatherDisplay.setTemp(i);
    weatherDisplay.setHumidity(i);
    weatherDisplay.setRainRate(i);
    weatherDisplay.setRainToday(i);
    weatherDisplay.setRainYesterday(i);
    weatherDisplay.setUV(i);
    weatherDisplay.setLightningDistance(i);
    weatherDisplay.setLightningTime(i);
    //weatherDisplay.setLightningAverage(i);

    weatherDisplay.updateDisplay();
   
    delay(500);    
  }                 
}