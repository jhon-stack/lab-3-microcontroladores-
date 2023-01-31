'''
Este programa guarda datos en el csv despues de ser cerrado, mientras no se cierre no guardara nada.
Falta corregirle eso.
'''
import serial
import csv
#serializamos
#En port ponemos el valor que se obtiene al ejeciutar el script virtualport.sh
ser = serial.Serial(port = '/dev/pts/12',baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS) 

f= open("data_saver.csv",'w') 
writer = csv.writer(f) 

while True:
    value = ser.readline().decode().split(' ')
    writer.writerow(value)#Escribir en la fila el valor obetenido
    print(value)#Imprime en pantalla 


f.close()
