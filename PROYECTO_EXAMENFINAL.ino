#include <IRremote.h>     //Libreria para el sensor infrarojo
#include "LedControl.h"   //Libreria para la matriz 8x8
#include <SPI.h>          // Libreria bus SPI
#include <MFRC522.h>      // Libreria especifica para MFRC522

#define RESTART asm("jmp 0x0000")


//SALIDAS PARA MOTOR DE CARRO
int ENA = 2; //MOTOR IZQUIERDO
int IN1 = 3;
int IN2 = 4; //HIGH HACIA ADELANTE
int ENB = 9; //MOTOR DERECHO
int IN3 = 6;
int IN4 = 7; //HIGH HACIA ADELANTE


//SENSOR ULTRASONICO
int Echo = 23;
int Trig = 22;
long duracion, distancia;



LedControl lc = LedControl(49, 52, 53, 1);

byte Encendido[8] = {

  B00011000,
  B00011000,
  B00011000,
  B01011010,
  B10011001,
  B10000001,
  B01000010,
  B00111100,
};

//DESPUES DE 1M
byte MAYOR1M[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

//75CM A 1 M
byte ENTRE75Y1[8] = {
  
  B00000000,
  B11111111,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00011000,
  B00000000,
  
};

//50CM A 75CM
byte ENTRE50Y75[8] = {
  
  B00000000,
  B00000000,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00000000,
  B00000000,
  
};

//25CM A 50CM
byte ENTRE25Y50[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00111110,
  B00011100,
  B00001000,
  B00000000,
  B00000000,

  
  };

//15CM A 25CM
byte ENTRE15Y25[8] = {
  
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B00111100,
  B00000000,
  
};

//15CM
byte MENORA5[8] = {
  
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00111100,
  B00111100,
  B00000000,
  B00000000,
  
};


int buzzer = 8;
IRrecv irrecv(buzzer);
decode_results codigo;

void setup() {
  //SALIDAS PARA LOS MOTORES DEL CARRO
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(buzzer, OUTPUT);

  //SENSOR ULTRASONICO
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  
  //MATRIZ 8X8
  lc.shutdown(0, false);
  lc.setIntensity(0, 4);
  lc.clearDisplay(0);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  digitalWrite(Trig, HIGH);   // Genera el pulso de trigger por 10us
  delay(0.01);
  digitalWrite(Trig, LOW);

  duracion = pulseIn(Echo, HIGH);          // Lee el tiempo del Echo
  distancia = (duracion / 2) / 29;          // Calcula la distancia en centimetros
  delay(10);

  if (distancia > 100) {  // si la distancia es mayor a 1M

          for (int a = 0; a < 8; a++) {
        lc.setRow(0, a, MAYOR1M[a]);
      }
    digitalWrite(ENA, 127);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, 127);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay (500);

  }
  if (distancia <=100 && distancia >= 76) {  // si la distancia es entre 75CM y 1M

          for (int a = 0; a < 8; a++) {
        lc.setRow(0, a, ENTRE75Y1[a]);
      }
    digitalWrite(ENA, 102);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, 102);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay (500);

  }

  if (distancia <=75 && distancia >=51) {  // si la distancia es entre 50CM y 75CM

          for (int a = 0; a < 8; a++) {
        lc.setRow(0, a, ENTRE50Y75[a]);
      }
    digitalWrite(ENA, 76);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, 76);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(500);
    
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
    

  }
  if (distancia <=50 && distancia >=26) {  // si la distancia es entre 25CM y 50CM

          for (int a = 0; a < 8; a++) {
        lc.setRow(0, a, ENTRE25Y50[a]);
      }
    digitalWrite(ENA, 51);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, 51);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(500);

    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer,LOW);
    delay(250);
    

  }

  if (distancia <=25 && distancia >=16) {  // si la distancia es menor a 25CM

          for (int a = 0; a < 8; a++) {
        lc.setRow(0, a, ENTRE15Y25[a]);
      }
    digitalWrite(ENA, 25);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, 25);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(500);
    
    digitalWrite(buzzer, HIGH);
    
    
  }

  if (distancia <=15) {  // si la distancia es menor a 15CM

          for (int a = 0; a < 8; a++) {
        lc.setRow(0, a, MENORA5[a]);
      }
    digitalWrite(ENA, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    digitalWrite(buzzer, LOW);

  }
 
}
