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

void extractUpdate(char[] buffer)
{
  // extract the update from the buffer
  // update the display

  // sendText = "U," + str(self.temperature) + "," + str(self.humidity) + "," + str(self.pressure) + "," + str(self.windGust) + "," + str(self.windAvg) + "," + str(self.precipDayTotal) + "," + str(self.rainMinute) + "," + str(self.precipType) + "," + str(self.lightningCount) + "," + str(self.lightningAvgDistance) + "," + str(self.UV) + "," + str(self.solarRadiation)

  byte index = 0;
   ptr = strtok(array, ",");  // delimiter
   while (ptr != NULL)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }
   //Serial.println(index);
   // print all the parts
   Serial.println("The Pieces separated by strtok()");
   for (int n = 0; n < index; n++)
   {
      Serial.print(n);
      Serial.print("  ");
      Serial.println(strings[n]);
   }
   //Those values are Sunlight,Humidity,Temperature,Pressure,Dewpoint.
  // use the atoi() and atof() functions to convert ASCII strings to numbers.
   Sunlight = atoi(strings[0]); //http://www.cplusplus.com/reference/cstdlib/atoi/?kw=atoi
   Humidity = atoi(strings[1]);
   Temperature = atoi(strings[2]);
   Pressure = atof(strings[3]); //http://www.cplusplus.com/reference/cstdlib/atof/?kw=atof
   Dewpoint = atoi(strings[4]);
}

void extractLightning(char[] buffer)
{

    // sendText = "L," + str(self.lightninLastStrikeDistance)

  byte index = 0;
   ptr = strtok(array, ",");  // delimiter
   while (ptr != NULL)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }
   //Serial.println(index);
   // print all the parts
   Serial.println("The Pieces separated by strtok()");
   for (int n = 0; n < index; n++)
   {
      Serial.print(n);
      Serial.print("  ");
      Serial.println(strings[n]);
   }
   //Those values are Sunlight,Humidity,Temperature,Pressure,Dewpoint.
  // use the atoi() and atof() functions to convert ASCII strings to numbers.
   Sunlight = atoi(strings[0]); //http://www.cplusplus.com/reference/cstdlib/atoi/?kw=atoi
   Humidity = atoi(strings[1]);
   Temperature = atoi(strings[2]);
   Pressure = atof(strings[3]); //http://www.cplusplus.com/reference/cstdlib/atof/?kw=atof
   Dewpoint = atoi(strings[4]);
}

void extractWind(char[] buffer)
{

  // sendText = "W," + str(self.windDirection) + "," + str(self.windSpeed)

  byte index = 0;
   ptr = strtok(array, ",");  // delimiter
   while (ptr != NULL)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }
   //Serial.println(index);
   // print all the parts
   Serial.println("The Pieces separated by strtok()");
   for (int n = 0; n < index; n++)
   {
      Serial.print(n);
      Serial.print("  ");
      Serial.println(strings[n]);
   }
   //Those values are Sunlight,Humidity,Temperature,Pressure,Dewpoint.
  // use the atoi() and atof() functions to convert ASCII strings to numbers.
   Sunlight = atoi(strings[0]); //http://www.cplusplus.com/reference/cstdlib/atoi/?kw=atoi
   Humidity = atoi(strings[1]);
   Temperature = atoi(strings[2]);
   Pressure = atof(strings[3]); //http://www.cplusplus.com/reference/cstdlib/atof/?kw=atof
   Dewpoint = atoi(strings[4]);
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
          handleInput((char*)buf)           
          digitalWrite(LED_BUILTIN, LOW);    
        }
    }

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