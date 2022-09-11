#include <SmmvsESP32HTTP.h>
#include <ArduinoJson.h>

#define ACCESSKEY "hrAEYXlyJ67HI0yODgUwVc7d2ORZLYHHHf9FSUtZDNZY0y9Sgu0DjhzGEUC5" // Ganti dengan access key akun SMMVS server anda
//#define WIFISSID "Armina Aha_plus"         // Ganti dengan SSID WiFi anda
//#define PASSWORD "10021988"     // Ganti dengan password WiFi anda
#define WIFISSID "new1comando"
#define PASSWORD "galonair"

// Connect with local network
// send data with HTTP POST use sendNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint) function

// send data with HTTP GET getNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint, String data) function
const char *_serverChar = "192.168.1.25";
const int httpPort = 80;
String _serverNoHttpLocal = "192.168.1.25";
String endpoint = "/api/data";

// Connect with internet connection
// send data with HTTP POST use send() function
// send data with HTTP GET get(String data) function
SmmvsESP32HTTP smmvs(ACCESSKEY); // Buat objek SMMVS

void setup()
{
  Serial.begin(115200);                     // Buka komunikasi serial dengan baudrate 115200
  smmvs.setDebug(true);                     // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  smmvs.wifiConnection(WIFISSID, PASSWORD); // Mencoba untuk menyambungkan ke WiFi
}

void loop()
{

  // Memasukkan nilai-nilai variabel ke penampungan data sementara
  String device_name = "Truk6ss";
  String rn = "cnt-n1PnYtBOQIuEDuMq";
  String totalDHT = "102";
  String rataSuhu = "25.6";
  String temp1 = "20";
  String temp2 = "20";
  String temp3 = "20";
  String temp4 = "20";
  String temp5 = "20";
  String temp6 = "20";
  String hum1 = "20";
  String hum2 = "20";
  String hum3 = "20";
  String hum4 = "20";
  String hum5 = "20";
  String hum6 = "20";
  String banFrontLeft = "32";
  String banFrontRight = "32";
  String banBackLeft = "36";
  String banBackRight = "36";
  String movementA = "20";
  String movementB = "20";
  String emergencyButton = "1";
  String lat = "-7.898989";
  String lon = "8.8798688";
  String speed = "0.37";
  String gpsTime = "2022-08-148:09:45";
  String volt = "23.4";

  // HTTP GET
  String data = "?device_name=" + device_name + "&rn=" + rn + "&totalDHT=" + totalDHT + "&temp1=" + temp1 + "&temp2=" + temp2 + "&temp3=" + temp3 + "&temp4=" + temp4 + "&temp5=" + temp5 + "&temp6=" + temp6 + "&hum1=" + hum1 + "&hum2=" + hum2 + "&hum3=" + hum3 + "&hum4=" + hum4 + "&hum5=" + hum5 + "&hum6=" + hum6 + "&banFrontLeft=" + banFrontLeft + "&banFrontRight=" + banFrontRight + "&banBackLeft=" + banBackLeft + "&banBackRight=" + banBackRight + "&movementA=" + movementA + "&movementB=" + movementB + "&emergencyButton=" + emergencyButton + "&lat=" + lat + "&lon=" + lon + "&speed=" + speed + "&gpsTime=" + gpsTime + "&volt=" + volt;
  // via http
  smmvs.getNonSecure(_serverNoHttpLocal, _serverChar, httpPort, endpoint, data);
  // via https
  // smmvs.get(data);

  // HTTP POST
  //    smmvs.add("device_name",device_name);
  //    smmvs.add("rn",rn);
  //    smmvs.add("totalDHT",totalDHT);
  //    smmvs.add("temp1",temp1);
  //    smmvs.add("temp2",temp2);
  //    smmvs.add("temp3",temp3);
  //    smmvs.add("temp4",temp4);
  //    smmvs.add("temp5",temp5);
  //    smmvs.add("temp6",temp6);
  //    smmvs.add("hum1",hum1);
  //    smmvs.add("hum2",hum2);
  //    smmvs.add("hum3",hum3);
  //    smmvs.add("hum4",hum4);
  //    smmvs.add("hum5",hum5);
  //    smmvs.add("hum6",hum6);
  //    smmvs.add("banFrontLeft",banFrontLeft);
  //    smmvs.add("banFrontRight",banFrontRight);
  //    smmvs.add("banBackLeft",banBackLeft);
  //    smmvs.add("banBackRight",banBackRight);
  //    smmvs.add("movementA",movementA);
  //    smmvs.add("movementB",movementB);
  //    smmvs.add("emergencyButton",emergencyButton);
  //    smmvs.add("lat",lat);
  //    smmvs.add("lon",lon);
  //    smmvs.add("speed",speed);
  //    smmvs.add("gpsTime",gpsTime);
  //    smmvs.add("volt",volt);
  //  via http
  //    smmvs.sendNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint);
  //  via https
  //    smmvs.send();

  delay(1000);
}
