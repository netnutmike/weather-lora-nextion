#include <WiFi.h>
#include <AsyncUDP.h>
#include <tempest.h>

const char ssid[] = "alligator-iot";  //  your network SSID (name)
const char pass[] = "22ab3f4ef3";       // your network password

AsyncUDP Udp;
unsigned int multicastPort = 50222;  // local port to listen for UDP packets
IPAddress multicastIP(255,255,255,255);

void setup()
{
  Serial.begin(115200);
  
  delay(250);
  Serial.println("Starting Tempest Reader");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  //Serial.println("Starting UDP");
  //Udp.begin(multicastPort);

  //Udp.beginMulticast(WiFi.localIP(), multicastIP, multicastPort);
  //Udp.listen(multicastPort)
  Serial.printf("Now listening at IP %s and %s, UDP port %d\n", WiFi.localIP().toString().c_str(), multicastIP.toString().c_str(), multicastPort);
}

void loop(){
    //int packetSize = Udp.parsePacket();
    if (Udp.listen(multicastPort)){
      Udp.onPacket([](AsyncUDPPacket packet) {
        Serial.print(", From: ");
        Serial.print(packet.remoteIP());
        Serial.print(":");
        Serial.print(packet.remotePort());
        Serial.print(", To: ");
        Serial.print(packet.localIP());
        Serial.print(":");
        Serial.print(packet.localPort());
        Serial.println();
        Serial.write(packet.data(), packet.length());
        Serial.println();
      
      });
    }
}