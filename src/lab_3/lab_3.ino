/*
Universidad de Costa Rica
Escuela de Ingenieria Electrica
IE-0624 Laboratorio de Microcontroladores
Laboratorio 3: Voltimetro de 4 canales con Arduino Uno
Elaborado por:  Jhon Gaitan Aguilar B73059
                Alex Varela
III-2022
*/

#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.h>
#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.cpp>
#include <math.h>
#include <stdio.h>

//Declaracion de Hardware y variables necesarias
static PCD8544 lcd;
int analogInput =   0; //Definimos el pin analógico A0 para la lectura del voltaje
//LEDS de aviso
int alarma_led_1=   9;
int alarma_led_2=   10;
int alarma_led_3=   11;
int alarma_led_4=   12;
int state_led_1 =   0;
int state_led_2 =   0;
int state_led_3 =   0;
int state_led_4 =   0;
float vout      =   0.0; //Definimos la variable Vout
float vin       =   0.0; //Definimos la variable Vin
float R1        =   200000.0; //  R1 (200K) Valor de la resistencia R1 del divisor de tensión
float R2        =   1000000.0; //  R2 (1M) Valor de la resistencia R2 del divisor de tención
int value       =   0;//Definimos la variable value
byte SelectorNP =   0; // Variable recibe el Dato leido del Pin digital 2
byte Pin_2      =   2; // Nombre del pin 2
float Vrms      =   0; // Variable para almacenar el calculo del valor RMS de fuente AC
long duration;  

///////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  //Modo serial:
  Serial.begin(9600);//Este debe coincidir con los demas dispositovos que conectamos
  //Declaracion de puertos de entrada    
  pinMode(analogInput, INPUT); //Activamos el input del pin analógico A0


  //declaracion de puertos de salida digitales
  pinMode(Pin_2, INPUT); // Pin como entrada digital
  pinMode(13, INPUT); // Pin 8 como entrada digital


  //Ajustes del display
  lcd.begin(84, 48);  // Activamos LCD
  lcd.print("4 channel voltimeter"); 


  //Establecer Pines como salidas para los LEDS que  activan cuando el voltaje excede 20V y -20V
  pinMode(alarma_led_1, OUTPUT);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
  //Selectores Negativo/positivo de la senal DC
  SelectorNP = digitalRead(Pin_2); // leemos el pin digital 3 reconocido como PIN_3

  //Pulsador Para seleccionar entre AC/DC
  bool estadoPulsador = digitalRead(13); // leemos el pin digital 8 reconocido como PIN_8  

  //Establecer lecturas de los pines analogicos y guardarlos en las variables value_n
  value = analogRead(analogInput); //Leemos el pin analógico A0
  
  //Voltage de salida/entrada para cada canal
  vout = (value * 5.0145) / 1024; // Cálculo para obtener el Vout 
  vin = vout / (R2/(R1+R2)); // Cálculo para obtener Vin del divisor de tensión

  //Condicional para entrar en el modo DC
  if (estadoPulsador == LOW) 
  { // Si es operar modo DC

    if (SelectorNP==0) 
    {   
          if (vin*5 > 24)
          {
            digitalWrite(alarma_led_1, HIGH);
          }     
          else
          {
            digitalWrite(alarma_led_1, LOW);
          }
          lcd.setCursor(0, 2); //Posicionamos el cursor en el LCD
          lcd.print("V1= ");//Mostramos el texto en el LCD
          lcd.print(vin*5);//Mostramos el valor del Vin en el LCD 
          //Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
          Serial.print("Vdc1: ");
          Serial.println(vin*5);
          delay(500); 
        
    }
    else
    {
      if (SelectorNP==1) 
      {
        if (vin*-5 < -24)
        {
          digitalWrite(alarma_led_1, HIGH);
        }     
        else
        {
            digitalWrite(alarma_led_1, LOW);
        }
        lcd.setCursor(0, 2); //Posicionamos el cursor en el LCD
        lcd.print("V1 ");//Mostramos el texto en el LCD
        lcd.print(vin*-5);//Mostramos el valor del Vin en el LCD
        //Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
        Serial.print("Vdc1: ");
        Serial.println(vin*-5);
        delay(500);
      }
     }
     
  }  
   
  if (estadoPulsador == HIGH) 
  { 
    //Buscamos el voltaje mas alto
    if(vin > Vrms)
    {
      Vrms = vin;
      //Seteamos en la pantalla LCD 
      lcd.setCursor(0, 2); //Posicionamos el cursor en el LCD
      lcd.print("V1 ");//Mostramos el texto en el LCD
      lcd.print(5*Vrms/sqrt(2));//Al voltaje mas alto le colocamos la formula de Voltaje RMS -> Vp/sqrt(2)
      //Pasamos al serial monitor que eventualmente lo pasaremos a un archivo csv
      Serial.print("Vrms1: ");
      Serial.println(Vrms);
      delay(500);
    }          
  }
  //Esto de aqui abajo es meramente de prueba, para la comunicacion serial se deben meter en los condicionales del switch AC\DC (yo lo hago)
  Serial.print("V: ");
  Serial.println(vin);
  }//Final de void loop()
        
