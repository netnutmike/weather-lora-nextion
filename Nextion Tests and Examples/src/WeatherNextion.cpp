#include "Arduino.h" 
#include <WeatherNextion.h>
#include <string.h>

WeatherNextion::WeatherNextion() {

}

void WeatherNextion::setWindDirection(int degree)
{
    iWindDirection = degree;

    updateWindDirectionText();
    iWindDirection_dirty = true;
}

void WeatherNextion::updateWindDirectionText()
{
    switch (iWindDirection) {
        case 0 ... 11:
            strcpy( sWindDirectionText, "N");
            break;
        case 12 ... 33:
            strcpy( sWindDirectionText, "NNE");
            break;
        case 34 ... 56:
            strcpy( sWindDirectionText, "NE");
            break;
        case 57 ... 78:
            strcpy( sWindDirectionText, "ENE");
            break;
        case 79 ... 101:
            strcpy( sWindDirectionText, "E");
            break;
        case 102 ... 123:
            strcpy( sWindDirectionText, "ESE");
            break;
        case 124 ... 146:
            strcpy( sWindDirectionText, "SE");
            break;
        case 147 ... 168:
            strcpy( sWindDirectionText, "SSE");
            break;
        case 169 ... 191:
            strcpy( sWindDirectionText, "S");
            break;
        case 192 ... 213:
            strcpy( sWindDirectionText, "SSW");
            break;
        case 214 ... 236:
            strcpy( sWindDirectionText, "SW");
            break;
        case 237 ... 258:
            strcpy( sWindDirectionText, "WSW");
            break;
        case 259 ... 281:
            strcpy( sWindDirectionText, "W");
            break;
        case 282 ... 303:
            strcpy( sWindDirectionText, "WNW");
            break;
        case 304 ... 326:
            strcpy( sWindDirectionText, "NW");
            break;
        case 327 ... 348:
            strcpy( sWindDirectionText, "NNW");
            break;
        case 349 ... 360:
            strcpy( sWindDirectionText, "N");
            break;
    }
}

void WeatherNextion::setWindSpeed(float speed)
{
    fWindSpeed = speed;
    iWindSpeed_dirty = true;
}

void WeatherNextion::setWindGust(float speed)
{
    fWindGust = speed;
    iWindGust_dirty = true;
}

void WeatherNextion::setPressure(float pressure)
{
    fPressure = pressure;
    iPressure_dirty = true;
}

void WeatherNextion::setPressureTrend(int pressureTrend)
{
    iPressureTrend = pressureTrend;
    iPressureTrend_dirty = true;
}

void WeatherNextion::setTemp(float temp)
{
    fTemp = temp;
    fTemp_Celsius = (fTemp-32) * 5/9;
    iTemp_dirty = true;

    calcHeatIndex();
    calcWindChill();
}

void WeatherNextion::setTemp_Celsius(float temp)
{
    fTemp_Celsius = temp;
    fTemp = (fTemp_Celsius * 9/5) + 32;
    iTemp_dirty = true;

    calcHeatIndex();
    calcWindChill();
}

void WeatherNextion::setHumidity(float humidity)
{
    fHumidity = humidity;
    iHumidity_dirty = true;

    calcHeatIndex();
}

void WeatherNextion::setRainRate(int rate)
{
    iRainRate = rate;
    iRainRate_dirty = true;
}

void WeatherNextion::setRainToday(float amount)
{
    fRainToday = amount;
    iRainToday_dirty = true;
}

void WeatherNextion::setRainYesterday(float amount)
{
    fRainYesterday = amount;
    iRainYesterday_dirty = true;
}

void WeatherNextion::setUV(float uv)
{
    fUV = uv;
    iUV_dirty = true;
}

void WeatherNextion::setLightningDistance(int distance)
{
    iLightningDistance = distance;
    iLightningDistance_dirty = true;
}

void WeatherNextion::setLightningTime(int setTime)
{
    iLightningTime = setTime;
    iLightningTime_dirty = true;
}

void WeatherNextion::setLightningAverage(int average)
{
    iLightningAverage = average;
    iLightningAverage_dirty = true;
}

void WeatherNextion::setConditions(int conditions)
{
    iConditions = conditions;
    iConditions_dirty = true;
}

