import serial
import csv
import re
import os

def virtual_port():

    directorio_actual = os.getcwd()

    with open(directorio_actual+"/sokat_ouput.txt",) as f:
        buffer_file = f.readline().rstrip()
        matches = re.search("/dev/pts/\d+",buffer_file)
        '''print(matches)
        print("su obejeto es", matches)
        print(matches[0])'''
        objeto = matches[0]
        return objeto
#var = '/dev/pts/3'
var  = str(virtual_port())
#serializamos
#En port ponemos el valor que se obtiene al ejeciutar el script virtualport.sh
ser = serial.Serial(port =  str(var),baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS) 
#ser = serial.Serial(port = '/dev/pts/3',baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS) 

f= open("data_saver.csv",'w') 
writer = csv.writer(f) 

while True:
    value = ser.readline().decode().split(' ')
    writer.writerow(value)#Escribir en la fila el valor obetenido
    print(value)#Imprime en pantalla 


f.close()
