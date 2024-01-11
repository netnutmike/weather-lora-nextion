# weather-lora-nextion

## About

In this project we are going to receive a message via LoRa from a weather station and update a Nextion display with the latest weather details.

This project came about because I have some neighbors that look at public weather network sites to get details from the Tempest weather station on my roof.

The public sites only update every few minutes and do not report on all of the sensors that are available on the Tempest weather station.  For example, the Tempest weather system has lightning detection but that is not available on the public weather networks.

There is another repo in my git repos that handles the receiving the messages from the Tempest and transmits them via LoRa in a more compact format because LoRa is a low speed medium.

## Nextion Display

In this project we are going to use a Nextion display to show the weather data.  The advantage to a nextion display is that you design the screen in a the nextion editor and then update the screen via a serial interface.

This makes writing code super simple and makes it easy to make changes to the display without needing to make changes to the source code.

The other advantage is you can change screen sizes easily.  The serial interface sends commands to set variables that can be on multiple screens.  If you have multiple size screens, you can design each screen and as long as you use the same names for the objects (variables) you can just change the cable and use the same code.

I have created the nextion screen for the 400x240 screen size.  I have included the source files that were used to create the interface.

I encourage everyone to make a better version and add it to the screen options.  If you look in the nextion folder you can find my and another other screens.  In the 400x240 folder there are details about the names of the elements for each page.

## Nextion Class

You will find a Class for the Nextion screen that I created to make the interface to the Nextion very simple.

## Solution Architecture

Here is an architecture overview that shows the overall system:

![Solution Architecture](Solution%20Architecture.jpg)

## The Nextion Class

The Nextion class has functions for each weather variable to be set.  When you call a dunction like setTemp it takes Farenheight as the input but in the background it also sets the Celsius value.

The class also only sends the weather values that have changed.  This makes the serial interface more efficient.  The Tempest sends once a minute an update for most of the weather values.  However it sends wind updates every few seconds and lightning updates as soon as a strike happens.

By sending only changed values the serial interface can beless utilized provind more time for the LoRa messages.

### Nextion Class Application Architecture

Below is a high level overview of how the class works.

![Application Architecture](Application%20Architecture.jpg)

### Nextion Class Functions

#### setWindDirection(int degree)
Sets the wind direction by degree.  Valid input is 0 - 359
After set, it calculates the proper abreviation for the wind direction (N, NNE, NE, ENE, E, etc)

#### setWindSpeed(float speed)
Sets the wind speed to a MPH value
After set, it calculates the KPH value and the wind chill

#### setWindGust(float speed)

#### setPressure(float pressure)

#### setPressureTrend(int pressureTrend)

#### setTemp(float temp)
Sets the temperature to a Farenheigt value
After set, it calculates the Celsius value, the wind chill and the heat index

#### setTemp_Celsius(float temp)
Sets the temperature to a Celsius value
After set, it calculates the Farenheight value, the wind chill and the heat index

#### setHumidity(float humidity)
Sets the humidity to a percentage value, do not include the percent sign (%)
After set, it calculates the heat index

#### setRainRate(int rate)

#### setRainToday(float amount)

#### setRainYesterday(float amount)

#### setUV(float uv)

#### setLightningDistance(int distance)

#### setLightningTime(int setTime)

#### setLightningAverage(int average)

#### setConditions(int conditions)

#### updateDisplay()
