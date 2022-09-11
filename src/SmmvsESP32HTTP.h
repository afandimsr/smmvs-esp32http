#ifndef SmmvsESP32HTTP_H
#define SmmvsESP32HTTP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

static const char *smmvs_root_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIFXDCCBESgAwIBAgISA7rfL/327oE1CE1QAKTpRatIMA0GCSqGSIb3DQEBCwUA\n"
    "MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD\n"
    "EwJSMzAeFw0yMjA3MjkwNjU0MjlaFw0yMjEwMjcwNjU0MjhaMCYxJDAiBgNVBAMT\n"
    "G3NtbXZzLmFoYS1zbWFydC1wcm9qZWN0LmNvbTCCASIwDQYJKoZIhvcNAQEBBQAD\n"
    "ggEPADCCAQoCggEBAJxY0iKHes2ObHIzT5fKkCtRvjZ8HRV8FUMp3SiigDwMIAwo\n"
    "80SqG4NvelPEQeLXZplUeivpFAbTe1vyLv8wb/H6uSXilhgZYqivQyUfBPbHXqOz\n"
    "iBhxH1SO13aDtnMzoksOiFcY9bI5N859+qFnAywwD/GSy7swB1zocx+uZs5LQxaR\n"
    "EVgdk/86wxTPkzvrmIaU557Tcu6k4bXlsVTaXN0mDa+GDOvU/ecO4HnMk2QKKleG\n"
    "5YADqdi68Sd5abX7eSNrC6+BFpX+m8ArdmSqRmU53IkGmag1CZzv+jpLTc0yYIDi\n"
    "0GyQFYywMkhq3cAU2z9aS+7eU70yfoGrsJdd1jsCAwEAAaOCAnYwggJyMA4GA1Ud\n"
    "DwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0T\n"
    "AQH/BAIwADAdBgNVHQ4EFgQUZUCc979n5sbjplL7slhtlsrkoqYwHwYDVR0jBBgw\n"
    "FoAUFC6zF7dYVsuuUAlA5h+vnYsUwsYwVQYIKwYBBQUHAQEESTBHMCEGCCsGAQUF\n"
    "BzABhhVodHRwOi8vcjMuby5sZW5jci5vcmcwIgYIKwYBBQUHMAKGFmh0dHA6Ly9y\n"
    "My5pLmxlbmNyLm9yZy8wRwYDVR0RBEAwPoIbc21tdnMuYWhhLXNtYXJ0LXByb2pl\n"
    "Y3QuY29tgh93d3cuc21tdnMuYWhhLXNtYXJ0LXByb2plY3QuY29tMEwGA1UdIARF\n"
    "MEMwCAYGZ4EMAQIBMDcGCysGAQQBgt8TAQEBMCgwJgYIKwYBBQUHAgEWGmh0dHA6\n"
    "Ly9jcHMubGV0c2VuY3J5cHQub3JnMIIBAwYKKwYBBAHWeQIEAgSB9ASB8QDvAHYA\n"
    "36Veq2iCTx9sre64X04+WurNohKkal6OOxLAIERcKnMAAAGCSPMgjgAABAMARzBF\n"
    "AiEA9ojw1mjtnPS22UhCOML71I2rshHGwLuL7rnfhHAiNmQCIEs/cB6ursydxjk7\n"
    "iSu6ZsG/hj7wt+Xgx1wVlKZKvMVXAHUAKXm+8J45OSHwVnOfY6V35b5XfZxgCvj5\n"
    "TV0mXCVdx4QAAAGCSPMgggAABAMARjBEAiAFR9PRd5UzHgHWMVsfdNJ8NiJOfrfe\n"
    "AQUlkshGi3VhkAIgRXxf1QpE3OdhYBPwud6/xHLNgm8kKhjNcKLNeHRnRpkwDQYJ\n"
    "KoZIhvcNAQELBQADggEBAGpi74U4koj7IQ7v1/KhyIgugvGDYHY1l+rtd5jgM7b1\n"
    "whMW6XORNdZeDWRRpEr/9Xk78nA4HgZl+WCr1QFQkQOU/Sja4B5r4xcin+gbGuC8\n"
    "Gmus2XiwDTglq53mX4+3htm6BFXFZf6hCKHdky0MpbJg2rsHWgzRuoB2vkgcdLYM\n"
    "CEOY/BUVbVEc1Af6fmxBAIdeLjmvlFPtCD3YAvnW2fYQaxYPPz1x1e9dxrCWZ1zW\n"
    "Yu/TIvSuDJzDAEn8BchvVsjD/AWR2z45qJgsodwxgIzyAMTFv0EpclD8D4/4t6Pc\n"
    "GRPEurUUxs6Koj83t/vWBMLVBv1F0y/f10ApNfyKKOU=\n"
    "-----END CERTIFICATE-----\n";

class SmmvsESP32HTTP
{

public:
  SmmvsESP32HTTP(String accessKey);
  // String createDevice();
  // String retrieveAllDevice(String projectName,int limit=0);
  // String storeData(String nameData[], String valueData[], int sizeParameter);
  /*
    Overloaded functions start
    SMMVS::add()

    These functions are meant to push data into the
    JSON buffer string
  */
  void add(String key, String value);
  void add(String key, int value);
  void add(String key, float value);
  void add(String key, double value);

  // 2-level nested json
  void add(String key, String key2, String value);
  void add(String key, String key2, int value);
  void add(String key, String key2, float value);
  void add(String key, String key2, double value);

  /* Overloaded functions end */
  void send();                                                                                                      // Store data in buffer to database
  void sendRaw(String text);                                                                                        // Store data in buffer to database
  void sendRawNonSecure(String text);                                                                               // Store data in buffer to database
  void sendNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint); // Store data in buffer to database
  void printData();                                                                                                 // Print waiting list data to serial monitor
  String retrieveAllData(int limit = 0);
  String retrieveLatestData();
  void get(String data);
  String getRaw();
  String getRawNonSecure(String server, String lat, String lon);
  void getNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint, String data);
  void getTest();
  void getLatestTest();

  /*
    SMMVS::get() functions

    These functions are meant to fetch data from the
    JSON buffer.
  */
  String getString(String key);
  int getInt(String key);
  float getFloat(String key);
  double getDouble(String key);

  // 2-level nested json
  String getString(String key, String key2);
  int getInt(String key, String key2);
  float getFloat(String key, String key2);
  double getDouble(String key, String key2);

  /* Overloaded functions end */
  bool getSuccess();
  bool wifiConnection(String SSID, String wifiPassword);
  bool checkWifiConnection();
  void setDebug(bool trueFalse);
  void setServer(String domain, String port);

  void measureSize();
  void measureGetSize();

private:
  void printDebug(String text);
  String ipToString(IPAddress ip);
  String _accessKey;
  String _server = "http://smmvs.aha-smart-project.com";
  String _serverNoHttp = "smmvs.aha-smart-project.com";

  const char *_serverChar = "smmvs.aha-smart-project.com";
  String _port = "8000";
  uint16_t _portNum = 8000;

  char *_wifiSSID;
  char *_wifiPass;
  bool _debug = false;
  bool _getSuccess;
  char *tempDebug;
  String jsonString = "{}";
  String jsonGetString;
  String _currentKey;
};

#endif
