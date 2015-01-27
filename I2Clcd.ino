#include <Wire.h>

#define ADDR_SERVO	1
#define ADDR_LCD	2
#define NUM_DATA	1

#define data1	0
#define data2	1

int data[NUM_DATA];

void setup() {
	Wire.begin(ADDR_LCD);        // join i2c bus (address optional for master)
 	Serial.begin(9600);  // start serial for output
}

void loop() {
	
	for(int x=0; x<NUM_DATA; x++){
	    Wire.requestFrom(ADDR_SERVO, 4); //Ask for 5 bytes
    	while(Wire.available())
   		{ 
    		int output=0;

    		//for(int i=4; i>=0; i--){
    			char data_read=Wire.read()-'0';
    	 		//output = output + potenciaDiez(i)*data_read;
    	 		
    	 		    Serial.println(data_read);
    	 	//	}
    	 		
    		//}
    		data[x]=output;
    		
    	}
	}
	
	for(int i=0; i<NUM_DATA; i++){
	    //Serial.println(data[i]);
	}
	Serial.println();
    delay(1000);

}

int potenciaDiez(int x){
	int result=1;
	for(int i=0; i<x; i++){
	    result=result*10;
	}
	return result;
}

