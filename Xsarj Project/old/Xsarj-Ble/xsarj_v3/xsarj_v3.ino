//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s

//nextion mavi esp 32 nin rx2 portuna
//nextion sarı esp 32 nin tx2 portuna
//sim800L nin tx portu esp32 nin D18 portuna
//sim800L nin rx portu esp32 nin D19 portuna

// http://192.168.43.53/get?message=hey    gönderilecek server mesajı
//
#include "esp_system.h"
#include <Arduino.h>
//#include <WiFi.h>
#include <EEPROM.h>
//#include <IOXhop_FirebaseESP32.h>
//#include "FirebaseESP32.h"
//#include <Nextion.h>
//#include <SoftwareSerial.h>
//#include <ArduinoJson.h>
//#include "TimeLib.h"
//#include <NTPClient.h>
//#include <WiFiUdp.h>
// Define NTP Client to get time
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
//#include <EMailSender.h>
//#include <HTTPClient.h>
// Create an instance
#include <PZEM004Tv30.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
//#include <serial.h>


/* Hardware Serial2 is only available on certain boards. Energy Monitor Serial
   For example the Arduino MEGA 2560
*/
PZEM004Tv30 pzem1(Serial2, 16, 17, 0x07); // Don't forget to arrange spesific address
PZEM004Tv30 pzem2(Serial2, 16, 17, 0x08); // Don't forget to arrange spesific address
PZEM004Tv30 pzem3(Serial2, 16, 17, 0x09); // Don't forget to arrange spesific address



int can_bus_working_value = 0;

const int wdtTimeout = 60000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

//#ifndef D5
//#if defined(ESP8266)
//#define D5 (14)
//#define D6 (12)
//#define D7 (13)
//#define D8 (15)
//#define TX (1)
//#elif defined(ESP32)
//#define D5 (18) // esp32 nin rx pini
//#define D6 (19) // esp32 nin tx pini
//#define D7 (23)
//#define D8 (5)
//#define TX (1)
//#endif
//#endif
//
//#ifdef ESP32
//#define BAUD_RATE 9600
//#else
//#define BAUD_RATE 9600
//#endif

// Reminder: the buffer size optimizations here, in particular the isrBufSize that only accommodates
// a single 8N1 word, are on the basis that any char written to the loopback SoftwareSerial adapter gets read
// before another write is performed. Block writes with a size greater than 1 would usually fail.
//SoftwareSerial swSer;
//SoftwareSerial swSer_1;

//Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

String all_sensor_data = "";
String all_relay_data = "0000000000000000";
String second_esp_serial_data = "";

int ble_status = 0;
int wifi_status = 0;
int connection_status = 0;
int last_connection_status = 0;

int wifi_name_found = 0;

float package_price_1 = 0.55;
float package_price_2 = 0.9;
float package_price_3 = 1.4;

int relay_1 = 14;
int relay_2 = 27;
int relay_3 = 26;
int relay_4 = 12;
int relay_5 = 100;
int relay_6 = 100;
int relay_7 = 100;
int relay_8 = 100;
int relay_9 = 100;
int relay_10 = 100;
int relay_11 = 100;

int start_charge_data_counter = 0;

int plug_in_but_no_charge_counter = 0;

int no_charging_counter = 0;

int sys_reset_value = 0;
int gsm_reset_value = 0;

String data_from_serial = "";

void writeStringToEeprom(char add, String data);
String read_StringFromEeprom(char add);

char uniquename[15]; //Create a Unique AP from MAC address
char uniqueid[15];
String id;

String message_send_getreq;
String message_receive_getreq;
String message_receive_postreq;

const char* host = "esp32";
char ssid[50] = "arduphone";
char password[50] = "arduphone";

//const char* host = "esp32";
//char ssid[50] = "ArtinSystems";
//char password[50] = "ArtinSystemsArtin2021";

int charge_state_from_module = 0;

//const char* host = "esp32";
//char ssid[50] = "Zeyno";
//char password[50] = "arduphone";

String timestamp = "0";

int wifi_connected_counter = 0;

unsigned long previousMillis_wifi_timer = 0;
const long interval_wifi_timer = 30000;

// Set these to run example.
#define FIREBASE_HOST "e-sera-dcbb0.firebaseio.com"
#define FIREBASE_AUTH "nRms9hAPIxI0amv9vzeahlqA8Q3NlFOKjufpEndE"

const char* PARAM_MESSAGE = "message";

int reset_button_esp = 0;
int reset_button_esp_value = 1;

int max_total_time = 0;

int sensor_1 = 100;
int sensor_2 = 100;
int sensor_3 = 100;
int sensor_4 = 36;
int sensor_5 = 39;
int sensor_6 = 34;
int sensor_7 = 35;
int sensor_8 = 32;
int sensor_9 = 33;

