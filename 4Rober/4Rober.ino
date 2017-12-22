/*
  Proyecto 4Rober ver Documentacion.
  Autor: Padron Agustin.
*/

#include <TimedAction.h>    //Libreria para ejecutar procedimientos cada determinado tiempo
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  


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

//variables de programa
int     estado = 0;
boolean protec_on = true;
boolean sacudir_on = false;

void sacudir();

SoftwareSerial BT(4,2);    // Definimos los pines RX y TX del Bluetooth
TimedAction sacudirT = TimedAction(250,sacudir);

void setup() {
  //se seleccionan los pines de salida para motores
  pinMode(izq, OUTPUT);
  pinMode(izq2, OUTPUT);
  pinMode(der, OUTPUT);
  pinMode(der2, OUTPUT);
  
  BT.begin(9600);       // Inicializamos el puerto serie BT
}

void loop() {
  if (sacudir_on) {
    sacudirT.check();
  }
  EscuchaBluetooth();
  if (protec_on){
    proteccion();
  }
}

//funcion de manejo de Bluetooth
void EscuchaBluetooth() {
  //Si envian algo por BR
  if(BT.available()) {
    int comando;
    comando = BT.read();
    sacudir_on = false;
    switch(comando) {
      case '0':
        neutro();
        break;
      case '1':
        avanzar(255);
        break;
      case '2':
        retroceder(255);
        break;
      case '3':
        izquierda(255);
        break;
      case '4':
        derecha(255);
        break;
      case '5':
        frenar(255);
        break;
      case '6':
        sacudir_on = true;
        break;
    }
  }

}

//Funciones de control de distancia
int medir(int trigPin,int echoPin){
  long durac;
  int dist;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  int medida = medir(trigPin_der, echoPin_der);
  return medida;
}

int medir_izquierda() {
  int medida = medir(trigPin_izq, echoPin_izq);
  return medida;
}

boolean limite_derecha() {
  int limite = 15;
  boolean resultado = false;
  if (medir_derecha() < limite) {
    resultado = true;
  }
  return resultado;
}

boolean limite_izquierda() {
  int limite = 15;
  boolean resultado = false;
  if (medir_izquierda() < limite) {
    resultado = true;
  }
  return resultado;
}

void proteccion() {
  if (limite_derecha() == true || limite_izquierda() == true){
    if (estado == 1) {
      neutro();
    }
  }
}

//Funciones de control de motores
void neutro() {
  analogWrite(izq, 0);
  analogWrite(izq2, 0);
  analogWrite(der, 0);
  analogWrite(der2, 0);
  estado = 0;
}

void frenar(int potencia) {
  analogWrite(izq, potencia);
  analogWrite(izq2, potencia);
  analogWrite(der, potencia);
  analogWrite(der2, potencia);
  estado = 5;
}


void avanzar(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, potencia);
  analogWrite(izq2, 0);
  analogWrite(der, potencia);
  analogWrite(der2, 0);
  estado = 1;
}

void retroceder(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, 0);
  analogWrite(izq2, potencia);
  analogWrite(der, 0);
  analogWrite(der2, potencia);
  estado = 2;
}

void izquierda(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, 0);
  analogWrite(izq2, potencia);
  analogWrite(der, potencia);
  analogWrite(der2, 0);
  estado = 3;
}

void derecha(int potencia) {
  //para avanzar se hace giradar los motores derecho e izquierdo hacia adelante.
  analogWrite(izq, potencia);
  analogWrite(izq2, 0);
  analogWrite(der, 0);
  analogWrite(der2, potencia);
  estado = 4;
}

void sacudir() {
  if (estado == 3) {
    derecha(255);
  }else{
    izquierda(255);
  }
}