void WeatherNextion::calcHeatIndex () 
{
    const double c1 = -42.379;
    const double c2 = 2.04901523;
        const double c3 = 10.14333127;
        const double c4 = -.22475541;
        const double c5 = -0.00683783;
        const double c6 = -0.05481717;
        const double c7 = 0.00122874;
        const double c8 = 0.00085282;
    const double c9 = -0.00000199;

    double heatIndex = c1 + (c2 * fTemp) +
                           (c3 * fHumidity) +
                           (c4 * fTemp*fHumidity) + 
                           (c5 * (fTemp*fTemp)) +
                           (c6 * (fHumidity * fHumidity)) +
                           (c7 * (fTemp * fTemp) * fHumidity) + 
                           (c8 * fTemp * (fHumidity * fHumidity)) +
                           (c9 * (fTemp * fTemp) * (fHumidity * fHumidity));
    if (fTemp < 80 || fHumidity < 40)
        heatIndex = fTemp;

    fHeatIndex = heatIndex;
    fHeatIndex_Celsius = (fHeatIndex-32) * 5/9;

    iHeatIndex_dirty = true;

}

void WeatherNextion::calcWindChill()
{     
    dWindChill = 35.74 + (0.6215*fTemp) - 35.75 * pow(fWindSpeed,0.16) + (0.4257*fTemp) * pow(fWindSpeed,0.16);

    if (fTemp > 50 || fWindSpeed < 4)
        dWindChill = fTemp;

    fWindChill_Celsius = (dWindChill-32) * 5/9;

    dWindChill_dirty = true;
}

void WeatherNextion::updateDisplay()
{
    if (iWindDirection_dirty)
    {
        Serial.print("windDirection.val=");
        int iWindDirectionadj = iWindDirection + 90;
        if (iWindDirectionadj > 360)
            iWindDirectionadj = iWindDirectionadj - 360;
        Serial.print(iWindDirectionadj);
        Serial.print("\xFF\xFF\xFF");
        iWindDirection_dirty = false;
    }

    if (iWindSpeed_dirty)
    {
        Serial.print("windVal.txt=\"");
        Serial.print(sWindDirectionText);
        Serial.print(" ");
        Serial.print(fWindSpeed);
        //Serial.print(iWindDirection);
        Serial.print("\"\xFF\xFF\xFF");
        iWindSpeed_dirty = false;
    }

    if (iWindGust_dirty)
    {
        Serial.print("gustVal.txt=\"");
        Serial.print(fWindGust);
        Serial.print("\"\xFF\xFF\xFF");
        iWindGust_dirty = false;
    }

    if (iPressure_dirty)
    {
        Serial.print("pressureVal.txt=\"");
        Serial.print(fPressure);
        Serial.print("\"\xFF\xFF\xFF");
        iPressure_dirty = false;
    }

    if (iPressureTrend_dirty)
    {
        Serial.print("pressureTrend.pic=");
        Serial.print(iPressureTrend);
        Serial.print("\xFF\xFF\xFF");
        iPressureTrend_dirty = false;
    }

    if (iTemp_dirty)
    {
        Serial.print("tempVal.txt=\"");
        Serial.print(fTemp);
        Serial.print("\"\xFF\xFF\xFF");
        iTemp_dirty = false;
    }

    if (iHumidity_dirty)
    {
        Serial.print("humidityVal.txt=\"");
        Serial.print(fHumidity);
        Serial.print("\"\xFF\xFF\xFF");
        iHumidity_dirty = false;
    }

    if (iRainRate_dirty)
    {
        Serial.print("rainRate.txt=\"");
        Serial.print(iRainRate);
        Serial.print("\"\xFF\xFF\xFF");
        iRainRate_dirty = false;
    }

    if (iRainToday_dirty)
    {
        Serial.print("rainToday.txt=\"");
        Serial.print(fRainToday);
        Serial.print("\"\xFF\xFF\xFF");
        iRainToday_dirty = false;
    }

    if (iRainYesterday_dirty)
    {
        Serial.print("rainYesterday.txt=\"");
        Serial.print(fRainYesterday);
        Serial.print("\"\xFF\xFF\xFF");
        iRainYesterday_dirty = false;
    }

    if (iUV_dirty)
    {
        Serial.print("uvVal.txt=\"");
        Serial.print(fUV);
        Serial.print("\"\xFF\xFF\xFF");
        iUV_dirty = false;
    }

    if (iLightningDistance_dirty)
    {
        Serial.print("lastStrikeDist.txt=\"");
        Serial.print(iLightningDistance);
        Serial.print("\"\xFF\xFF\xFF");
        iLightningDistance_dirty = false;
    }

    if (iLightningTime_dirty)
    {
        Serial.print("lastStrikeTime.txt=\"");
        Serial.print(iLightningTime);
        Serial.print("\"\xFF\xFF\xFF");
        iLightningTime_dirty = false;
    }

    if (iLightningAverage_dirty)
    {
        Serial.print("lightningAverageVal.txt=\"");
        Serial.print(iLightningAverage);
        Serial.print("\"\xFF\xFF\xFF");
        iLightningAverage_dirty = false;
    }

    if (iConditions_dirty)
    {
        Serial.print("page0.pic=");
        Serial.print(iConditions);
        Serial.print("\xFF\xFF\xFF");
        iConditions_dirty = false;
    }
}