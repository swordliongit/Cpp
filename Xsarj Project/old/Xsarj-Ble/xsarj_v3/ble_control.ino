
unsigned long previousMillis_ble_send_timer = 0;
const long interval_ble_send_timer = 1000;

unsigned long ble_send_timer = 0;
String data_for_ble = "";

void ble_Setup() {
  // Create the BLE Device
  BLEDevice::init("XSARJ-4");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_TX,
                        BLECharacteristic::PROPERTY_READ   |
                        BLECharacteristic::PROPERTY_WRITE  |
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_INDICATE
                      );

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_RX,
      BLECharacteristic::PROPERTY_READ   |
      BLECharacteristic::PROPERTY_WRITE  |
      BLECharacteristic::PROPERTY_NOTIFY |
      BLECharacteristic::PROPERTY_INDICATE
                                          );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void ble_Send_To_App() {

  //  if (deviceConnected) {
  //    pTxCharacteristic->setValue(&txValue, 1);
  //    pTxCharacteristic->notify();
  //    txValue++;
  //    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  //  }
  if (deviceConnected) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_ble_send_timer >= interval_ble_send_timer) {
      previousMillis_ble_send_timer = currentMillis;
      ble_send_timer++;
      if (ble_send_timer == 1) {
        if (charge_counter != 0) {
          ble_Send_data("s1-" + String((sum_of_power / 3600)));
        }
        if (charge_counter == 0) {
          ble_Send_data("s1-" + String(0));
        }
      }
      if (ble_send_timer == 2) {
        ble_Send_data("s2-" + String(sensor_2_value));
      }
      if (ble_send_timer == 3) {
        ble_Send_data("s3-" + String(sensor_3_value));
      }
      if (ble_send_timer == 4) {
        ble_Send_data("s4-" + String(charge_cost.toFloat() * -1));
        //        if (charge_counter >= 0) {
        //          if ((sum_of_power / charge_counter) < 7.4) {
        //            ble_Send_data("s4-" + String((charge_counter / 60) * package_price_1));
        //          }
        //          if ((sum_of_power / charge_counter) >= 7.4 && (sum_of_power / charge_counter) < 11) {
        //            ble_Send_data("s4-" + String((charge_counter / 60) * package_price_2));
        //          }
        //          if ((sum_of_power / charge_counter) >= 11) {
        //            ble_Send_data("s4-" + String((charge_counter / 60) * package_price_3));
        //          }
        //        }
        //if (charge_counter <= 0) {
        //  ble_Send_data("s4-0");
        //}
      }
      if (ble_send_timer == 5) {
        ble_Send_data("s5-" + String(partner_id));
      }
      if (ble_send_timer == 6) {
        ble_Send_data("e5-" + error_code_1 + error_code_2 + error_code_3 + error_code_4 + error_code_5 + error_code_6 + error_code_7 + error_code_8 + error_code_9 + error_code_10 + error_code_11 + error_code_12 + error_code_13 + error_code_14 + error_code_15 + error_code_16 + error_code_17);
        ble_send_timer = 0;
      }

      //      if (ble_send_timer == 3) {
      //        ble_Send_data("s3-" + String(sensor_3_value) + "!");
      //      }
      //      if (ble_send_timer == 4) {
      //        ble_Send_data("s4-" + String(sensor_4_value) + "!");
      //      }
      //  if (ble_send_timer == 4) {
      //    ble_Send_data("b1-" + relay_1_cloud_value + "!");
      //    ble_send_timer = 0;
      //    }
      //      if (ble_send_timer == 6) {
      //        ble_Send_data("s6-" + String(sensor_6_value) + "!");
      //      }
      //      if (ble_send_timer == 7) {
      //        ble_Send_data("s7-" + String(sensor_7_value) + "!");
      //      }
      //      if (ble_send_timer == 8) {
      //        ble_Send_data("s8-" + String(sensor_8_value) + "!");
      //      }
      //      if (ble_send_timer == 9) {
      //        ble_Send_data("s9-" + String(sensor_9_value) + "!");
      //      }
      //      if (ble_send_timer == 10) {
      //        ble_Send_data("s10-" + String(sensor_10_value) + "!");
      //      }
      //      if (ble_send_timer == 11) {
      //        ble_Send_data("s11-" + String(sensor_11_value) + "!");
      //      }
      //      if (ble_send_timer == 12) {
      //        ble_Send_data("s12-" + String(sensor_12_value) + "!");
      //      }
      //      if (ble_send_timer == 13) {
      //        ble_Send_data("s13-" + String(sensor_13_value) + "!");
      //      }
      //      if (ble_send_timer == 14) {
      //        ble_Send_data("s14-" + String(sensor_14_value) + "!");
      //        ble_send_timer = 0;
      //      }
    }
  }

  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("---------------start advertising-------------------");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
    Serial.println("-------------------Ble Device Connected--------------------");
    oldDeviceConnected = deviceConnected;
  }
}

void ble_Send_data(String data) {
  char copy[100];
  data.toCharArray(copy, 100);
  //   pCharacteristic->setValue(&txValue, 1); // To send the integer value
  //pCharacteristic->setValue(copy); // Sending a test message
  pTxCharacteristic->setValue(copy);
  pTxCharacteristic->notify(); // Send the value to the app!
  //  Serial.print("*** Sent Value: ");
  //  Serial.print(sensor_data);
  //  Serial.println(" ***");
}
