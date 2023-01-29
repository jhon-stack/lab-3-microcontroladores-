/*Universidad de Costa Rica
IE-0624 Laboratorio de Microcontroladores
Prof: Marco Villalta Fallas
Estudiantes: Jhon Gaitan Aguilar B73059 y Alex Varela 
Laboratorio 3
Voltimetro
Ciclo: III-2022
*/
////////////////////////////////////////////////////////////////////////////////
//Includes:
//Nota: Agregar esta libreria pudo hacerse agregando el zip dentro del IDE
//      Yo lo hice agregando descomprimiendo ese zip y agregando manualmente el folder en el path </usr/share/arduino/libraries/>
#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.h>
#include </usr/share/arduino/libraries/pcd8544-master/PCD8544.cpp>
//Puede que hagan falta mas Includes.
////////////////////////////////////////////////////////////////////////////////
//Con respecto a la libreroia PCD8544, para que funciones se deben conectar a los pines del Arduino 1 (digital) de la siguiente manera:
/*
  No se exactamente donde esta definido esto, creo que es en PCD8544.cpp | PCD8544.h. Incluso se podrian cambiar
  *RST  -> PIN[6]
  *CS   -> PIN[7]
  *CLK  -> PIN[3]
  *DIN  -> PIN[4]
  *D/C  -> PIN[5]

*/ 

static PCD8544 lcd;//

void setup(){
  //Analog I/O's

  //Digital I/O's 
  pinMode(8, OUPUT);//Pin del LED que se activa si el voltaje menor a -20V o superior a 20V
  lcd.begin(84, 48);// PCD8544-compatible displays may have a different resolution...

  //Serial communication
  
  }

void loop(){
 
}