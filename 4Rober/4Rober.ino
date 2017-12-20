/*
  Proyecto 4Rober ver Documentacion.
  Autor: Padron Agustin.
*/
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(4,2);    // Definimos los pines RX y TX del Bluetooth

//Variable de control de motores
int izq  = 5;   //motor izquierdo borne para avanzar
int izq2 = 6;   //motor izquierdo borne para retroceder
int der  = 10;  //motor derecho borne para avanzar
int der2 = 11;  //motor derecho borne para retroceder
//Variables de sensores de distancia
int echoPin_der = 7;
int trigPin_der = 8;
int echoPin_izq = 9;
int trigPin_izq = 12;


void setup() {
  //se seleccionan los pines de salida para motores
  pinMode(izq, OUTPUT);
  pinMode(izq2, OUTPUT);
  pinMode(der, OUTPUT);
  pinMode(der2, OUTPUT);

  BT.begin(9600);       // Inicializamos el puerto serie BT
  
  avanzar(255);
  delay(2000);
  frenar(255);
  delay(2000);
  izquierda(255);
  delay(2000);
  derecha(255);
  delay(2000);
  retroceder(255);
  delay(2000);
  neutro();
}

void loop() {
  //Si envian algo por BR
  if(BT.available()) {
    int comando;
    comando = BT.read();
    switch(comando) {
      case 0:
        neutro();
        break;
      case 1:
        avanzar(255);
        break;
      case 2:
        retroceder(255);
        break;
      case 3:
        izquierda(255);
        break;
      case 4:
        derecha(255);
        break;
      case 5:
        frenar(255);
        break;
      case 6:
        sacudir(1000, 10);
        break;
    }
  }

}

//Funciones de control de distancia
int medir(int trigPin,int echoPin){
  long durac;
  int dist;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durac = pulseIn(echoPin, HIGH);
  dist = (durac/2) / 29.1;
  return (dist);
}

int medir_derecha() {
  return (medir(trigPin_der, echoPin_der));
}

int medir_izquiera() {
  return (medir(trigPin_izq, echoPin_izq));
}


//Funciones de control de motores
void neutro() {
  analogWrite(izq, 0);
  analogWrite(izq2, 0);
  analogWrite(der, 0);
  analogWrite(der2, 0);
}

void frenar(int potencia) {
  analogWrite(izq, potencia);
  analogWrite(izq2, potencia);
  analogWrite(der, potencia);
  analogWrite(der2, potencia);
}


void avanzar(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, potencia);
  analogWrite(izq2, 0);
  analogWrite(der, potencia);
  analogWrite(der2, 0);
}

void retroceder(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, 0);
  analogWrite(izq2, potencia);
  analogWrite(der, 0);
  analogWrite(der2, potencia);
}

void izquierda(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, 0);
  analogWrite(izq2, potencia);
  analogWrite(der, potencia);
  analogWrite(der2, 0);
}

void derecha(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, potencia);
  analogWrite(izq2, 0);
  analogWrite(der, 0);
  analogWrite(der2, potencia);
}


void sacudir(int sensibilidad, int repeticiones) {
  for (int i = 0; i < repeticiones; i++) {
    izquierda(255);
    delay(sensibilidad);
    derecha(255);
    delay(sensibilidad*2);
  }
}
