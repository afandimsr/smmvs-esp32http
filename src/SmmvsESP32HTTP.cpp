#include "SmmvsESP32HTTP.h"

SmmvsESP32HTTP::SmmvsESP32HTTP(String accessKey)
{
    _accessKey = accessKey;
}

void SmmvsESP32HTTP::getNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint, String data)
{

    jsonGetString = "";
    _getSuccess = false;
    printDebug("[SMMVS] Connecting to " + _serverNoHttpLocal + "\n");

    // const char* _serverCharLocal = "http://127.0.0.1";
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    // const int httpPort = 8007;
    if (!client.connect(_serverCharLocal, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = endpoint;
    String queryParams = data;
    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + queryParams + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttpLocal + "\r\n" +
                 "Authorization: Bearer " + _accessKey + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return;
        }
    }
    String line = "";
    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if (line.indexOf("HTTP/1.1 201 Created") >= 0)
    {
        printDebug("[SMMVS] Created! Response: 201\n\n");
        printDebug("[SMMVS] Header Response Start\n");
        printDebug(line + "\n");
        printDebug("[SMMVS] Header Response End\n\n");
    }
    else if (line.indexOf("HTTP/1.1 502 Bad Gateway") >= 0)
    {
        printDebug("[SMMVS] Bad Gateway! Response: 502\n");
        printDebug("[SMMVS] Note: please check your vehicle status in smmvs web\n\n");
    }
    else if (line.indexOf("HTTP/1.1 401 Unauthorized") >= 0)
    {
        printDebug("[SMMVS] Unauthorized! Response: 401\n");
        printDebug("[SMMVS] Note: please check your api key\n\n");
    }
    else if (line.indexOf("HTTP/1.1 500 Internal Server Error") >= 0)
    {
        printDebug("[SMMVS] Server Error! Response: 500\n");
        printDebug("[SMMVS] Note: make sure the vehicle name and rn field are correct\n");
        printDebug("[SMMVS] or contact your smmvs administrator server\n\n");
    }
    else
    {
        printDebug("[SMMVS] Creating data failed!\n");
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    _getSuccess = true;
}

void SmmvsESP32HTTP::get(String data)
{

    jsonGetString = "";
    _getSuccess = false;
    printDebug("[SMMVS] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(smmvs_root_ca);
    client.setInsecure();

    const int httpPort = 443;
    if (!client.connect(_serverChar, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/api/data";
    String queryParams = data;

    printDebug("Requesting URL: " + url + queryParams + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + queryParams + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttp + "\r\n" +
                 "Authorization: Bearer " + _accessKey + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";
    while (client.available())
    {

        line += client.readStringUntil('\r');
    }
    // Check if response is successful
    if (line.indexOf("HTTP/1.1 201 Created") >= 0)
    {
        printDebug("[SMMVS] Created! Response: 201\n\n");
        printDebug("[SMMVS] Header Response Start\n");
        printDebug(line + "\n");
        printDebug("[SMMVS] Header Response End\n\n");
    }
    else if (line.indexOf("HTTP/1.1 502 Bad Gateway") >= 0)
    {
        printDebug("[SMMVS] Bad Gateway! Response: 502\n");
        printDebug("[SMMVS] Note: please check your vehicle status in smmvs web\n\n");
    }
    else if (line.indexOf("HTTP/1.1 401 Unauthorized") >= 0)
    {
        printDebug("[SMMVS] Unauthorized! Response: 401\n");
        printDebug("[SMMVS] Note: please check your api key\n\n");
    }
    else if (line.indexOf("HTTP/1.1 500 Internal Server Error") >= 0)
    {
        printDebug("[SMMVS] Server Error! Response: 500\n");
        printDebug("[SMMVS] Note: make sure the vehicle name and rn field are correct\n");
        printDebug("[SMMVS] or contact your smmvs administrator server\n\n");
    }
    else
    {
        printDebug("[SMMVS] Creating data failed!\n");
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    _getSuccess = true;
}

String SmmvsESP32HTTP::getRaw()
{

    jsonGetString = "";
    _getSuccess = false;
    printDebug("[SMMVS] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(smmvs_root_ca);

    const int httpPort = 443;
    if (!client.connect(_serverChar, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return "Conn failed";
    }

    // We now create a URI for the request
    String url = "/api/data";

    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + _serverNoHttp + "\r\n" +
                 "Content-Type: application/json;ty=4\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return "Timeout";
        }
    }

    String payload = "";
    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
        while (client.read() != '{')
            ;
        String line = "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject &object = jsonBuffer.parseObject(line);
        String receivedData = object["m2m:cin"]["con"];
        payload = receivedData;
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    _getSuccess = true;
    return payload;
}

String SmmvsESP32HTTP::getRawNonSecure(String server, String lat, String lon)
{
    jsonGetString = "";
    _getSuccess = false;
    printDebug("[SMMVS] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    const int httpPort = 8000;
    if (!client.connect(_serverChar, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return "Conn failed";
    }

    // We now create a URI for the request
    String url = "/api/data?lat=" + lat + "&lon=" + lon;

    printDebug("Requesting URL: " + url + "\n");

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Accept: application/json\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return "Timeout";
        }
    }

    String payload = "";
    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
        while (client.read() != '{')
            ;
        String line = "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject &object = jsonBuffer.parseObject(line);
        String receivedData = object["lot"];
        payload = receivedData;
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    _getSuccess = true;
    return payload;
}

bool SmmvsESP32HTTP::getSuccess()
{
    return _getSuccess;
}

void SmmvsESP32HTTP::sendNonSecure(String _serverNoHttpLocal, const char *_serverCharLocal, const int httpPort, String endpoint)
{
    printDebug("[SMMVS] Connecting to " + _serverNoHttpLocal + "\n");

    // const char* _serverCharLocal = "http://192.168.209.70";
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    // const int httpPort = 8007;
    if (!client.connect(_serverCharLocal, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    // String url = "/api/data";
    String url = endpoint;

    jsonString.replace("", "\\\"");

    String body;
    // body += "{";
    // body += "\"m2m:cin\": {";
    body += "" + jsonString + "";
    // body += "}";
    // body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttpLocal + "\r\n";
    req += "Authorization: Bearer " + _accessKey + "\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json\r\n";
    req += "Content-Length:" + String(body.length()) + "\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if (_debug)
    {
        Serial.println(req);
    }

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while (client.available())
    {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if (line.indexOf("HTTP/1.1 201 Created") >= 0)
    {
        printDebug("[SMMVS] Created! Response: 201\n\n");
        printDebug("[SMMVS] Header Response Start\n");
        printDebug(line + "\n");
        printDebug("[SMMVS] Header Response End\n\n");
    }
    else if (line.indexOf("HTTP/1.1 502 Bad Gateway") >= 0)
    {
        printDebug("[SMMVS] Bad Gateway! Response: 502\n");
        printDebug("[SMMVS] Note: please check your vehicle status in smmvs web\n\n");
    }
    else if (line.indexOf("HTTP/1.1 401 Unauthorized") >= 0)
    {
        printDebug("[SMMVS] Unauthorized! Response: 401\n");
        printDebug("[SMMVS] Note: please check your api key\n\n");
    }
    else if (line.indexOf("HTTP/1.1 500 Internal Server Error") >= 0)
    {
        printDebug("[SMMVS] Server Error! Response: 500\n");
        printDebug("[SMMVS] Note: make sure the vehicle name and rn field are correct\n");
        printDebug("[SMMVS] or contact your smmvs administrator server\n\n");
    }
    else
    {
        printDebug("[SMMVS] Creating data failed!\n");
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void SmmvsESP32HTTP::send()
{
    printDebug("[SMMVS] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(smmvs_root_ca);
    client.setInsecure();

    const int httpPort = 443;
    if (!client.connect(_serverChar, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/api/data";

    jsonString.replace("", "\\\"");

    String body;
    // body += "{";
    // body += "\"m2m:cin\": {";
    // body += "\"data\": \"" + jsonString + "\"";
    body += "" + jsonString + "";
    // body += "}";
    // body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "Authorization: Bearer " + _accessKey + "\r\n";
    req += "Accept: application/json\r\n";
    // req += "Connection: close\r\n";
    req += "Content-Type: application/json\r\n";
    req += "Content-Length:" + String(body.length()) + "\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if (_debug)
    {
        Serial.println(req);
    }

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while (client.available())
    {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if (line.indexOf("HTTP/1.1 201 Created") >= 0)
    {
        printDebug("[SMMVS] Created! Response: 201\n\n");
        printDebug("[SMMVS] Header Response Start\n");
        printDebug(line + "\n");
        printDebug("[SMMVS] Header Response End\n\n");
    }
    else if (line.indexOf("HTTP/1.1 502 Bad Gateway") >= 0)
    {
        printDebug("[SMMVS] Bad Gateway! Response: 502\n");
        printDebug("[SMMVS] Note: please check your vehicle status in smmvs web\n\n");
    }
    else if (line.indexOf("HTTP/1.1 401 Unauthorized") >= 0)
    {
        printDebug("[SMMVS] Unauthorized! Response: 401\n");
        printDebug("[SMMVS] Note: please check your api key\n\n");
    }
    else if (line.indexOf("HTTP/1.1 500 Internal Server Error") >= 0)
    {
        printDebug("[SMMVS] Server Error! Response: 500\n");
        printDebug("[SMMVS] Note: make sure the vehicle name and rn field are correct\n");
        printDebug("[SMMVS] or contact your smmvs administrator server\n\n");
    }
    else
    {
        printDebug("[SMMVS] Creating data failed!\n");
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void SmmvsESP32HTTP::sendRaw(String text)
{
    printDebug("[SMMVS] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;

    client.setCACert(smmvs_root_ca);

    const int httpPort = 443;
    if (!client.connect(_serverChar, httpPort))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/api/data";

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + text + "\"";
    body += "}";
    body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json;ty=4\r\n";
    req += "Content-Length:" + String(body.length()) + "\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if (_debug)
    {
        Serial.println(req);
    }

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while (client.available())
    {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if (line.indexOf("HTTP/1.1 201 Created") >= 0)
    {
        printDebug("[SMMVS] Created! Response: 201\n");
    }
    else
    {
        printDebug("[SMMVS] Creating data failed!\n");
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void SmmvsESP32HTTP::sendRawNonSecure(String text)
{
    printDebug("[SMMVS] Connecting to " + _serverNoHttp + "\n");

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    const int httpPort = 443;
    if (!client.connect(_serverChar, _portNum))
    {
        printDebug("[SMMVS] Connection failed!\n");
        return;
    }

    // We now create a URI for the request
    String url = "/api/data";

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + text + "\"";
    body += "}";
    body += "}";

    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(body);

    printDebug("Requesting URL: " + url + "\n");

    String req = "";
    req += "POST " + url + " HTTP/1.1\r\n";
    req += "Host: " + _serverNoHttp + "\r\n";
    req += "Accept: application/json\r\n";
    req += "Connection: close\r\n";
    req += "Content-Type: application/json;ty=4\r\n";
    req += "Content-Length:" + String(body.length()) + "\r\n";
    req += "\r\n";
    req += body + "\r\n";

    // This will send the request to the server
    client.print(req);
    if (_debug)
    {
        Serial.println(req);
    }

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            Serial.println("[SMMVS] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "";

    while (client.available())
    {
        line += client.readStringUntil('\r');
    }

    // Check if response is successful
    if (line.indexOf("HTTP/1.1 201 Created") >= 0)
    {
        printDebug("[SMMVS] Created! Response: 201\n");
    }
    else
    {
        printDebug("[SMMVS] Creating data failed!\n");
    }

    printDebug("\n[SMMVS] Closing connection...\n");
    jsonString = "{}";
    _currentKey = "";
}

void SmmvsESP32HTTP::add(String key, String value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
}

void SmmvsESP32HTTP::add(String key, String key2, String value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    if (_currentKey != key)
    {
        JsonObject &nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else
    {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
    _currentKey = key;
}

void SmmvsESP32HTTP::add(String key, int value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
}

void SmmvsESP32HTTP::add(String key, String key2, int value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    if (_currentKey != key)
    {
        JsonObject &nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else
    {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
    _currentKey = key;
}

void SmmvsESP32HTTP::add(String key, float value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
}

void SmmvsESP32HTTP::add(String key, String key2, float value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    if (_currentKey != key)
    {
        JsonObject &nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else
    {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
    _currentKey = key;
}

void SmmvsESP32HTTP::add(String key, double value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
}

void SmmvsESP32HTTP::add(String key, String key2, double value)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonString);
    if (_currentKey != key)
    {
        JsonObject &nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else
    {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString = newInsert;
    _currentKey = key;
}

String SmmvsESP32HTTP::getString(String key)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key];
    return value;
}

String SmmvsESP32HTTP::getString(String key, String key2)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key][key2];
    return value;
}

int SmmvsESP32HTTP::getInt(String key)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key];
    return value;
}

int SmmvsESP32HTTP::getInt(String key, String key2)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key][key2];
    return value;
}

float SmmvsESP32HTTP::getFloat(String key)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key];
    return value;
}

float SmmvsESP32HTTP::getFloat(String key, String key2)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key][key2];
    return value;
}

double SmmvsESP32HTTP::getDouble(String key)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key];
    return value;
}

double SmmvsESP32HTTP::getDouble(String key, String key2)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key][key2];
    return value;
}

void SmmvsESP32HTTP::printData()
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &sendObject = jsonBuffer.parseObject(jsonString);
    JsonObject &getObject = jsonBuffer.parseObject(jsonGetString);
    printDebug("\n\n[SMMVS] Data to send: \n\n");
    sendObject.prettyPrintTo(Serial);
    printDebug("\n\n[SMMVS] Data available to get: \n\n");
    getObject.prettyPrintTo(Serial);
}

void SmmvsESP32HTTP::printDebug(String text)
{
    if (_debug)
        Serial.print(text);
}

void SmmvsESP32HTTP::setDebug(bool trueFalse)
{
    _debug = trueFalse;
}

String SmmvsESP32HTTP::ipToString(IPAddress ip)
{
    String s = "";
    for (int i = 0; i < 4; i++)
        s += i ? "." + String(ip[i]) : String(ip[i]);
    return s;
}

bool SmmvsESP32HTTP::wifiConnection(String SSID, String wifiPassword)
{
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(SSID)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count = 0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[SMMVS] Trying to connect to " + SSID + "...\n");

    // for (count=0;count<20;count++) {
    //     delay(500);
    //     printDebug(".");
    // }

    int counter = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        printDebug(".");
        counter++;
        if (counter >= 10)
        {
            counter = 0;
            printDebug("[SMMVS] Could not connect to " + SSID + "! Retrying...\n");
        }
    }

    WiFi.setAutoReconnect(true);
    printDebug("\n[SMMVS] WiFi Connected!\n");
    printDebug("[SMMVS] IP Address: " + ipToString(WiFi.localIP()) + "\n");
    return true;
}

bool SmmvsESP32HTTP::checkWifiConnection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        printDebug("[SMMVS] WIFI RECONNECT...");
        return wifiConnection(_wifiSSID, _wifiPass);
    }
}
