//gsm module settings
// Gsm saatini Aktif etme
//AT+CCLK?
//AT+CLTS=1
//AT+CLTS?
//AT&W //ayarlatı kaydet gsm' i yeniden başlat
//AT+CCLK?

String apn = "internet";                       //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String gsm_signal_strength;
int gsm_check_counter = 0;
int gsm_status = 0;
int last_gsm_status = 0;
int gsm_error = 0;
String gsm_serial_data = "";

unsigned long previousMillis_gsm_post1_timer = 0;
const long interval_gsm_post1_timer = 100;

unsigned long previousMillis_gsm_get1_timer = 0;
const long interval_gsm_get1_timer = 100;

unsigned long previousMillis_gsm_check_timer = 0;
const long interval_gsm_check_timer = 1000;

int gsm_counter = 0;
int last_gsm_counter = 0;



void gsm_Health_Control() {
  gsm_Check_Timer();
  //  Serial.print("gsm_check_counter");
  //  Serial.print("-");
  //  Serial.println(gsm_check_counter);
  // timer 1000 ms ye ayarlı yani 1 dk
  if (gsm_check_counter > 60 && gsm_counter < 1000) {
    //sim800l resetle
    Serial.println("reset sim");
    gsm_Restart();
    gsm_check_counter = 0;
  }
  if (gsm_serial_data.indexOf("+HTTPACTION:") > 0 && gsm_serial_data.indexOf("601") > 0) {
    gsm_Restart();
    Serial.print(gsm_status);
    Serial.print("-");
    Serial.println(gsm_error);
    gsm_error++;
    gsm_check_counter = 0;
    gsm_serial_data = "";
  }
}

void gsm_Check_Timer() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_gsm_check_timer >= interval_gsm_check_timer) {
    previousMillis_gsm_check_timer = currentMillis;
    gsm_check_counter++;
  }
}

void gsm_Timer() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_gsm_post1_timer >= interval_gsm_post1_timer) {
    previousMillis_gsm_post1_timer = currentMillis;
    gsm_counter++;
  }
}

void gsm_Send_Httppost_1(String url) {
  if (gsm_counter == 40 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+CLTS=1");
  }
  if (gsm_counter == 42 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+CCLK?");
  }
  if (gsm_counter == 44 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+SAPBR=3,1,APN," + apn);
  }
  if (gsm_counter == 48 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+SAPBR =1,1");
  }
  if (gsm_counter == 50 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPINIT");
  }
  if (gsm_counter == 52 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPPARA=CID,1");
  }
  if (gsm_counter == 54 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPPARA=URL," + url);
  }
  if (gsm_counter == 56 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPSSL=1");// urlsi https olursa = 0, sadece http olursa 1 olacak
  }
  if (gsm_counter == 58 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPPARA=CONTENT,application/json"); //application/json
  }
  if (gsm_counter == 60 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPDATA=192,10000");
  }
  if (gsm_counter == 62 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println(json_Object_Creator());
  }
  if (gsm_counter == 150 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPACTION=1");
  }
  if (gsm_counter == 200 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPREAD");
  }
  if (gsm_counter == 202 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPTERM");
  }
  if (gsm_counter == 222 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+SAPBR=0,1");
    gsm_status = 0;
    gsm_error = 0;
  }
}


void gsm_Send_Httpget_1(String url) {

  if (gsm_counter == 224 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+CSQ");
  }
  if (gsm_counter == 226 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+SAPBR=3,1,APN," + apn);
  }
  if (gsm_counter == 228 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+SAPBR =1,1");
  }
  if (gsm_counter == 230 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPINIT");
  }
  if (gsm_counter == 232 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPPARA=CID,1");
  }
  if (gsm_counter == 234 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPPARA=URL," + url);
  }
  if (gsm_counter == 236 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPSSL=1");// urlsi https olursa = 0, sadece http olursa 1 olacak
  }
  if (gsm_counter == 238 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPACTION=0");
  }
  if (gsm_counter == 342 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPREAD");
  }
  if (gsm_counter == 352 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+HTTPTERM");
  }
  if (gsm_counter == 354 && last_gsm_counter != gsm_counter) {
    last_gsm_counter = gsm_counter;
    //swSer.println("AT+SAPBR=0,1");
    gsm_counter = 0;
    gsm_status = 0;
    gsm_error = 0;
  }
}