double sensor_1_value = 0;
double sensor_2_value = 0;
double sensor_3_value = 0;
int sensor_4_value = 0;
int sensor_5_value = 0;
int sensor_6_value = 0;
int sensor_7_value = 0;
int sensor_8_value = 0;
int sensor_9_value = 0;
int sensor_10_value = 0;
int sensor_11_value = 0;
int sensor_12_value = 0;
int sensor_13_value = 0;
int sensor_14_value = 0;

String relay_1_cloud_value = "0";
String relay_2_cloud_value = "0";
String relay_3_cloud_value = "0";
String relay_4_cloud_value = "0";
String relay_5_cloud_value = "0";
String relay_6_cloud_value = "0";
String relay_7_cloud_value = "0";
String relay_8_cloud_value = "0";
String relay_9_cloud_value = "0";
String relay_10_cloud_value = "0";
String relay_11_cloud_value = "0";
String relay_12_cloud_value = "0";
String relay_13_cloud_value = "0";
String relay_14_cloud_value = "0";
String relay_15_cloud_value = "0";
String relay_16_cloud_value = "0";

int config_1_value = 0;
int config_2_value = 0;
int config_3_value = 0;
int config_4_value = 0;
int config_5_value = 0;
int config_6_value = 0;
int config_7_value = 0;
int config_8_value = 0;
int config_9_value = 0;
int config_10_value = 0;
int config_11_value = 0;
int config_12_value = 0;
int config_13_value = 0;
int config_14_value = 0;
int config_15_value = 0;
int config_16_value = 0;
int config_17_value = 0;
int config_18_value = 0;
int config_19_value = 0;
int config_20_value = 0;
int config_21_value = 0;
int config_22_value = 0;
int config_23_value = 0;
int config_24_value = 0;
int config_25_value = 0;
int config_26_value = 0;
int config_27_value = 0;
int config_28_value = 0;
int config_29_value = 0;
int config_30_value = 0;

String auth_session_id = "";
String partner_total_payment_from_firebase = "0";
String partner_id = "0";
const char * headerKeys[] = {"Set-Cookie", "Date"} ;
const size_t numberOfHeaders = 2;

int config_data_read_value = 0;

int emergency_send_sensor_data_value = 0;
int last_emergency_send_sensor_data_value = 0;

int window_1_operation_time = 100;
int window_2_operation_time = 100;

float wind_speed = 0.0;
int wind_direction = 0;
int rain_status = 0;

int open_window_1 = 0;
int open_window_2 = 0;
int manuel_auto_value = 0; // 0 = manuel

int water_manuel_auto = 1;
int fan_manuel_auto_value = 0;
int humidity_manuel_auto_value = 0;


String temp_config = "";
String temp_values = "";
String water_config = "";
String water_values = "";
String fan_config = "";
String fan_values = "";
String humidity_config = "";
String humidity_values = "";

unsigned long charge_counter = 0;

String error_code_1 = "0";
String error_code_2 = "0";
String error_code_3 = "0";
String error_code_4 = "0";
String error_code_5 = "0";
String error_code_6 = "0";
String error_code_7 = "0";
String error_code_8 = "0";
String error_code_9 = "0";
String error_code_10 = "0";
String error_code_11 = "0";
String error_code_12 = "0";
String error_code_13 = "0";
String error_code_14 = "0";
String error_code_15 = "0";
String error_code_16 = "0";
String error_code_17 = "0";
String error_code_18 = "0";
String error_code_19 = "0";
String error_code_20 = "0";
String error_code_21 = "0";

String relay_1_cloud_value_last = "0";
String relay_2_cloud_value_last = "0";
String relay_3_cloud_value_last = "0";
unsigned long last_payment_id = 0;
float partner_total_payment = 0.0;
float last_invoice_payment = 0.0;
String charge_cost = "0";
double sum_of_power = 0;


BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
String char_data_from_ble = "";
String data_from_ble = "";


// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" // telefon tarafında tx olacak
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" // telefon tarafında rx olacak


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++) {
          //Serial.print(rxValue[i]);
          char_data_from_ble += rxValue[i];
        }

        data_from_ble = char_data_from_ble;

        if (data_from_ble.length() > 0) {
          char_data_from_ble = "";
        }
        //        Serial.print("data_from_mobile");
        //        Serial.print(" ");
        Serial.println(data_from_ble);
        if (data_from_ble.indexOf("r1") >= 0) {
          relay_1_cloud_value = (data_from_ble.substring(data_from_ble.indexOf("r1") + 2 , data_from_ble.indexOf("tp")));
          Serial.print("relay_1_cloud_value: ");
          Serial.println(relay_1_cloud_value);
          if (relay_1_cloud_value == "1") {
            relay_2_cloud_value = "1";
            relay_3_cloud_value = "1";
          }
          if (relay_1_cloud_value == "0") {
            relay_2_cloud_value = "0";
            relay_3_cloud_value = "0";
          }
          no_charging_counter = 0;
          plug_in_but_no_charge_counter = 0;
          error_code_1 = "0";
          error_code_2 = "0";
          error_code_3 = "0";
          error_code_4 = "0";
          error_code_5 = "0";
          error_code_6 = "0";
          error_code_7 = "0";
          error_code_8 = "0";
          error_code_9 = "0";
          error_code_10 = "0";
          error_code_11 = "0";
          error_code_12 = "0";
          error_code_13 = "0";
          error_code_14 = "0";
          error_code_15 = "0";
          error_code_16 = "0";
          error_code_17 = "0";
          charge_counter = 0;
          charge_cost = "0";
          sum_of_power = 0;
          start_charge_data_counter = 0;
        }
        if (data_from_ble.indexOf("tp") >= 0) {
          partner_total_payment = (data_from_ble.substring(data_from_ble.indexOf("tp") + 2 , data_from_ble.indexOf("pz"))).toFloat();
          Serial.print("partner_total_payment: ");
          Serial.println(partner_total_payment);
        }
        if (data_from_ble.indexOf("pi") >= 0) {
          partner_id = (data_from_ble.substring(data_from_ble.indexOf("pi") + 2 , data_from_ble.indexOf("%"))).toFloat();
          Serial.print("partner_id: ");
          Serial.println(partner_id);
        }
        if (data_from_ble.indexOf("!") >= 0) {
          package_price_1 = (data_from_ble.substring(data_from_ble.indexOf("!") + 1 , data_from_ble.indexOf("$"))).toFloat();
          Serial.print("package_price_1: ");
          Serial.println(package_price_1);

        }
        if (data_from_ble.indexOf("$") >= 0) {
          package_price_2 = (data_from_ble.substring(data_from_ble.indexOf("$") + 1 , data_from_ble.indexOf("?"))).toFloat();
          Serial.print("package_price_2: ");
          Serial.println(package_price_2);

        }
        if (data_from_ble.indexOf("?") >= 0) {
          package_price_3 = (data_from_ble.substring(data_from_ble.indexOf("?") + 1 , data_from_ble.indexOf("&"))).toFloat();
          Serial.print("package_price_3: ");
          Serial.println(package_price_3);
        }
        energy_Analyzer_Relay_1();
      }
    }
};

void setup() {
  Serial.begin(115200);
  //Serial1.begin(9600);


  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt

  createSSID();
  Serial.println("Device id = " + id);

  EEPROM.begin(350);
  //testEepromWorking();
  read_Int_Eeprom();

  //myNextion.init();
  //  swSer.begin(BAUD_RATE, SWSERIAL_8N1, D5, D6);
  //  swSer_1.begin(BAUD_RATE, SWSERIAL_8N1, D7, D8);

  Serial.println("\nSoftware serial test started");

  pinMode(reset_button_esp, INPUT_PULLUP);
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
  pinMode(sensor_5, INPUT);
  pinMode(sensor_6, INPUT);
  pinMode(sensor_7, INPUT);

  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);
  pinMode(relay_8, OUTPUT);
  pinMode(relay_9, OUTPUT);
  pinMode(relay_10, OUTPUT);
  pinMode(relay_11, OUTPUT);

  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_3, LOW);
  digitalWrite(relay_4, LOW);
  digitalWrite(relay_5, LOW);
  digitalWrite(relay_6, LOW);
  digitalWrite(relay_7, LOW);
  digitalWrite(relay_8, LOW);
  digitalWrite(relay_9, LOW);
  digitalWrite(relay_10, LOW);
  digitalWrite(relay_11, LOW);

  //arrangeWifiAndPassword();
  Serial.print("ssid: ");
  Serial.print(ssid);
  Serial.print(" password: ");
  Serial.print(password);
  Serial.print(" ");

  //scan_Wifi();
  if (wifi_name_found == 0) {
    ble_Setup();
  }

  if (wifi_name_found == 1) {
    //tryToReconnectWifi_Setup();
    //Serial.print("IP Address: ");
    //Serial.println(WiFi.localIP());

    //    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    //    Firebase.reconnectWiFi(true);
    //
    //    get_Temp_Config_Setup();
    //    get_Temp_Values_Setup();
    //    get_Water_Config_Setup();
    //    get_Water_Values_Setup();
    //    get_Fan_Config_Setup();
    //    get_Fan_Values_Setup();
    //    get_Humidity_Config_Setup();
    //    get_Humidity_Values_Setup();
    //
    //    wifi_Detect_Changes_Relays();
    //
    //    Send_Mail(emailtaker_mail_adress, "Cihaz Yeniden Başlatıldı", "Merhaba, <br>Detaylı Bilgi İçin,<br>Mobil Uygulamanız Üzerinden son güncel veri saatini kontrol ediniz. Teşekkür Ederiz");
    //    http_Post_Take_Session_Id_Setup();

    // Initialize a NTPClient to get time
    //    timeClient.begin();
    //    // Set offset time in seconds to adjust for your timezone, for example:
    //    // GMT +1 = 3600
    //    // GMT +8 = 28800
    //    // GMT -1 = -3600
    //    // GMT 0 = 0
    //    timeClient.setTimeOffset(3600);
    //    wifi_Ntc_Time_Setup();

  }
}

