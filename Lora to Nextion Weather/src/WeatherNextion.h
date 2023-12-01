#ifndef WeatherNextion_h
#define WeatherNextion_h
#include "Arduino.h" 

#define CONDITIONS_SUNNY 0
#define CONDITIONS_PARTLY_SUNNY 7
#define CONDITIONS_CLOUDY 4
#define CONDITIONS_RAINING 8
#define CONDITIONS_HEAVY_RAIN 5
#define CONDITIONS_THUNDERSTORM 10
#define CONDITIONS_NIGHT_CLEAR_SKY 3
#define CONDITIONS_NONE 2
#define PRESSURE_STABLE 9
#define PRESSURE_ASCENDING 1
#define PRESSURE_DECENDING 14


class WeatherNextion {
public:
	WeatherNextion();
	void setWindDirection(int degree);
    void setWindSpeed(float speed);
    void setWindGust(float speed);
    void setPressure(float pressure);
    void setPressureTrend(int pressureTrend);
    void setTemp(float temp);
    void setTemp_Celsius(float temp);
    void setHumidity(float humidity);
    void setRainRate(int rate);
    void setRainToday(float amount);
    void setRainYesterday(float amount);
    void setUV(float uv);
    void setLightningDistance(int distance);
    void setLightningTime(int setTime);
    void setLightningAverage(int average);
    void setConditions(int conditions);
    void updateDisplay();
    void calcHeatIndex();
    void calcWindChill();
    void updateWindDirectionText(); 
private:
    // Current Values
    int iWindDirection;
    float fWindSpeed;
    float fWindGust;
    float fPressure;
    int iPressureTrend;
    float fTemp;
    float fTemp_Celsius;
    float fHeatIndex;
    float fHeatIndex_Celsius;
    float fHumidity;
    int iRainRate;
    float fRainToday;
    float fRainYesterday;
    float fUV;
    int iLightningDistance;
    int iLightningTime;
    int iLightningAverage;
    int iConditions;
    double dWindChill;
    float fWindChill_Celsius;
    char sWindDirectionText[4];
    
    // Dirty Flags for each variable
	int iWindDirection_dirty;
    int iWindSpeed_dirty;
    int iWindGust_dirty;
    int iPressure_dirty;
    int iPressureTrend_dirty;
    int iTemp_dirty;
    int iHumidity_dirty;
    int iRainRate_dirty;
    int iRainToday_dirty;
    int iRainYesterday_dirty;
    int iUV_dirty;
    int iLightningDistance_dirty;
    int iLightningTime_dirty;
    int iLightningAverage_dirty;
    int iConditions_dirty;
    int iHeatIndex_dirty;
    int dWindChill_dirty;
};
#endif