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
#include <WiFi.h>
#include <EEPROM.h>
//#include <IOXhop_FirebaseESP32.h>
//#include "FirebaseESP32.h"
//#include <Nextion.h>
#include <SoftwareSerial.h>
//#include <ArduinoJson.h>
#include "TimeLib.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
#include <EMailSender.h>
#include <HTTPClient.h>
// Create an instance
//#include <PZEM004Tv30.h>
//#include <BLEDevice.h>
//#include <BLEServer.h>
//#include <BLEUtils.h>
//#include <BLE2902.h>
#include "DHT.h"
#include <Update.h>
#include <analogWrite.h>
#include <PZEM004Tv30.h>

//---------------------- SYSTEM VARIABLES START ------------------------

TaskHandle_t Task1;

String server_url = "https://panel.xsarj.com";
String server_username = "device@xsarj.com";
String server_password = "Xsarj.artin.2022";
String server_db_name = "xsarj";

// location of firmware file on external web server
// change to your actual .bin location
#define HOST_OF_OTA "http://panel.xsarj.com:8081/web/content/2330?download=true"
HTTPClient client;
// Global variables
int totalLength;       //total size of firmware
int currentLength = 0; //current size of written firmware
int version = 0;
int camera_version = 0;
int http_get_version = 9999;

int wifi_request_counter = 0;
int last_wifi_request_counter = 0;

int device_http_counter = 0;
int last_device_http_counter = 0;

String device_status = "passive";
String device_status_1 = "passive";
String device_status_2 = "passive";
String device_status_3 = "passive";
String device_status_4 = "passive";
String device_status_5 = "passive";
String device_status_6 = "passive";
String device_status_7 = "passive";
String device_status_8 = "passive";
String device_status_9 = "passive";
String device_status_10 = "passive";
String device_status_11 = "passive";
String device_status_12 = "passive";
String device_status_13 = "passive";
String device_status_14 = "passive";
String device_status_15 = "passive";
String device_status_16 = "passive";
float entrance_delay_time = 0;
float exit_delay_time = 0;
float alarm_time = 0;
int setting_1_value = 0;
int setting_2_value = 0;
int setting_3_value = 0;
int setting_4_value = 0;
int setting_5_value = 0;
int setting_6_value = 0;
int setting_7_value = 0;
int setting_8_value = 0;
int setting_9_value = 0;
int setting_10_value = 0;

//int internal_temp_of_room = 0;
//int internal_hum_of_room = 0;
//int alarm_time = 0;

bool create_report = true;
int device_update = 0;

bool default_settings_1 = true;
bool zone_status_1 = false;
bool always_on_1 = false;
bool sudden_alarm_1 = false;

bool default_settings_2 = true;
bool zone_status_2 = false;
bool always_on_2 = false;
bool sudden_alarm_2 = false;

bool default_settings_3 = true;
bool zone_status_3 = false;
bool always_on_3 = false;
bool sudden_alarm_3 = false;

bool default_settings_4 = true;
bool zone_status_4 = false;
bool always_on_4 = false;
bool sudden_alarm_4 = false;

int wifi_strength = 0;
float test_signal_time = 0;

int zone_1_sensor_status = 0;
int zone_2_sensor_status = 0;
int zone_3_sensor_status = 0;
int zone_4_sensor_status = 0;

String ademco_id = "I234";
String gsm_ademco_id = "E602-000&gsm";
String last_gsm_ademco_id = "G234";

int ademco_id_sended_value = 1;



/* Hardware Serial2 is only available on certain boards. Energy Monitor Serial
   For example the Arduino MEGA 2560
*/
//#if defined(ESP32)
//PZEM004Tv30 pzem(Serial2, 16, 17);
//#else
//PZEM004Tv30 pzem(Serial2);
//#endif

const char* emailsender_mail_adress = "*****";
const char* emailsender_mail_password = "*****";
char* emailtaker_mail_adress = "*****";

int can_bus_working_value = 0;

tmElements_t te;  //Time elements structure
time_t unixTime; // a time stamp
String date_time_now = "2021-10-19 07:36:50";

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
#define D5 (18) // esp32 nin rx pini
#define D6 (19) // esp32 nin tx pini
#define D7 (23)
#define D8 (5)
#define TX (1)
//#endif
//#endif
//
//#ifdef ESP32
#define BAUD_RATE 9600
//#else
//#define BAUD_RATE 9600
//#endif

// Reminder: the buffer size optimizations here, in particular the isrBufSize that only accommodates
// a single 8N1 word, are on the basis that any char written to the loopback SoftwareSerial adapter gets read
// before another write is performed. Block writes with a size greater than 1 would usually fail.
SoftwareSerial swSer;
SoftwareSerial swSer_1;

//Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

