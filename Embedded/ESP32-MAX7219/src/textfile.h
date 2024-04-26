#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <SPIFFS.h>

const char* myfile = "/mytext.txt";
// for reading out and displaying the text for the LED matrix bar
#define BUF_SIZE 30
char message[BUF_SIZE] = ".";
bool newMessageAvailable = true;


void deleteTextfile()
{
    SPIFFS.remove(myfile);
    delay(500);
}

void saveText(String myText)
{
    deleteTextfile();
    File file = SPIFFS.open(myfile, "w");
    file.print(myText);
    file.close();
    Serial.println("Data" + String(myfile) + " with the text: " + myText + "is created.");
}

// for the display on the LED matrix bar
void selectText(void){ 

    File file = SPIFFS.open(myfile, "r");
    //reset to default
    for( int i = 0; i < sizeof(message);  ++i )
    {
        message[i] = (char)0;
    }
        
     
    static uint8_t putIndex = 0;
  
    for(putIndex=0; putIndex < file.size(); putIndex++)
    {
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

// for website
String checkTextexists()
{
    if (SPIFFS.exists(myfile)) {
        File file = SPIFFS.open(myfile, "r");
        int i;
        String output;
        for (i = 0; i < file.size(); i++) 
        {
            output += (char)file.read();
        }
        file.close();
        return output;
    }
    else return "false";
}

#endif