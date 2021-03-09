#include <Arduino.h>
/**
 * Arduino Sketch für SmartHome yourself - Arduino Lehrgang
 * 
 * Tag 19: GPIO über SerialComInstruments steuern
 * In diesem Sketch überwachen wir die Serielle Kommunikation auf Eingaben. 
 * In der loop-Methode wird geprüft ob eine Eingabe nach dem SerialComInstruments-Protokoll codiert vom PC an den Arduino übertragen wird.
 * Falls eine Eingabe nach dem Schema "#__M__<" übertragen wird, wird diese geprüft. 
 * Sofern ein gültiger Kanal erkannt wird (zwischen "#" und "M"), wird der Wert (zwischen "M" und "<") ausgewertet 
 * und entsprechend verarbeitet.
 * 
 * Beim schalten der LEDs wird nach gleicher Codierung ein Farbcode vom Arduino an den PC übermittelt. 
 * Dies sorgt für eine Einfärbung des entsprechenden Blocks in der Oberfläche. 
 * 
 * https://www.arduino.cc/reference/en/language/functions/communication/serial/parseint/
 * https://www.arduino.cc/reference/en/language/functions/communication/serial/parsefloat/
 * 
 * http://www.serialcominstruments.com/SerialComInstruments%20Doku.pdf
 * 
 * By Daniel Scheidler - Dezember 2019
 *
 *
 *******************************************  zum Testen vom RGB LED 64x32 Panel. Programm in Examples ***********************************
 *
 */

const unsigned int Line_A = A0;                // globale Konstante für Pin mit roter LED
const unsigned int Line_B = A1;               // globale Konstante für Pin mit gelber LED
const unsigned int Line_C = A2;              // globale Konstante für Pin mit grüner LED
const unsigned int Line_D = A3;                // globale Konstante für Pin mit roter LED
const unsigned int RED_oben = 12;               // globale Konstante für Pin mit gelber LED
const unsigned int GREEN_oben = 11;              // globale Konstante für Pin mit grüner LED
const unsigned int BLUE_oben = 10;                // globale Konstante für Pin mit roter LED
const unsigned int RED_unten = 9;               // globale Konstante für Pin mit gelber LED
const unsigned int GREEN_unten = 8;              // globale Konstante für Pin mit grüner LED
const unsigned int BLUE_unten = 7;                // globale Konstante für Pin mit roter LED
const unsigned int CLOCK = 6;               // globale Konstante für Pin mit gelber LED
const unsigned int LATCH = 5;              // globale Konstante für Pin mit grüner LED
const unsigned int OE = 4;

void schalte(int kanal, float wert);

void setup() {
  Serial.begin(38400);                              // Serielle Kommunikation mit 38400 Baud starten


  pinMode(Line_A, OUTPUT);
  pinMode(Line_B, OUTPUT);
  pinMode(Line_C, OUTPUT);
  pinMode(Line_D, OUTPUT);
  pinMode(RED_oben, OUTPUT);                    // PIN von roter LED als OUTPUT festlegen.
  pinMode(GREEN_oben, OUTPUT);                   // PIN von gelber LED als OUTPUT festlegen.
  pinMode(BLUE_oben, OUTPUT);                  // PIN von grüner LED als OUTPUT festlegen.
  pinMode(RED_unten, OUTPUT);
  pinMode(GREEN_unten, OUTPUT);
  pinMode(BLUE_unten, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(OE, OUTPUT);

  digitalWrite(Line_A, 0);
  digitalWrite(Line_B, 0);
  digitalWrite(Line_C, 0);
  digitalWrite(Line_D, 0);
  digitalWrite(RED_oben, 0);
  digitalWrite(GREEN_oben, 0);
  digitalWrite(BLUE_oben, 0);
  digitalWrite(RED_unten, 0);
  digitalWrite(GREEN_unten, 0);
  digitalWrite(BLUE_unten, 0);
  digitalWrite(CLOCK, 0);
  digitalWrite(LATCH, 0);
  digitalWrite(OE, 0);

}


void loop() {
  char zeichen;
  int kanalId;
  float wert;

  while (Serial.available()) {                      // Solange serielle Eingabe vorhanden ist
    zeichen = Serial.read(); 
    Serial.write(zeichen);                       // nächstes Zeichen einlesen
    if (zeichen == '#') {                           // Wenn Zeichen eine Raute ist:
      kanalId = Serial.parseInt();                  // eingehende Ganzzahl in Variable "kanalId" einlesen.
                                                    // gelesen wird bis zum nächsten Zeichen, welches keine Ganzzahl ist.
      
      zeichen = Serial.read();                      // nächstes Zeichen einlesen.
      Serial.write(zeichen);  
      if (zeichen == 'M') {                         // Wenn gelesenes Zeichen ein "M" ist:
        wert = Serial.parseFloat();                 // eingehende Fließkommazahl einlesen.
                                                    // gelesen wird bis zum nächsten Zeichen, welches keine Fließkommazahl ist.
        
        zeichen = Serial.read();                    // nächstes Zeichen einlesen.
        Serial.write(zeichen);  
        if (zeichen == '<') {                       // Wenn gelesenes Zeichen ein Kleiner-Zeichen ist:
          schalte(kanalId, wert);                   // rufe "schalte" Methode mit eingelesenem Kanal und Wert auf.
        }
      }
    }
  Serial.write(" /r/n");  
  }

}


void schalte(int kanal, float wert){
  switch (kanal){                                   // Kanal auswerten
     case 1:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(Line_A, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(Line_A, LOW);           // rote LED ausschalten
       }
       break;                                       // aus switch/case aussteigen

     case 2:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(Line_B, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(Line_B, LOW);           // rote LED ausschalten
       }
       break;

     case 3:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(Line_C, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(Line_C, LOW);           // rote LED ausschalten
       }
       break;       
    
    case 4:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(Line_D, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(Line_D, LOW);           // rote LED ausschalten
       }
       break;
    
    case 5:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(RED_oben, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(RED_oben, LOW);           // rote LED ausschalten
       }
       break;

     case 6:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(GREEN_oben, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(GREEN_oben, LOW);           // rote LED ausschalten
       }
       break;

     case 7:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(BLUE_oben, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(BLUE_oben, LOW);           // rote LED ausschalten
       }
       break;

     case 8:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(RED_unten, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(RED_unten, LOW);           // rote LED ausschalten
       }
       break;

     case 9:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(GREEN_unten, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(GREEN_unten, LOW);           // rote LED ausschalten
       }
       break;

     case 10:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(BLUE_unten, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(BLUE_unten, LOW);           // rote LED ausschalten
       }
       break;

     case 11:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(CLOCK, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(CLOCK, LOW);           // rote LED ausschalten
       }
       break;

     case 12:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(LATCH, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(LATCH, LOW);           // rote LED ausschalten
       }
       break;

     case 13:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(OE, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(OE, LOW);           // rote LED ausschalten
       }
       break;        

  }
}

