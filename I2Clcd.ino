#include <Wire.h>

#define ADDR_SERVER	1
#define ADDR_LCD	2
#define NUM_DATA	5						//Num de datos que almacenara el array

//Definimos la posicion de cada dato en el array
#define data1	0
#define data2	1

int data[NUM_DATA];							//Array de datos

void setup() {
	Wire.begin(ADDR_LCD);       			//Nos unimos al bus I2C con la direccion dada
 	Serial.begin(9600);  					
}

void loop() {
	askForData();
	
	//Devuelve los datos contenidos en el array
	for(int i=0; i<NUM_DATA; i++){
	    Serial.println(data[i]);
	}
	
	Serial.println();
    delay(1000);

}

//Llama al I2C server para que le devuelva el array de datos
void askForData(){

	//Hace una llamada al slave por cada dato que se quiere obtener
	for(int x=0; x<NUM_DATA; x++){
	    Wire.requestFrom(ADDR_SERVER, 6); 						//Pide 6 bytes a la direccion del servidor I2C

	    //Lee los seis digitos por separado y los recompone
    	while(Wire.available())
   		{ 
    		int output=0;
    		for(int i=5; i>=0; i--){
    			char data_read=Wire.read()-'0';					//Los datos se leen como caracter y los pasamos a enteros
    	 		output = output + potenciaDiez(i)*data_read;
    	 		
    		}
    		data[x]=output;
    		
    	}
	}
}

//Devuelve diez a la potencia pasada como parametro. La funcion pow() utiliza un float como base y usandola aqui genera pequeños errores
int potenciaDiez(int x){
	int result=1;
	for(int i=0; i<x; i++){
	    result=result*10;
	}
	return result;
}

