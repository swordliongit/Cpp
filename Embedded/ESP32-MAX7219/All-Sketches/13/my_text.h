const char* datei = "/meintext.txt";
// zum Auslesen und Darstellen des textes für die LED-Matrixleiste
#define BUF_SIZE  75
char message[BUF_SIZE] = ".";
bool newMessageAvailable = true;

void deleteTextfile(){
  SPIFFS.remove(datei);
  delay(100);
}

void speichereWert(String meingrandioserText){
      deleteTextfile();
      File file = SPIFFS.open(datei, "w");     
      // Daten hinzufügen
      file.print(meingrandioserText);
      file.close();
      Serial.println("Datei " + String(datei) + " mit Text " + meingrandioserText + "  erstellt!");
}

//für die Website
String checkTextexists(){

  if (SPIFFS.exists(datei)) {
    File file = SPIFFS.open(datei, "r");
    int i;
    String ausgabe;
     for (i = 0; i < file.size(); i++) {
      ausgabe += (char)file.read();
    }
    file.close();
    return ausgabe;
  }
  else return "false";
}


//für die Darstellung auf der LED-Matrix-leiste
void selectText(void){ 

  File file = SPIFFS.open(datei, "r");

  //zurücksetzen
  for( int i = 0; i < sizeof(message);  ++i )
    message[i] = (char)0;
     
  static uint8_t  putIndex = 0;
  
     for(putIndex=0;putIndex<file.size();putIndex++){
        message[putIndex] = (char)file.read();
      }

     
    if ((message[putIndex] == '\n') || (putIndex >= BUF_SIZE-3))  // end of message character or full buffer
    {
      // put in a message separator and end the string
      message[putIndex] = '\0';
      // restart the index for next filling spree and flag we have a message waiting
      putIndex = 0;
      newMessageAvailable = true;
    }

    file.close();

}
