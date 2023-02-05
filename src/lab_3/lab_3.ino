/*
Universidad de Costa Rica
Escuela de Ingenieria Electrica
IE-0624 Laboratorio de Microcontroladores
Laboratorio 3: Voltimetro de 4 canales con Arduino Uno
Elaborado por:  Jhon Gaitan Aguilar B73059
                Alex Varela Quiros  B26918
III-2022
*/

#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.h>
#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.cpp>
#include <math.h>
#include <stdio.h>


// Declaracion de Hardware y variables necesarias
static PCD8544 lcd;
// Definimos los nombres de los pines analogicos para la lectura del voltaje
int analogInput5 = 5; // PIN A5
int analogInput4 = 4; // PIN A4
int analogInput2 = 2; // PIN A2
int analogInput0 = 0; // PIN A0
// LEDS de aviso conectados a cada pin numerado
int alarma_led_1 = 9; // Alarma para canal 1
int alarma_led_2 = 10; // Alarma para canal 2
int alarma_led_3 = 11;
int alarma_led_4 = 12;
// Variables para el circuito
float R1 = 200000.0;  //  R1 (200K) Valor de la resistencia R1 del divisor de tension
float R2 = 1000000.0; //  R2 (1M) Valor de la resistencia R2 del divisor de tension
// Variables de almacenamiento por canal 1.
int value5 = 0;      // Definimos la variable value
byte Pin_2 = 2;      // Nombre del pin 2
byte SelectorNP = 0; // Variable recibe dato de un comparador, para detectar si es negativo o positivo V.
float Vrms5 = 0;     // Variable para almacenar el calculo del valor RMS de fuente AC
float vout5 = 0.0;   // Definimos la variable Vout
float vin5 = 0.0;    // Definimos la variable Vin
// Variables de almacenamiento por canal 2
int value4 = 0;      // Definimos la variable value
byte Pin_1 = 1;      // Nombre del pin 2
byte SelectorNP1 = 0; // Variable recibe dato de un comparador, para detectar si es negativo o positivo V.
float Vrms4 = 0;     // Variable para almacenar el calculo del valor RMS de fuente AC
float vout4 = 0.0;   // Definimos la variable Vout
float vin4 = 0.0;    // Definimos la variable Vin
// Variables de almacenamiento por canal 3
int value2 = 0;      // Definimos la variable value
byte Pin_8 = 8;      // Nombre del pin 2
byte SelectorNP2 = 0; // Variable recibe dato de un comparador, para detectar si es negativo o positivo V.
float Vrms2 = 0;     // Variable para almacenar el calculo del valor RMS de fuente AC
float vout2 = 0.0;   // Definimos la variable Vout
float vin2 = 0.0;    // Definimos la variable Vin
// Variables de almacenamiento por canal 4
int value0 = 0;      // Definimos la variable value
byte Pin_0 = 0;      // Nombre del pin 2
byte SelectorNP0 = 0; // Variable recibe dato de un comparador, para detectar si es negativo o positivo V.
float Vrms0 = 0;     // Variable para almacenar el calculo del valor RMS de fuente AC
float vout0 = 0.0;   // Definimos la variable Vout
float vin0 = 0.0;    // Definimos la variable Vin
///////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // Modo serial:
  Serial.begin(9600); // Este debe coincidir con los demas dispositovos que conectamos

  // Declaracion de puertos de entrada
  pinMode(analogInput5, INPUT); // Activamos el input del pin analógico A5
  pinMode(analogInput4, INPUT); // Activamos el input del pin analógico A4
  pinMode(analogInput2, INPUT); // Activamos el input del pin analógico A2
  pinMode(analogInput0, INPUT); // Activamos el input del pin analógico A0

  // Declaracion de puertos de entrada para trabajar en modo digital
  pinMode(13, INPUT);     // Pin 13 como entrada  DC
  pinMode(Pin_2, INPUT);  // Pin2 como entrada
  pinMode(Pin_1, INPUT);  // Pin1 como entrada
  pinMode(Pin_8, INPUT); // Pin8 como entrada
  pinMode(Pin_0, INPUT); // Pin0 como entrada

  // Ajustes del display
  lcd.begin(84, 48); // Activamos LCD
  lcd.print("Voltmeter");
  lcd.setCursor(15, 1); // Posicionamos el cursor en el LCD
  lcd.print("4 channel");
  // Establecer Pines como salidas para los LEDS que  activan cuando el voltaje excede 20V y -20V
  pinMode(alarma_led_1, OUTPUT);
  pinMode(alarma_led_2, OUTPUT);
  pinMode(alarma_led_3, OUTPUT);
  pinMode(alarma_led_4, OUTPUT);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  // ************** PROGRAMACION PARA CANAL 1 **********************
  // Selectores Negativo/positivo de la senal DC
  SelectorNP = digitalRead(Pin_2); // leemos el pin digital 2 reconocido como PIN_2
  bool estadoPulsador = digitalRead(13); // leemos el pin digital 13, voltaje para seleccionar entre AC/DC
  // Establecer lecturas de los pines analogicos y guardarlos en las variables value_n
  value5 = analogRead(analogInput5); // Leemos el pin analógico A0
  // Voltage de salida/entrada para cada canal
  vout5 = (value5 * 5.0145) / 1024; // Cálculo para obtener el Vout
  vin5 = vout5 / (R2 / (R1 + R2));  // Cálculo para obtener Vin del divisor de tensión
  if (estadoPulsador == LOW)        // Condicional para entrar en el modo DC
  {
    if (SelectorNP == 0) // Si el voltaje de la fuente es positivo
    {                    // Condiciones de alarma de LED
      if (vin5 * 5 > 24)
      {
        digitalWrite(alarma_led_1, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_1, LOW);
      }
      // Para mostrar en pantalla
      lcd.setCursor(12, 2); // Posicionamos el cursor en el LCD
      lcd.print("V1= ");   // Mostramos el texto en el LCD
      lcd.print(vin5 * 5); // Mostramos el valor del Vin en el LCD
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vdc1: ");
      Serial.println(vin5 * 5);
      delay(500);
    }
    else
    {
      if (SelectorNP == 1) // Si el voltaje de la fuente es negativo
      {                    // Condiciones de alarma de LED
        if (vin5 * -5 < -24)
        {
          digitalWrite(alarma_led_1, HIGH);
        }
        else
        {
          digitalWrite(alarma_led_1, LOW);
        }
        // Para mostrar en pantalla
        lcd.setCursor(12, 2);  // Posicionamos el cursor en el LCD
        lcd.print("V1 ");     // Mostramos el texto en el LCD
        lcd.print(vin5 * -5); // Mostramos el valor del Vin en el LCD
        // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
        Serial.print("Vdc1: ");
        Serial.println(vin5 * -5);
        delay(500);
      }
    }
  }

  if (estadoPulsador == HIGH) // Condicional para entrar en el modo AC
  {
    // Buscamos el voltaje mas alto
    if (vin5 > Vrms5)
    {
      Vrms5 = vin5;
      if (Vrms5 > 24)
      {
        digitalWrite(alarma_led_1, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_1, LOW);
      }
      // Seteamos en la pantalla LCD
      lcd.setCursor(12, 2);            // Posicionamos el cursor en el LCD
      lcd.print("V1 RMS:");               // Mostramos el texto en el LCD
      lcd.print(5 * Vrms5 / sqrt(2)); // Al voltaje mas alto le colocamos la formula de Voltaje RMS -> Vp/sqrt(2)
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vrms1: ");
      Serial.println(Vrms5);
      delay(500);
    }
  }
  // ************** PROGRAMACION PARA CANAL 2 **********************
  // Selectores Negativo/positivo de la senal DC
  SelectorNP1 = digitalRead(Pin_1); // leemos el pin digital 2 reconocido como PIN_2
  bool estadoPulsador1 = digitalRead(13); // leemos el pin digital 13, voltaje para seleccionar entre AC/DC
  // Establecer lecturas de los pines analogicos y guardarlos en las variables value_n
  value4 = analogRead(analogInput4); // Leemos el pin analógico A0
  // Voltage de salida/entrada para cada canal
  vout4 = (value4 * 5.0145) / 1024; // Cálculo para obtener el Vout
  vin4 = vout4 / (R2 / (R1 + R2));  // Cálculo para obtener Vin del divisor de tensión
  if (estadoPulsador1 == LOW)        // Condicional para entrar en el modo DC
  {
    if (SelectorNP1 == 0) // Si el voltaje de la fuente es positivo
    {                    // Condiciones de alarma de LED
      if (vin4 * 5 > 24)
      {
        digitalWrite(alarma_led_2, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_2, LOW);
      }
      // Para mostrar en pantalla
      lcd.setCursor(12, 3); // Posicionamos el cursor en el LCD
      lcd.print("V2= ");   // Mostramos el texto en el LCD
      lcd.print(vin4 * 5); // Mostramos el valor del Vin en el LCD
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vdc1: ");
      Serial.println(vin4 * 5);
      delay(500);
    }
    else
    {
      if (SelectorNP1 == 1) // Si el voltaje de la fuente es negativo
      {                    // Condiciones de alarma de LED
        if (vin4 * -5 < -24)
        {
          digitalWrite(alarma_led_2, HIGH);
        }
        else
        {
          digitalWrite(alarma_led_2, LOW);
        }
        // Para mostrar en pantalla
        lcd.setCursor(12, 3);  // Posicionamos el cursor en el LCD
        lcd.print("V2 ");     // Mostramos el texto en el LCD
        lcd.print(vin4 * -5); // Mostramos el valor del Vin en el LCD
        // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
        Serial.print("Vdc1: ");
        Serial.println(vin4 * -5);
        delay(500);
      }
    }
  }

  if (estadoPulsador1 == HIGH) // Condicional para entrar en el modo AC
  {
    // Buscamos el voltaje mas alto
    if (vin4 > Vrms4)
    {
      Vrms4 = vin4;
      if (Vrms4 > 24)
      {
        digitalWrite(alarma_led_2, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_2, LOW);
      }
      // Seteamos en la pantalla LCD
      lcd.setCursor(12, 3);            // Posicionamos el cursor en el LCD
      lcd.print("V2 RMS:");               // Mostramos el texto en el LCD
      lcd.print(5 * Vrms4 / sqrt(2)); // Al voltaje mas alto le colocamos la formula de Voltaje RMS -> Vp/sqrt(2)
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vrms2: ");
      Serial.println(Vrms4);
      delay(500);
    }
  }
  // ************** PROGRAMACION PARA CANAL 3 **********************
  // Selectores Negativo/positivo de la senal DC
  SelectorNP2 = digitalRead(Pin_8); // leemos el pin digital 2 reconocido como PIN_2
  bool estadoPulsador2 = digitalRead(13); // leemos el pin digital 13, voltaje para seleccionar entre AC/DC
  // Establecer lecturas de los pines analogicos y guardarlos en las variables value_n
  value2 = analogRead(analogInput2); // Leemos el pin analógico A0
  // Voltage de salida/entrada para cada canal
  vout2 = (value2 * 5.0145) / 1024; // Cálculo para obtener el Vout
  vin2 = vout2 / (R2 / (R1 + R2));  // Cálculo para obtener Vin del divisor de tensión
  if (estadoPulsador2 == LOW)        // Condicional para entrar en el modo DC
  {
    if (SelectorNP2 == 0) // Si el voltaje de la fuente es positivo
    {                    // Condiciones de alarma de LED
      if (vin2 * 5 > 24)
      {
        digitalWrite(alarma_led_3, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_3, LOW);
      }
      // Para mostrar en pantalla
      lcd.setCursor(12, 4); // Posicionamos el cursor en el LCD
      lcd.print("V3= ");   // Mostramos el texto en el LCD
      lcd.print(vin2 * 5); // Mostramos el valor del Vin en el LCD
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vdc1: ");
      Serial.println(vin2 * 5);
      delay(500);
    }
    else
    {
      if (SelectorNP2 == 1) // Si el voltaje de la fuente es negativo
      {                    // Condiciones de alarma de LED
        if (vin2 * -5 < -24)
        {
          digitalWrite(alarma_led_3, HIGH);
        }
        else
        {
          digitalWrite(alarma_led_3, LOW);
        }
        // Para mostrar en pantalla
        lcd.setCursor(12, 4);  // Posicionamos el cursor en el LCD
        lcd.print("V3 ");     // Mostramos el texto en el LCD
        lcd.print(vin2 * -5); // Mostramos el valor del Vin en el LCD
        // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
        Serial.print("Vdc1: ");
        Serial.println(vin2 * -5);
        delay(500);
      }
    }
  }

  if (estadoPulsador2 == HIGH) // Condicional para entrar en el modo AC
  {
    // Buscamos el voltaje mas alto
    if (vin2 > Vrms2)
    {
      Vrms2 = vin2;
      if (Vrms2 > 24)
      {
        digitalWrite(alarma_led_3, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_3, LOW);
      }
      // Seteamos en la pantalla LCD
      lcd.setCursor(12, 4);            // Posicionamos el cursor en el LCD
      lcd.print("V3 RMS:");               // Mostramos el texto en el LCD
      lcd.print(5 * Vrms2 / sqrt(2)); // Al voltaje mas alto le colocamos la formula de Voltaje RMS -> Vp/sqrt(2)
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vrms3: ");
      Serial.println(Vrms2);
      delay(500);
    }
  }
  // ************** PROGRAMACION PARA CANAL 4 **********************
   // Selectores Negativo/positivo de la senal DC
  SelectorNP0 = digitalRead(Pin_0); // leemos el pin digital 2 reconocido como PIN_2
  bool estadoPulsador0 = digitalRead(13); // leemos el pin digital 13, voltaje para seleccionar entre AC/DC
  // Establecer lecturas de los pines analogicos y guardarlos en las variables value_n
  value0 = analogRead(analogInput0); // Leemos el pin analógico A0
  // Voltage de salida/entrada para cada canal
  vout0 = (value0 * 5.0145) / 1024; // Cálculo para obtener el Vout
  vin0 = vout0 / (R2 / (R1 + R2));  // Cálculo para obtener Vin del divisor de tensión
  if (estadoPulsador0 == LOW)        // Condicional para entrar en el modo DC
  {
    if (SelectorNP0 == 0) // Si el voltaje de la fuente es positivo
    {                    // Condiciones de alarma de LED
      if (vin0 * 5 > 24)
      {
        digitalWrite(alarma_led_4, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_4, LOW);
      }
      // Para mostrar en pantalla
      lcd.setCursor(12, 5); // Posicionamos el cursor en el LCD
      lcd.print("V4= ");   // Mostramos el texto en el LCD
      lcd.print(vin0 * 5); // Mostramos el valor del Vin en el LCD
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vdc1: ");
      Serial.println(vin0 * 5);
      delay(500);
    }
    else
    {
      if (SelectorNP0 == 1) // Si el voltaje de la fuente es negativo
      {                    // Condiciones de alarma de LED
        if (vin0 * -5 < -24)
        {
          digitalWrite(alarma_led_4, HIGH);
        }
        else
        {
          digitalWrite(alarma_led_4, LOW);
        }
        // Para mostrar en pantalla
        lcd.setCursor(12, 5);  // Posicionamos el cursor en el LCD
        lcd.print("V4 ");     // Mostramos el texto en el LCD
        lcd.print(vin0 * -5); // Mostramos el valor del Vin en el LCD
        // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
        Serial.print("Vdc1: ");
        Serial.println(vin0 * -5);
        delay(500);
      }
    }
  }

  if (estadoPulsador0 == HIGH) // Condicional para entrar en el modo AC
  {
    // Buscamos el voltaje mas alto
    if (vin0 > Vrms0)
    {
      Vrms0 = vin0;
      if (Vrms0 > 24)
      {
        digitalWrite(alarma_led_4, HIGH);
      }
      else
      {
        digitalWrite(alarma_led_4, LOW);
      }
      // Seteamos en la pantalla LCD
      lcd.setCursor(12, 5);            // Posicionamos el cursor en el LCD
      lcd.print("V4 RMS:");               // Mostramos el texto en el LCD
      lcd.print(5 * Vrms0 / sqrt(2)); // Al voltaje mas alto le colocamos la formula de Voltaje RMS -> Vp/sqrt(2)
      // Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vrms4: ");
      Serial.println(Vrms0);
      delay(500);
    }
  }
  // ********************************PRUEBA****************************************
  // Esto de aqui abajo es meramente de prueba, para la comunicacion serial se deben meter en los condicionales del switch AC\DC (yo lo hago)
  Serial.print("V: ");
  Serial.println(vin5);
} // Final de void loop()

