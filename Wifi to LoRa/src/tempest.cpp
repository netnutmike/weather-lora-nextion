#include <tempest.h>
#include "ArduinoJson.h"

tempest::tempest(int port) {
    this->UDPPort = port;
}

char tempest::getCurrentJSON() {

    StaticJsonDocument<512> doc;

    doc["timestamp"] = this->timestampValue;
    doc["windLull"] = this->windLull;
    doc["windAvg"] = this->windAvg;
    doc["windGust"] = this->windGust;
    doc["windDirection"] = this->windDirection;
    doc["windSpeed"] = this->windSpeed;
    doc["pressure"] = this->pressure;
    doc["pressureInInches"] = this->pressureInInches;
    doc["temperature"] = this->temperature;
    doc["fahrenheit"] = this->fahrenheit;
    doc["humidity"] = this->humidity;
    doc["UV"] = this->UV;
    doc["solarRadiation"] = this->solarRadiation;
    doc["rainMinute"] = this->rainMinute;
    doc["precipType"] = this->precipType;
    doc["precipDayTotal"] = this->precipDayTotal;
    doc["lightningAvgDistance"] = this->lightningAvgDistance;
    doc["lightningCount"] = this->lightningCount;
    doc["lightningLastStrikeDistance"] = this->lightningLastStrikeDistance;
    doc["battery"] = this->battery;
    doc["reportInterval"] = this->reportInterval;
    doc["hubserial"] = this->hubserial;
    doc["deviceUptime"] = this->deviceUptime;
    doc["voltage"] = this->voltage;
    doc["firmwareVersion"] = this->firmwareVersion;
    doc["rssi"] = this->rssi;
    doc["hubrssi"] = this->hubrssi;
    doc["sensorStatus"] = this->sensorStatus;
    doc["firmwareVersion"] = this->firmwareVersion;
    doc["uptime"] = this->uptime;
    doc["radioStatVersion"] = this->radioStatVersion;
    doc["radioStatRebootCnt"] = this->radioStatRebootCnt;
    doc["radioStati2cErrors"] = this->radioStati2cErrors;
    doc["radioStatus"] = this->radioStatus;
    doc["RadioStatNetworkID"] = this->RadioStatNetworkID;

    serializeJson(doc, this->json);

    char return_value[] = this->json.c_str();

    return return_value;

}

void tempest::newMessage(char message[]) {


     DeserializationError error = deserializeJson(this->newMessageDoc, message);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    Serial.println(this->newMessageDoc["type"]);

    /*if (doc["type"] == "rapid_wind") {
        newRapidWind(doc);
    } else if (doc["type"] == "hub_status") {
        newHubStatus(doc);
    } else if (doc["type"] == "device_status") {
        newDeviceStatus(doc);
    } else if (doc["type"] == "strike") {
        newStrike(doc);
    } else if (doc["type"] == "obs_st") {
        newObsSt(doc);
    } else if (doc["type"] == "sky") {
        newSky(doc);
    }*/

}

void tempest::newRapidWind() {

}

void tempest::newHubStatus() {

}

void tempest::newDeviceStatus() {

}

void tempest::newDeviceStatus() {

}

void tempest::newStrike() {

}

void tempest::newObsSt() {

}

void tempest::newSky() {

}   

void tempest::sendLora() {

}

void tempest::sendRapidWind() {

}

void tempest::sendStrike() {

}

void tempest::sendObsSt() {

}

