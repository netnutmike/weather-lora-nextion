#include <Arduino.h>
#include <WeatherNextion.h>
#include <SPI.h> 
#include <RH_RF95.h>

#define RFM95_CS    8
#define RFM95_INT   7
#define RFM95_RST   4

#define RF95_FREQ 915.0

// Singleton instance of the radio driver 
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(38400);

  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(RFM95_RST, OUTPUT);  
  digitalWrite(RFM95_RST, HIGH);

  // manual reset  
  digitalWrite(RFM95_RST, LOW);  
  delay(10);  
  digitalWrite(RFM95_RST, HIGH);  
  delay(10);  

  rf95.init()
  rf95.setFrequency(RF95_FREQ)
  rf95.setTxPower(23, false);
}

void loop() {

  WeatherNextion weatherDisplay;

  if (rf95.available()) 
    {    
      // Should be a message for us now    
      uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];    
      uint8_t len = sizeof(buf);    
      if (rf95.recv(buf, &len)) 
        {      
          digitalWrite(LED_BUILTIN, HIGH);      
          RH_RF95::printBuffer("Received: ", buf, len);      
          Serial.print("Got: ");      
          Serial.println((char*)buf);       
          Serial.print("RSSI: ");      
          Serial.println(rf95.lastRssi(), DEC); 
          digitalWrite(LED_BUILTIN, LOW);    }

  /*for (int i=1; i<=360; i++)
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
  }           */      
}