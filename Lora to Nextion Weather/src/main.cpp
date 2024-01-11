#include <Arduino.h>
#include <WeatherNextion.h>
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

void extractUpdate(char[] buffer)
{
  // extract the update from the buffer
  // update the display

  // 0 - "U," 
  // 1 - str(self.temperature) + "," + 
  // 2 - str(self.humidity) + "," + 
  // 3 - str(self.pressure) + "," + 
  // 4 - str(self.windGust) + "," + 
  // 5 - str(self.windAvg) + "," + 
  // 6 - str(self.precipDayTotal) + "," + 
  // 7 - str(self.rainMinute) + "," + 
  // 8 - str(self.precipType) + "," + 
  // 9 - str(self.lightningCount) + "," + 
  // 10 - str(self.lightningAvgDistance) + "," + 
  // 11 - str(self.UV) + "," + 
  // 12 - str(self.solarRadiation)

  byte index = 0;
  ptr = strtok(buffer, ",");  // delimiter
  while (ptr != NULL)
  {
    strings[index] = ptr;
    index++;
    ptr = strtok(NULL, ",");
  }

  weatherDisplay.setTemp(atof(strings[1]));
  weatherDisplay.setHumidity(atof(strings[2]));
  weatherDisplay.setPressure(atof(strings[3]));
  weatherDisplay.setWindGust(atof(strings[4]));
  weatherDisplay.setRainToday(atof(strings[6]));
  weatherDisplay.setRainRate(atof(strings[7]));
  weatherDisplay.setUV(atof(strings[11]));

  weatherDisplay.updateDisplay();
}

void extractLightning(char[] buffer)
{

    // 0 - "L," 
    // 1 - str(self.lightninLastStrikeDistance)

  byte index = 0;
  ptr = strtok(buffer, ",");  // delimiter
  while (ptr != NULL)
  {
    strings[index] = ptr;
    index++;
    ptr = strtok(NULL, ",");
  }
  
  weatherDisplay.setLightningDistance(atoi(strings[1]));
  weatherDisplay.updateDisplay();
}

void extractWind(char[] buffer)
{

  // 0 - "W,"
  // 1 - str(self.windDirection) + "," + 
  // 2 - str(self.windSpeed)

  byte index = 0;
  ptr = strtok(buffer, ",");  // delimiter
  while (ptr != NULL)
  {
    strings[index] = ptr;
    index++;
    ptr = strtok(NULL, ",");
  }

  weatherDisplay.setWindDirection(atoi(strings[1]));
  weatherDisplay.setWindSpeed(atof(strings[2]));
  weatherDisplay.updateDisplay();

}

void handleInput(char[] buffer)
{
  if (buffer[0] == 'W')
  {
    extractWind(buffer);

  }
  else if (buffer[0] == 'L')
  {
    extractLightning(buffer);
  }
  else if (buffer[0] == 'U')
  {
    extractUpdate(buffer);
    // sendText = "U," + str(self.temperature) + "," + str(self.humidity) + "," + str(self.pressure) + "," + str(self.windGust) + "," + str(self.windAvg) + "," + str(self.precipDayTotal) + "," + str(self.rainMinute) + "," + str(self.precipType) + "," + str(self.lightningCount) + "," + str(self.lightningAvgDistance) + "," + str(self.UV) + "," + str(self.solarRadiation)
  }
  
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
          handleInput((char*)buf);         
          digitalWrite(LED_BUILTIN, LOW);    
        }
    }     
}