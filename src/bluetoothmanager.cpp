#include "bluetoothmanager.h"
#include "main_instances.h"

extern MyServerCallbacks g_serverCallbacks;
extern MyCharacteristicCallbacks g_charCallbacks;

void MyServerCallbacks::onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Client connected.");
};

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Client disconnected.");
    BLEDevice::startAdvertising();
}

void MyCharacteristicCallbacks::onIndicate(BLECharacteristic *pCharacteristic) {
    Serial.println("Indication successful (ACK received).");
}

void setupBLE() {
    Serial.println("Starting BLE Server...");

    BLEDevice::init("ESP32_Graph");

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(&g_serverCallbacks);

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_INDICATE |
        BLECharacteristic::PROPERTY_READ
    );

    pCharacteristic->setCallbacks(&g_charCallbacks);

    BLE2902 *p2902 = new BLE2902();
    p2902->setNotifications(false);
    p2902->setIndications(true);

    pCharacteristic->addDescriptor(p2902);

    pService->start();

    delay(1000);

    BLEDevice::startAdvertising();
    Serial.println("Characteristic set up. ESP32 ready to connect.");
}