String all_sensor_data = "";
String all_relay_data = "0000000000000000";
String second_esp_serial_data = "";
String all_sensor_values = "";

int ble_status = 0;
int wifi_status = 0;
int connection_status = 0;
int last_connection_status = 0;

int wifi_name_found = 0;

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

int buzzer = 100;

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

String wifiname = "";
String wifipassword = "";

String wifi_name = "arduphone";
String wifi_password = "arduphone";

String timestamp = "0";

int wifi_connected_counter = 0;

unsigned long previousMillis_wifi_timer = 0;
const long interval_wifi_timer = 30000;

// Set these to run example.
//#define FIREBASE_HOST "e-sera-dcbb0.firebaseio.com"
//#define FIREBASE_AUTH "nRms9hAPIxI0amv9vzeahlqA8Q3NlFOKjufpEndE"

const char* PARAM_MESSAGE = "message";

int reset_button_esp = 0;
int reset_button_esp_value = 1;

//Define Firebase Data objects
//FirebaseData firebaseData1;
//FirebaseData firebaseData2;
//FirebaseData firebaseData3;
//FirebaseData firebaseData4;
String path = "/devices";

int sensor_1 = 100;
int sensor_2 = 100;
int sensor_3 = 100;
int sensor_4 = 36;
int sensor_5 = 39;
int sensor_6 = 34;
int sensor_7 = 35;
int sensor_8 = 32;
int sensor_9 = 33;
int sensor_10 = 100;
int sensor_11 = 100;

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

int led_1 = 100;
int led_2 = 100;

String auth_session_id = "";
String partner_total_payment_from_firebase = "0";
String partner_id = "0";
const char * headerKeys[] = {"Set-Cookie", "Date"} ;
const size_t numberOfHeaders = 2;

int config_data_read_value = 0;

int emergency_send_sensor_data_value = 0;
int last_emergency_send_sensor_data_value = 0;

//---------------------- SYSTEM VARIABLES END ------------------------

//---------------------- XSARJ VARIABLES START -----------------------
/* Hardware Serial2 is only available on certain boards. Energy Monitor Serial
   For example the Arduino MEGA 2560
*/
PZEM004Tv30 pzem1(Serial2, 16, 17, 0x07); // Don't forget to arrange spesific address
PZEM004Tv30 pzem2(Serial2, 16, 17, 0x08); // Don't forget to arrange spesific address
PZEM004Tv30 pzem3(Serial2, 16, 17, 0x09); // Don't forget to arrange spesific address
float package_price_1 = 0.55;
float package_price_2 = 0.9;
float package_price_3 = 1.4;
int start_charge_data_counter = 0;
int plug_in_but_no_charge_counter = 0;
unsigned long no_charging_counter = 0;
unsigned long idle_no_charging_counter = 0;
int charge_state_from_module = 0;

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
unsigned long charge_counter = 0;

int restart_device_value = 0;

//------------------  XSARJ VARIABLES END -----------------------

