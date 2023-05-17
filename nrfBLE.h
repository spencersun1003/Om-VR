#ifndef nrfBLE_h
#define nrfBLE_h
#include <bluefruit.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

// BLE Service
BLEDfu  bledfu;  // OTA DFU service
BLEDis  bledis;  // device information
BLEUart bleuart; // uart over ble
BLEBas  blebas;  // battery


class nrfBLE
{
  public:
    nrfBLE();
    //void loop();
    void send_data(String data);
    String receive_data();
    void startAdv(void);
    static void connect_callback(uint16_t conn_handle);
    static void disconnect_callback(uint16_t conn_handle, uint8_t reason);
};

#endif