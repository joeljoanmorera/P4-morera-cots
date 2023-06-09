#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define bleServerName "ES32-Server"
#define Service_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define Characteristic_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

bool deviceConnected = false;

// Humidity Characteristic and Descriptor
BLECharacteristic pCharacteristics(Characteristic_UUID, 
                                    BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor pDescriptor(BLEUUID((uint16_t)0x2902));

//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks: public BLEServerCallbacks 
{
  void onConnect(BLEServer* pServer)
  {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer)
  {
    deviceConnected = false;
  }
};

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  //Inizalization of BLE Device
  BLEDevice::init(bleServerName);

  //Create BLE server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  //Create the BLE service
  BLEService *pService = pServer->createService(Service_UUID);

  //Create the BLE Characteristic and BLE Descriptor
  pService->addCharacteristic(&pCharacteristics);
  pDescriptor.setValue("TEXT:");
  pCharacteristics.addDescriptor(&pDescriptor);
  
  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(Service_UUID);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x12);
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  // BLECharacteristic *pCharacteristic = pService->createCharacteristic(
  //                                        CHARACTERISTIC_UUID,
  //                                        BLECharacteristic::PROPERTY_NOTIFY
  //                                      );

  // pCharacteristic->setValue("Hola Mundo via BLE");
  // pService->start();
  // // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  // pAdvertising->addServiceUUID(SERVICE_UUID);
  // pAdvertising->setScanResponse(true);
  // pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  // pAdvertising->setMinPreferred(0x12);
  // BLEDevice::startAdvertising();
  // Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() 
{
  if (deviceConnected)
  {
    float value = 3.1415;
    static char valueTemp [6];
    dtostrf(value, 6, 2, valueTemp);
    pCharacteristics.setValue(valueTemp);
    pCharacteristics.notify();
    Serial.print("Enviamos el numero PI:");
    Serial.println(valueTemp);
    delay(5000);
  }
}