//Print GSM Status
//void read_Gsm_Serial() {
//  while (swSer.available()) {
//    gsm_serial_data = swSer.readString();
//    yield();
//    Serial.println("gsm data:" + gsm_serial_data);
//    gsm_time_picker();
//    gsm_Status_Counter();
//    gsm_Get_Data_Parser();
//  }
//}
//
//void write_Gsm_Serial() {
//  while (Serial.available() > 0) {
//    swSer.write(Serial.read());
//    yield();
//  }
//}
//Gsm Check and OK - ERROR datas counter
void gsm_Status_Counter() {
  if (gsm_serial_data.indexOf("OK") > 0) {
    gsm_status++;
    gsm_check_counter = 0;
    Serial.print(gsm_status);
    Serial.print("-");
    Serial.println(gsm_error);
  }
  if (gsm_serial_data.indexOf("ERROR") > 0 ) {
    Serial.print(gsm_status);
    Serial.print("-");
    Serial.println(gsm_error);
    gsm_error++;
    gsm_check_counter = 0;
  }
}

void gsm_Get_Data_Parser() {
  if (gsm_serial_data.indexOf("+HTTPREAD:") > 0 && gsm_serial_data.indexOf("!") && gsm_serial_data.indexOf("&") > 0 ) {
    relay_1_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 1 , gsm_serial_data.indexOf("!") + 2));
    relay_2_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 2 , gsm_serial_data.indexOf("!") + 3));
    relay_3_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 3 , gsm_serial_data.indexOf("!") + 4));
    relay_4_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 4 , gsm_serial_data.indexOf("!") + 5));
    relay_5_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 5 , gsm_serial_data.indexOf("!") + 6));
    relay_6_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 6 , gsm_serial_data.indexOf("!") + 7));
    relay_7_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 7 , gsm_serial_data.indexOf("!") + 8));
    relay_8_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 8 , gsm_serial_data.indexOf("!") + 9));
    relay_9_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 9 , gsm_serial_data.indexOf("!") + 10));
    relay_10_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 10 , gsm_serial_data.indexOf("!") + 11));
    relay_11_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 11 , gsm_serial_data.indexOf("!") + 12));
    relay_12_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 12 , gsm_serial_data.indexOf("!") + 13));
    relay_13_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 13 , gsm_serial_data.indexOf("!") + 14));
    relay_14_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 14 , gsm_serial_data.indexOf("!") + 15));
    relay_15_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 15 , gsm_serial_data.indexOf("!") + 16));
    relay_16_cloud_value = (gsm_serial_data.substring(gsm_serial_data.indexOf("!") + 16 , gsm_serial_data.indexOf("!") + 17));
    Serial.print("gsm_cloud_get_data: ");
    Serial.print(gsm_serial_data);
    Serial.print("relay_5_cloud_value");
    Serial.print(":");
    Serial.println(relay_5_cloud_value);
  }
}

void gsm_time_picker() {
  if (gsm_serial_data.indexOf("+CCLK:") > 0 ) {
    String allyear = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 8 , gsm_serial_data.indexOf("+CCLK:") + 25));
    String year = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 8 , gsm_serial_data.indexOf("+CCLK:") + 10));
    te.Year = atoi (year.c_str ());
    String month = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 11 , gsm_serial_data.indexOf("+CCLK:") + 13));
    te.Month = atoi (month.c_str ());
    String day = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 14 , gsm_serial_data.indexOf("+CCLK:") + 16));
    te.Day = atoi (day.c_str ());
    String hour = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 17 , gsm_serial_data.indexOf("+CCLK:") + 19));
    te.Hour = atoi (hour.c_str ());
    String minute = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 20 , gsm_serial_data.indexOf("+CCLK:") + 22));
    te.Minute = atoi (minute.c_str ());
    String second = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 23 , gsm_serial_data.indexOf("+CCLK:") + 25));
    te.Second = atoi (second.c_str ());
    unixTime =  makeTime(te) + 946760400;
    timestamp = String(unixTime);
    Serial.print("time=");
    Serial.println(timestamp);
  }
}

String json_Object_Creator()
{
  StaticJsonBuffer<3400> JSONbuffer;
  JsonObject& JsonData = JSONbuffer.createObject();
  JsonData["sensors"] = all_sensor_data;
  JsonData["time"] = String(unixTime);
  String requestData;
  JsonData.printTo(requestData);
  //Serial.println(requestData);
  return requestData;
}
