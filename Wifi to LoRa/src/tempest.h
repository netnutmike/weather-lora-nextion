#ifndef tempest_h
#define tempest_h

#include <ArduinoJson.h>

class tempest {
public:
	tempest(int port);
    char getCurrentJSON();
    void newMessage(char message[]);

private:
    // Functions
    void newRapidWind();
    void newHubStatus();
    void newDeviceStatus();
    void newStrike();
    void newObsSt();
    void newSky();
    void sendLora();
    void sendRapidWind();
    void sendStrike();
    void sendObsSt();

    // Variables
    int UDPPort;
    String timestampValue;
    String windLull;
    String windAvg;
    String windGust;
    String windDirection;
    String windSpeed;
    String pressure;
    int pressureInInches;
    String temperature;
    int fahrenheit;
    String humidity;
    String UV;
    String solarRadiation;
    String rainMinute;
    String precipType;
    String precipDayTotal;
    String lightningAvgDistance;
    String lightningCount;
    String lightningLastStrikeDistance;
    String battery;
    String reportInterval;
    String hubserial;
    String deviceUptime;
    String voltage;
    String firmwareVersion;
    String rssi;
    String hubrssi;
    String sensorStatus;
    String uptime;
    String radioStatVersion;
    String radioStatRebootCnt;
    String radioStati2cErrors;
    String radioStatus;
    String RadioStatNetworkID;
    String json;

    StaticJsonDocument<512> newMessageDoc;

};
#endif