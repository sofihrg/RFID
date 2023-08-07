#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

//Declaración de los pines que se usarán en la comunicación UART.
SoftwareSerial BT1(10, 11); // RX | TX



//Declaración de los pines que se usarán en la comunicación SPI.
const int RST_pin = 5; //Pin para resetear el módulo
const int SS_pin = 53; //Pin de selección del módulo/esclavo. También llamado SDA.
//Creación del objeto mfrc522
MFRC522 mfrc522(SS_pin, RST_pin);//¿Cuáles son los registros?

void setup() {
  Serial.begin(9600); //Inicia puerto serial
  SPI.begin(); //Inicia comunicación por SPI
  mfrc522.PCD_Init(); //Inicia el módulo MFRC522 con el nombre de objeto declarado anteriormente

  pinMode(8, OUTPUT);        // Al poner en HIGH forzaremos el modo AT
  pinMode(9, OUTPUT);        // cuando se alimente de aqui
  digitalWrite(8, HIGH);
  delay (500) ;              // Espera antes de encender el modulo
  Serial.begin(9600);
  Serial.println("Levantando el modulo HC-05");
  digitalWrite (9, HIGH);    //Enciende el modulo
  Serial.println("Esperando comandos AT:");
  BT1.begin(9600); 
}

void loop(){
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print("UID: ");
      /*
       * mfrc522.uid.size: Almacena el tamaño del UID.
       * mfrc522.uid.uidByte: almacena cada byte del UID.
       * 
       * Los byte se concatenarán en un array. Se usa mfrc522.uid.size como 
       * referencia de cuántas veces repetir el proceso.
       * 
       * El UID será mostrado en formato hexadecimal en el monitor serie.
      */
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        
        if (BT1.available())
            Serial.println(mfrc522.uid.uidByte[i],HEX);
            BT1.println(mfrc522.uid.uidByte[i],HEX);
            

            
        if (Serial.available())
            Serial.println(mfrc522.uid.uidByte[i],HEX);
      }
      
      Serial.println(); //Imprime un salto de línea.
      mfrc522.PICC_HaltA(); //Resetea el módulo para estar disponible a nuevas lecturas.
    }
  }
  delay(250);

}