void setup() {

  Serial.begin(115200);
  //Serial2.begin(115200);

  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt

  createSSID();
  path = id;
  Serial.println("Device id = " + id);

  EEPROM.begin(400);
  //testEepromWorking();
  read_Int_Eeprom();
  Serial.println("Eeprom Values Read Succesfully!");

  //myNextion.init();
  swSer.begin(BAUD_RATE, SWSERIAL_8N1, D5, D6);
  swSer_1.begin(BAUD_RATE, SWSERIAL_8N1, D7, D8);

  pinMode(reset_button_esp, INPUT_PULLUP);
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
  pinMode(sensor_5, INPUT);
  pinMode(sensor_6, INPUT);
  pinMode(sensor_7, INPUT);
  pinMode(sensor_8, INPUT);
  pinMode(sensor_9, INPUT);
  pinMode(sensor_10, INPUT);
  pinMode(sensor_11, INPUT);

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

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

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

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, LOW);
  Serial.println("Input and Outputs Arranged Succesfully");

  arrangeWifiAndPassword();
  Serial.print("ssid: ");
  Serial.print(ssid);
  Serial.print(" password: ");
  Serial.print(password);
  Serial.print(" ");

  scan_Wifi();
  if (wifi_name_found == 0) {
    //ble_Setup();
  }

  if (wifi_name_found == 1) {
    tryToReconnectWifi_Setup();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    wifi_Http_Get_Request_For_Ota_Filename_Setup();
    //Send_Mail(emailtaker_mail_adress, "Cihaz Yeniden Başlatıldı", "Merhaba, <br>Detaylı Bilgi İçin,<br>Mobil Uygulamanız Üzerinden son güncel veri saatini kontrol ediniz. Teşekkür Ederiz");
    http_Post_Take_Session_Id_Setup();
    wifi_Http_Post_Request_Create_Setup(true);

    charge_counter = setting_1_value;
    sum_of_power = setting_2_value;

    swSer_send_Data_Pstatus("6");
    Serial.println("---------- Master Send To Led Panel Started Data ----------------");

    // Initialize a NTPClient to get time
    timeClient.begin();
    // Set offset time in seconds to adjust for your timezone, for example:
    // GMT +1 = 3600
    // GMT +8 = 28800
    // GMT -1 = -3600
    // GMT 0 = 0
    timeClient.setTimeOffset(3600);
    wifi_Ntc_Time_Setup();

  }

  device_Status_Setup();

  //myNextion.sendCommand("page page_home");
  //delay(1000);
  //nextion_Send_Datas_At_Setup();

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(500);
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ) {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(server_url + "/create/report-for-device");
      http.addHeader("Cookie", auth_session_id);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Connection", "keep-alive");
      http.addHeader("Accept-Encoding", "gzip, deflate, br");
      http.addHeader("Accept", "*/*");
      http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
      if (wifi_request_counter == test_signal_time * 4 ) {
        create_report = true;
        wifi_request_counter = 0;
      }
      else {
        create_report = false;
      }
      if (wifi_request_counter > test_signal_time * 4 ) {
        wifi_request_counter = 0;
      }
      if (ademco_id.indexOf("E130") >= 0) {
        create_report = false;
      }
      http.setConnectTimeout(5000);
      int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"create\",\"params\":{\"device_id\":\"" + id + "\",\"code\":\"" + String(ademco_id) + all_sensor_values + "\",\"zone\":\"2\",\"create_report\":" + String(create_report) + ",\"device_update\":" + device_update + "},\"id\":569151295}");
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
        if (httpResponseCode == 200 && response.indexOf("\"error\":") < 0) {
          wifi_request_counter++;
          if (restart_device_value == 1) {
            ESP.restart();
          }
        }
        Serial.println("wifi_request_counter: " + String(wifi_request_counter));
        wifi_Get_Data_Parser(response);
      } else {
        Serial.print("Error on sending Post Create Request: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("Error in WiFi connection(Http Post Ask Server)");
    }
    delay(15000);
  }
}

void loop() {
  timerWrite(timer, 0); //reset timer (feed watchdog)

  //change_wifi_Command();
  if (ble_status == 0 && WiFi.status() != WL_CONNECTED) {
    scan_Wifi_Timer();
  }

  reset_Wifi_Name();

  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  if (sensor_7_value > 1900 && sensor_7_value < 2500) {
    setting_1_value = int(ceil(pow(charge_counter, 0.333)));
    setting_2_value = int(ceil(pow(sum_of_power, 0.333)));
    setting_3_value = int(ceil(pow(entrance_delay_time, 0.333)));
    write_Int_ToEeprom();
    delay(20000);
  }

  energy_Analyzer_Relay_1();

  charge_Time_plug_Out_Status();
  idle_Timer();

  //finish_Charge_Because_Of_Money();

  check_Money_Finish();

  read_Energy_Serial();
  read_Sensors();

  fast_Response_Request();

  restart_Device_Over_Wifi();

  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  if (sensor_7_value > 1900 && sensor_7_value < 2500) {
    setting_1_value = int(ceil(pow(charge_counter, 0.333)));
    setting_2_value = int(ceil(pow(sum_of_power, 0.333)));
    setting_3_value = int(ceil(pow(entrance_delay_time, 0.333)));
    write_Int_ToEeprom();
    delay(20000);
  }

  //return_Of_Charge_Module();

  charge_State();

  if (charge_state_from_module == 1) {
    control_Relays();
  }

  //esp_To_Esp_Communication();
  //swSer1_Send_Data();
  //  if (WiFi.status() != WL_CONNECTED) {
  //    gsm_Timer();
  //    gsm_Send_Httppost_1("http://panel.xsarj.com:8081/create/report-for-device");
  //    //gsm_Send_Httpget_1("http://panel.xsarj.com:8081/create/report-for-device-gsm");
  //    gsm_Health_Control();
  //  }
  //  read_Gsm_Serial();
  //  write_Gsm_Serial();
  wifi_Ntc_Time();
  //nextion_Control();
  //nextion_Send_Data_Periodic();

  http_Post_Take_Session_Id();

  //esp_To_Esp_Communication();

  sensor_7_value = analogRead(sensor_7); // analog voltage by resistor
  if (sensor_7_value > 1900 && sensor_7_value < 2500) {
    setting_1_value = int(ceil(pow(charge_counter, 0.333)));
    setting_2_value = int(ceil(pow(sum_of_power, 0.333)));
    setting_3_value = int(ceil(pow(entrance_delay_time, 0.333)));
    write_Int_ToEeprom();
    delay(20000);
  }

  led_Status();

  device_Status();

  wifi_Http_Get_Request_For_Ota_Filename();

}
