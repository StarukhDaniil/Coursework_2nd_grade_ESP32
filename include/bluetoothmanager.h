#pragma once

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID           "0000180A-0000-1000-8000-00805f9b34fb"
#define CHARACTERISTIC_UUID    "00002A58-0000-1000-8000-00805f9b34fb"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
};

class MyCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onIndicate(BLECharacteristic *pCharacteristic);
};

void setupBLE();
