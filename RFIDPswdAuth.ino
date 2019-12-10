#include <Keyboard.h>



/*
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read data from a PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>
//#include <Keyboard.h>
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

//

int greenLED = A1;
int redLED = A0;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  //while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("Please put your card on the RFID reader..");
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  //Keyboard.begin();
  
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String RFIDtag = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    RFIDtag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    RFIDtag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  RFIDtag.toUpperCase();
  
  if ( RFIDtag.substring(1) == "96 4D 20 7E" )//Change the 00 00 00 00 to your UID card number that you want to give access 

  {
    Serial.println("Access is granted");
    digitalWrite(greenLED, HIGH);
    delay(1000);
    digitalWrite(greenLED, LOW);
    if (digitalRead(8) == HIGH && 
        digitalRead(7) == LOW && 
        digitalRead(6) == LOW && 
        digitalRead(5) == LOW && 
        digitalRead(4) == LOW && 
        digitalRead(3) == LOW && 
        digitalRead(2) == LOW) {
      Keyboard.print("1on");
      pressEnter();
    } else if (digitalRead(8) == LOW && 
        digitalRead(7) == HIGH && 
        digitalRead(6) == LOW && 
        digitalRead(5) == LOW && 
        digitalRead(4) == LOW && 
        digitalRead(3) == LOW && 
        digitalRead(2) == LOW) {
      Keyboard.print("2on");
      pressEnter();
    } else if (digitalRead(8) == LOW && 
        digitalRead(7) == LOW && 
        digitalRead(6) == HIGH && 
        digitalRead(5) == LOW && 
        digitalRead(4) == LOW && 
        digitalRead(3) == LOW && 
        digitalRead(2) == LOW) {
      Keyboard.print("3on");
      pressEnter();
    } else if (digitalRead(8) == LOW && 
        digitalRead(7) == LOW && 
        digitalRead(6) == LOW && 
        digitalRead(5) == HIGH && 
        digitalRead(4) == LOW && 
        digitalRead(3) == LOW && 
        digitalRead(2) == LOW) {
      Keyboard.print("4on");
      pressEnter();
    } else if (digitalRead(8) == LOW && 
        digitalRead(7) == LOW && 
        digitalRead(6) == LOW && 
        digitalRead(5) == LOW && 
        digitalRead(4) == HIGH && 
        digitalRead(3) == LOW && 
        digitalRead(2) == LOW) {
      Keyboard.print("5on");
      pressEnter();
    } else if (digitalRead(8) == LOW && 
        digitalRead(7) == LOW && 
        digitalRead(6) == LOW && 
        digitalRead(5) == LOW && 
        digitalRead(4) == LOW && 
        digitalRead(3) == HIGH && 
        digitalRead(2) == LOW) {
      Keyboard.print("6on");
      pressEnter();
    } else if (digitalRead(8) == LOW && 
        digitalRead(7) == LOW && 
        digitalRead(6) == LOW && 
        digitalRead(5) == LOW && 
        digitalRead(4) == LOW && 
        digitalRead(3) == LOW && 
        digitalRead(2) == HIGH) {
      Keyboard.print("7on");
      pressEnter();
    }
    
    Serial.println("Please put your card on the RFID reader..");

  }

  else   {
    Serial.println("Access is denied");
    digitalWrite(redLED, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    Serial.println("Please put your card on the RFID reader..");
  }
}

void pressEnter() {
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}

