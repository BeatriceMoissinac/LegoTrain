//www.elegoo.com
//2016.12.09

/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example to change UID of changeable MIFARE card.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * This sample shows how to set the UID on a UID changeable MIFARE card.
 * NOTE: for more informations read the README.rst
 * 
 * @author Tom Clement
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10   // Configurable, see typical pin layout above

/* Set your new UID here! */
#define MyUID2 {213, 226, 100, 163} // blue one
#define MyUID {129,254, 32, 47}
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance



MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  // Enhance the MFRC522 Receiver Gain to maximum value of some 48 dB
  mfrc522.PCD_SetRegisterBitMask(mfrc522.RFCfgReg, (0x07<<4));
  Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));

  //LED
  pinMode(A0, OUTPUT);
  analogWrite(A0,0);

}


void loop() {
  
  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }


    
  // Read UID
//  Serial.print(F("Card UID:"));
//  for (byte i = 0; i < mfrc522.uid.size; i++) {
////    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
////    Serial.print(mfrc522.uid.uidByte[i], HEX);
//    Serial.println(mfrc522.uid.uidByte[i]);
//  } 
//  Serial.println();


  bool successRead = true;
  byte successCode[] = MyUID;
  if (mfrc522.uid.uidByte[0] != successCode[0]){
     successRead = false;
  }
//  for (byte i = 0; i < mfrc522.uid.size; i++) {
//    if (mfrc522.uid.uidByte[i] != successCode[i]){
//      successRead = false;
//    }
//  }

  if(successRead){
    //Piezo sound and LED signal
    tone(8, 262, 500);
    analogWrite(A0,255);
    delay(500);
    analogWrite(A0,0);
  }
}
