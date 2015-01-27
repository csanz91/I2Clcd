#include <Wire.h>

#define ADDR_SERVER	1
#define ADDR_LCD	2
#define NUM_DATA	5						//Num de datos que almacenara el array

//Definimos la posicion de cada dato en el array
#define data1	0
#define data2	1

float data[NUM_DATA];							//Array de datos

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

    delay(1000);

}

//Llama al I2C server para que le devuelva el array de datos
void askForData(){

	byte data_received[4];

	//Hace una llamada al slave por cada dato que se quiere obtener
	for(int x=0; x<NUM_DATA; x++){
	    Wire.requestFrom(ADDR_SERVER, 4); 						//Pide 6 bytes a la direccion del servidor I2C

	    //Lee los cuatro bytes de los que se forma el float y los vuelve a unir
    	int i = 0;
	    while(Wire.available())    // slave may send less than requested
	    { 
	    	data_received[i] = Wire.read(); // receive a byte as character  
	    	i++;
	    }
	    //A union datatypes makes the byte and float elements share the same piece of memory, which enables conversion from a byte array to a float possible
	    union float_tag {byte data_b[4]; float data_fval;} float_Union;    
	    float_Union.data_b[0] = data_received[0];
	    float_Union.data_b[1] = data_received[1];
	    float_Union.data_b[2] = data_received[2];
	    float_Union.data_b[3] = data_received[3];    
    	data[x] = float_Union.data_fval;
	}
}
