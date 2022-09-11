# SMMVS ESP32 HTTP  
This is the documentation for SMMVS ESP32 library.  

This library is meant to simplify the process of retrieving and deploying data to SMMVS IoT Platform's REST API using ESP32 with Arduino framework.  

This library has been tested with Arduino ESP32 version 1.0.1.

For dependencies, this library uses [bblanchon's ArduinoJson v5](https://github.com/bblanchon/ArduinoJson) and is already included in the bundle.    

For more information regarding the platform itself, please visit SMMVS' [official website](https://smmvs.aha-smart-project.com/).

## Installation  
**Arduino IDE** <img src="https://camo.githubusercontent.com/647cefc4a331bc5ab2a760d3c731b9d0b3f1259b/68747470733a2f2f7777772e61726475696e6f2e63632f66617669636f6e2e69636f" width="20">  
1. Install ESP32 Core for Arduino. For more information please refer to the ESP32 for Arduino's [installation manual](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)
2. Download the latest release and add this library into Arduino IDE (Sketch > Include Library > Add .ZIP Library...)  

## Examples
Please note that `SMMVSStoreSecure` and `SMMVSGetLatestSecure` are preferred than `SMMVSStoreData` and `SMMVSGetLatestSecure` because they use HTTPS (port 443) rather than HTTP (port 80).  

* **SMMVSGetLatestData** - Fetch the latest data stored in a project device
* **SMMVSGetLatestSecure** - Fetch the latest data stored in a project device through HTTPS  
* **SMMVSStoreData** - Deploy data into a project device
* **SMMVSStoreSecure** - Deploy data into a project device through HTTPS  

## API Reference

> Class `SMMVSESP32HTTP`  

All methods and properties need to be insantiated in order to use them.

### Constructor
* `SMMVSESP32HTTP(String ACCESSKEY)`
The constructor of class `SMMVSESP32HTTP`. Put your SMMVS account access key as the parameter. The access key should be an Arduino `String` datatype.

### Store Data
* `void add(String key, value)` or `void add(String key, String key2, value)`   
Insert a JSON key-value data to the property `jsonString` of class `SMMVSESP32HTTP`. The `value` parameter is overloaded. The supported data types for the value parameter are:
    * `String`
    * `int`
    * `float`
    * `double`  

* `void sendNonSecure()`    
**(Not recommended)** Send the data stored in `jsonString` property of class `SMMVSESP32HTTP` through HTTP port 80 (non-secure).  

* `void send()`  
**(Recommended)** Send the data stored in `jsonString` property of class `SMMVSESP32HTTP` through HTTPS port 443 (secure).  

**Powered by SMMVS Team**
