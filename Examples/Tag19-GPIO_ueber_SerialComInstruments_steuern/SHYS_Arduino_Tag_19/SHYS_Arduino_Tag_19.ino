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
 */

const unsigned int ROTE_LED_PIN = 3;                // globale Konstante für Pin mit roter LED
const unsigned int GELBE_LED_PIN = 4;               // globale Konstante für Pin mit gelber LED
const unsigned int GRUENE_LED_PIN = 5;              // globale Konstante für Pin mit grüner LED


void setup() {
  Serial.begin(38400);                              // Serielle Kommunikation mit 38400 Baud starten

  pinMode(ROTE_LED_PIN, OUTPUT);                    // PIN von roter LED als OUTPUT festlegen.
  pinMode(GELBE_LED_PIN, OUTPUT);                   // PIN von gelber LED als OUTPUT festlegen.
  pinMode(GRUENE_LED_PIN, OUTPUT);                  // PIN von grüner LED als OUTPUT festlegen.
}


void loop() {
  char zeichen;
  int kanalId;
  float wert;

  while (Serial.available()) {                      // Solange serielle Eingabe vorhanden ist
    zeichen = Serial.read();                        // nächstes Zeichen einlesen
    if (zeichen == '#') {                           // Wenn Zeichen eine Raute ist:
      kanalId = Serial.parseInt();                  // eingehende Ganzzahl in Variable "kanalId" einlesen.
                                                    // gelesen wird bis zum nächsten Zeichen, welches keine Ganzzahl ist.
      
      zeichen = Serial.read();                      // nächstes Zeichen einlesen.
      if (zeichen == 'M') {                         // Wenn gelesenes Zeichen ein "M" ist:
        wert = Serial.parseFloat();                 // eingehende Fließkommazahl einlesen.
                                                    // gelesen wird bis zum nächsten Zeichen, welches keine Fließkommazahl ist.
        
        zeichen = Serial.read();                    // nächstes Zeichen einlesen.
        if (zeichen == '<') {                       // Wenn gelesenes Zeichen ein Kleiner-Zeichen ist:
          schalte(kanalId, wert);                   // rufe "schalte" Methode mit eingelesenem Kanal und Wert auf.
        }
      }
    }
  }

}


void schalte(int kanal, float wert){
  switch (kanal){                                   // Kanal auswerten
     case 1:                                        // Wenn Kanal = 1 ist
       // Switch-Button
       if (wert > 0){                               // Wenn Wert größer 0 ist
         digitalWrite(ROTE_LED_PIN, HIGH);          // rote LED einschalten
       } else {                                     // sonst
         digitalWrite(ROTE_LED_PIN, LOW);           // rote LED ausschalten
       }
       break;                                       // aus switch/case aussteigen
       
     case 2:                                        // Wenn Kanal = 2 ist
       // Button-Panel
       if (wert == 1){                              // Wenn Wert = 1 ist
         digitalWrite(GELBE_LED_PIN, HIGH);         // gelbe LED einschalten
         Serial.println("#2M41<");                  // ersten Button Gelb färben
         Serial.println("#2M22<");                  // zweiten Button Grau färben
         
       } else if (wert == 2){                       // Wenn Wert = 2 ist
         digitalWrite(GELBE_LED_PIN, LOW);          // gelbe LED ausschalten
         Serial.println("#2M21<");                  // ersten Button Grau färben
         Serial.println("#2M02<");                  // zweiten Button Schwarz färben
         
       } else if (wert == 3){                       // Wenn Wert = 3 ist
         digitalWrite(GRUENE_LED_PIN, HIGH);        // grüne LED einschalten
         Serial.println("#2M53<");                  // dritten Button Grün färben
         Serial.println("#2M24<");                  // vierten Button Grau färben
         
       } else if (wert == 4){                       // Wenn Wert = 4 ist
         digitalWrite(GRUENE_LED_PIN, LOW);         // grüne LED ausschalten
         Serial.println("#2M23<");                  // dritten Button Grau färben
         Serial.println("#2M04<");                  // vierten Button Schwarz färben
       }
       break;
  }
}

