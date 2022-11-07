#ifndef SmmvsESP32HTTP_H
#define SmmvsESP32HTTP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

static const char *smmvs_root_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIFVTCCBD2gAwIBAgISBNRKbUEvfE1RhROph3lB/zfAMA0GCSqGSIb3DQEBCwUA\n"
    "MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD\n"
    "EwJSMzAeFw0yMjExMDgwMjQyNDJaFw0yMzAyMDYwMjQyNDFaMBsxGTAXBgNVBAMT\n"
    "EGlvdC10ZWxlcGF0aS5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB\n"
    "AQC68XrF+u4xVAv/+l2vuvICGBdOJY98elmALLdRLmbJv4HyC2hWbXw0geNGbFGG\n"
    "wZsQNqU+wnXa5EYaqLhr6rH2gxrpR/Z6ZzcVNgtyBVYLFP418plF9tdTdLIdAiAT\n"
    "mC8CA+eL3SJbemWu7WkiCB633MMaDT/Bbf1B5Vloe8g/jXHVfWU+y5YTrDpQyIoW\n"
    "Rp9SK1AcBFtE+bubWpSKPJgw2LI8hD0Vyz7OMM1c+w2xt7QGTvDnfF5uxnx2976A\n"
    "wN+I5brHlCiv5ngY9fwWy+hsFqJBP7DhNitydgLdzFfMcFaIkseJuiBmm+Olhhbm\n"
    "K4F9Zti63E2NAdB0o/zTvI6TAgMBAAGjggJ6MIICdjAOBgNVHQ8BAf8EBAMCBaAw\n"
    "HQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMAwGA1UdEwEB/wQCMAAwHQYD\n"
    "VR0OBBYEFIsHUBFBU9gImzrYlwL9bgwNRmf2MB8GA1UdIwQYMBaAFBQusxe3WFbL\n"
    "rlAJQOYfr52LFMLGMFUGCCsGAQUFBwEBBEkwRzAhBggrBgEFBQcwAYYVaHR0cDov\n"
    "L3IzLm8ubGVuY3Iub3JnMCIGCCsGAQUFBzAChhZodHRwOi8vcjMuaS5sZW5jci5v\n"
    "cmcvMEgGA1UdEQRBMD+CEGlvdC10ZWxlcGF0aS5jb22CFW1haWwuaW90LXRlbGVw\n"
    "YXRpLmNvbYIUd3d3LmlvdC10ZWxlcGF0aS5jb20wTAYDVR0gBEUwQzAIBgZngQwB\n"
    "AgEwNwYLKwYBBAGC3xMBAQEwKDAmBggrBgEFBQcCARYaaHR0cDovL2Nwcy5sZXRz\n"
    "ZW5jcnlwdC5vcmcwggEGBgorBgEEAdZ5AgQCBIH3BIH0APIAdwB6MoxU2LcttiDq\n"
    "OOBSHumEFnAyE4VNO9IrwTpXo1LrUgAAAYRVVUYzAAAEAwBIMEYCIQCeWBi2l/B6\n"
    "1gcCdg1PwjNgXA9yFzIX5kESavl5D2Dt3QIhAP3r5BdEyfgjcu7m8OobhPO6Gxk1\n"
    "tO5fbwRmCnwdrA+yAHcArfe++nz/EMiLnT2cHj4YarRnKV3PsQwkyoWGNOvcgooA\n"
    "AAGEVVVGPQAABAMASDBGAiEA1MDNgTt4m+gOOOYJvrOBDkJk/wcJyy5Q9xYWAFwU\n"
    "5WoCIQCWt1a2UOaQC0F7YHpZ9wqw2kV43U2ILaADhu3IRilQ0jANBgkqhkiG9w0B\n"
    "AQsFAAOCAQEAaH8w0A+x4U3AmzRDeKUyi8qioJcW9TD1BA4ulxeCH9/0KMbQ0lwQ\n"
    "LexV3VtlluaMtkIYCncLuxIXmorK2wAqTfIThZVC7BPW/DUhAFA2MVuaHoBJyv9O\n"
    "s/YnzOSNL3EVRbaq6wENv97R/JxRCnV14wPlcohntD8di1RUhp5b1ST4ycR/rvsj\n"
    "uw1klfqrbLz3RQ++nvbpQklixIeMI5OaK9ZilsaST2QnDCP7qK0ipSMISucfJ4CB\n"
    "HPTVSYWrv4BK6GJVUVDeo8jj1t0FM0RBsfR/E8nBAa2g5EqxMuzRf5LF+uy1dEH4\n"
    "9C0da2RXRYjragTHKaRBK2ETQENjjHNNCQ==\n"
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
  String _server = "http://iot-telepati.com";
  String _serverNoHttp = "iot-telepati.com";

  const char *_serverChar = "iot-telepati.com";
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