void loop() {
  timerWrite(timer, 0); //reset timer (feed watchdog)

  reset_Wifi_Name();

  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  if (sensor_7_value > 1000 && sensor_7_value < 2500) {
    config_1_value = int(ceil(pow(charge_counter, 0.333)));
    config_2_value = int(ceil(pow(sum_of_power, 0.333)));
    config_3_value = int(ceil(pow(relay_1_cloud_value.toInt(), 0.333)));
    config_4_value = int(ceil(pow(partner_total_payment, 0.333)));
    config_5_value = int(ceil(pow(package_price_1, 0.333)));
    write_Int_ToEeprom();
    delay(20000);
  }

  //change_wifi_Command();
  //  if (ble_status == 0 && WiFi.status() != WL_CONNECTED) {
  //    scan_Wifi_Timer();
  //  }

  //Serial.println("2");

  //reset_Wifi_Name();
  //  serial1_Get_Data();
  //  serial1_Send_Data();
  //Serial.println(can_bus_working_value);

  energy_Analyzer_Relay_1();

  charge_Time_plug_Out_Status();

  finish_Charge_Because_Of_Money();

  check_Money_Finish();

  read_Energy_Serial();
  read_Sensors();

  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  if (sensor_7_value > 1000 && sensor_7_value < 2500) {
    config_1_value = int(ceil(pow(charge_counter, 0.333)));
    config_2_value = int(ceil(pow(sum_of_power, 0.333)));
    config_3_value = int(ceil(pow(relay_1_cloud_value.toInt(), 0.333)));
    config_4_value = int(ceil(pow(partner_total_payment, 0.333)));
    config_5_value = int(ceil(pow(package_price_1, 0.333)));
    write_Int_ToEeprom();
    delay(20000);
  }

  //  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  //  if (sensor_7_value > 1000 && sensor_7_value < 2500) {
  //    change_wifi_Command();
  //    second_esp_serial_data = "sop:" + String(sum_of_power) + "cc:" + String(charge_counter) + "r1:" + relay_1_cloud_value + "ptp:" + String(partner_total_payment) + "pp" + package_price_1 + "!";
  //    delay(20000);
  //  }

  //esp_To_Esp_Communication();
  //swSer1_Send_Data();
  //  if (WiFi.status() != WL_CONNECTED && ble_status == 0) {
  //    gsm_Timer();
  //    gsm_Send_Httppost_1(String(FIREBASE_HOST) + "/" + id + "/" + "sensors.json");
  //    gsm_Send_Httpget_1(String(FIREBASE_HOST) + "/" + id + "/" + "relays.json");
  //    gsm_Health_Control();
  //  }
  //  read_Gsm_Serial();
  //  write_Gsm_Serial();
  //wifi_Ntc_Time();
  //nextion_Control();
  //wifi_Get_Data_From_Cloud();
  //wifi_Change_Sensors_Atcloud();
  //wifi_Append_Sensors_to_Cloud_Once();
  //wifi_Append_Sensors_to_Cloud_When_Charge();
  //wifi_Append_Sensors_to_Cloud_When_Not_Charge();

  //http_Post_Take_Session_Id();

  //arrange_Window_Limits();
  //control_Window_Motors_According_Temp();

  //water_Periodic_Time();

  //control_Fan_Motors_According_Temp();

  //control_Humidity_Motors_According_Hum();

  //device_Connection_Status_Check();

  //wifi_Append_Sensors_to_Cloud_Emergency();

  if (wifi_name_found == 0) {
    ble_Send_To_App();
  }

  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  if (sensor_7_value > 1000 && sensor_7_value < 2500) {
    config_1_value = int(ceil(pow(charge_counter, 0.333)));
    config_2_value = int(ceil(pow(sum_of_power, 0.333)));
    config_3_value = int(ceil(pow(relay_1_cloud_value.toInt(), 0.333)));
    config_4_value = int(ceil(pow(partner_total_payment, 0.333)));
    config_5_value = int(ceil(pow(package_price_1, 0.333)));
    write_Int_ToEeprom();
    delay(20000);
  }

  //return_Of_Charge_Module();

  charge_State();

  if (charge_state_from_module == 1) {
    control_Relays();
  }
}
