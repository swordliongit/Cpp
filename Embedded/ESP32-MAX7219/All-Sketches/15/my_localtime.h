/*
 * Quellen:
 * https://werner.rothschopf.net/202011_arduino_esp8266_ntp_en.htm
 * https://werner.rothschopf.net/microcontroller/202103_arduino_esp32_ntp_en.htm
 * https://www.epochconverter.com/programming/c
 */

#include <time.h>                   // time() ctime()

/* Configuration of NTP */
//#define MY_NTP_SERVER "at.pool.ntp.org"          
const char* ntpServer = "at.pool.ntp.org"; 
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"   /* Configuration of NTP */
// choose the best fitting NTP server pool for your country
#define MY_NTP_SERVER "at.pool.ntp.org"

// choose your time zone from this list
// https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"

/* Globals */
long currenttimestap;

time_t now;                         // this is the epoch
tm tm;                              // the structure tm holds time information in a more convient way

String convertTimestamptoDate(String timest){
  struct tm t2;
  time_t t_of_day = timest.toInt();
  localtime_r(&t_of_day, &t2);  

  //führende Null
  String st;
  String mi;
  String seco;

  if((t2.tm_hour) <10)  st= "0"+String(t2.tm_hour);
  else st = String(t2.tm_hour);

  if((t2.tm_min)<10) mi = "0"+String(t2.tm_min);
  else mi = String(t2.tm_min);

  if((t2.tm_sec)<10) seco = "0"+String(t2.tm_sec);
  else seco = String(t2.tm_sec);

  //String ganzesDatum;
  //ganzesDatum=st+":"+mi+" Uhr "+ String(t2.tm_mday)+"."+String(t2.tm_mon+1)+"."+String(t2.tm_year + 1900);

  String uhrzeit=st+":"+mi+":"+seco;
   
  return uhrzeit;
}

void getcurrenttimestamp() {
  time(&now);     
  // read the current time
  //now=  1635660301;
  localtime_r(&now, &tm);           // update the structure tm with the current time
  currenttimestap=now;
  
  /*
  Serial.print("year:");
  Serial.print(tm.tm_year + 1900);  // years since 1900
  Serial.print("\tmonth:");
  Serial.print(tm.tm_mon + 1);      // January = 0 (!)
  Serial.print("\tday:");
  Serial.print(tm.tm_mday);         // day of month
  Serial.print("\thour:");
  Serial.print(tm.tm_hour);         // hours since midnight  0-23
  Serial.print("\tmin:");
  Serial.print(tm.tm_min);          // minutes after the hour  0-59
  Serial.print("\tsec:");
  Serial.print(tm.tm_sec);          // seconds after the minute  0-61*
  Serial.print("\twday");
  Serial.print(tm.tm_wday);         // days since Sunday 0-6
  if (tm.tm_isdst == 1)             // Daylight Saving Time flag
    Serial.print("\tDST");
  else
    Serial.print("\tstandard");
    */
}
