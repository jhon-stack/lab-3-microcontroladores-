---
__Generador del CSV__\
Archivos necesarios:


- __data_saver.py__
- __virtualport.sh__
- __AC.simu__
- __lab_3.ino__

Para ejecutar el archivo csv se deben seguir las siguientes instrucciones:
- Tener abierto el archivo de simulacion  AC.simu en el cual se encuntra el micontrolador con las entradas y salidas digitales conectadas a circuitos externos.
- Compilar y extraer el firmware de lab_3.ino y cargarlo dentro del microcontrolador Arduino Uno.
- Dentro de las opciones que presenta la tarjeta abrir el monitor serial (_open serial monitor_) y el puerto (_open serial port).
- Asegurarse de estar en el directorio de source dentro del repositorio.
- Escribir el siguiente comando: source virtualport.sh.
- inmediantamente se emularan los puertos virtuales, para configurar el puerto serial de la tarjeta es necesario ir al archivo dentro de ese mismo directorio llamado sokat_ouput.txt y escibir la segunda linea para el nombre del pueeto. Dicho archivo guarda el output del comando socat para que sea leido mas facilmente por el script de python data_saver.py y con esto le evita al usuario ingresar el nombre del puerto manualmente.
- Una vez ingresado el nombre del puerto en la configuracion serial en simulide, lo siguiente es darle play a la simulacion.
- Seguido, en otra terminal, ejecutar el archivo de python con el siguiente comando: python3 data_saver.py. Este comando correra y en la misma terminal mostrara las lecturas seriales en tiempo real, basta con cancelar el script para tener una salida llamada data-saver.csv el cual almecena los valores mostrados anterioemente.