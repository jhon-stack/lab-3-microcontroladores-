//Votímetro digital DC 0-30V con Arduino

#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.h>
#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.cpp>

static PCD8544 lcd;

int analogInput = 0; //Definimos el pin analógico A0 para la lectura del voltaje
int alarma_led = 8;
float vout = 0.0; //Definimos la variable Vout
float vin = 0.0; //Definimos la variable Vin
float R1 = 200000.0; //  R1 (200K) Valor de la resistencia R1 del divisor de tensión
float R2 = 1000000.0; //  R2 (1M) Valor de la resistencia R2 del divisor de tención
int value = 0;//Definimos la variable value

void setup(){//////////////////////////////////////////////////////////////////////////////
  //Modo serial:
  serial.begin(9600);    
   pinMode(analogInput, INPUT); //Activamos el input del pin analógico A0
  // PCD8544-compatible displays may have a different resolution...
  lcd.begin(84, 48);  // Activamos LCD
  lcd.print("DC VOLTIMETRO"); //Mostramos en el LCD este mensaje al inicio
  //LED de color rojo que se activa cuando el voltaje excede 20V y -20V
  pinMode(alarma_led, OUTPUT);
}

void loop(){//////////////////////////////////////////////////////////////////////////////
  value = analogRead(analogInput); //Leemos el pin analógico A0
  vout = (value * 5.0145) / 1024; // Cálculo para obtener el Vout 
  vin = vout / (R2/(R1+R2)); // Cálculo para obtener Vin del divisor de tensión
    if (vin<0.09)
    { //Si la lectura de Vin es menor que 0.09V le decimos que nos muestre 0
      vin=0.0; 
    }
  Serial.print(vout);
  Serial.println(" V");   
lcd.setCursor(0, 1); //Posicionamos el cursor en el LCD
lcd.print("INPUT V= ");//Mostramos el texto en el LCD
lcd.print(vin*5);//Mostramos el valor del Vin en el LCD
delay(500); //Se hace una lectura de voltaje cada 500 ms
}
