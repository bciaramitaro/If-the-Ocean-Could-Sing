#include <ADCTouch.h>

#define TOUCHPIN A0
#define TOUCHPIN2 A1
#define TOUCHPIN3 A2
#define TOUCHPIN4 A3
#define TOUCHPIN5 A4

// set the touch sensor resolution: 
// higher means more stable results, at the cost of higher processing times
#define RESOLUTION 100

#define SMOOTH 100 // determine how many readings are stored for smoothing
float multiplier = 1.2; // determine when the sensor is understood as "ON"

int previousReadings[SMOOTH]; // smooth data a little: the last readings
int currentIndex = 0; // used for cycling through the array
int reading; // the latest reading
int state = 0;

int previousReadings2[SMOOTH]; // smooth data a little: the last readings
int currentIndex2 = 0; // used for cycling through the array
int reading2; // the latest reading
int state2 = 0;

int previousReadings3[SMOOTH]; // smooth data a little: the last readings
int currentIndex3 = 0; // used for cycling through the array
int reading3; // the latest reading
int state3 = 0;

int previousReadings4[SMOOTH]; // smooth data a little: the last readings
int currentIndex4 = 0; // used for cycling through the array
int reading4; // the latest reading
int state4 = 0;

int previousReadings5[SMOOTH]; // smooth data a little: the last readings
int currentIndex5 = 0; // used for cycling through the array
int reading5; // the latest reading
int state5 = 0;


// calculate the average of the previous readings
int average(){
  unsigned long sum = 0;
  for(int i = 0; i < SMOOTH; i++){
    sum += previousReadings[i];
  }
  return sum / SMOOTH;
}

int average2(){
  unsigned long sum = 0;
  for(int i = 0; i < SMOOTH; i++){
    sum += previousReadings2[i];
  }
  return sum / SMOOTH;
}


int average3(){
  unsigned long sum = 0;
  for(int i = 0; i < SMOOTH; i++){
    sum += previousReadings3[i];
  }
  return sum / SMOOTH;
}

int average4(){
  unsigned long sum = 0;
  for(int i = 0; i < SMOOTH; i++){
    sum += previousReadings4[i];
  }
  return sum / SMOOTH;
}

int average5(){
  unsigned long sum = 0;
  for(int i = 0; i < SMOOTH; i++){
    sum += previousReadings5[i];
  }
  return sum / SMOOTH;
}


void setup() {
  Serial.begin(9600); // serial communication
  pinMode(13,OUTPUT);
  // fill the [previousReaings] array with readings
  for(int i = 0; i < SMOOTH; i++){
    previousReadings[i] = ADCTouch.read(TOUCHPIN, RESOLUTION);
    previousReadings2[i] = ADCTouch.read(TOUCHPIN2, RESOLUTION);
    previousReadings3[i] = ADCTouch.read(TOUCHPIN3, RESOLUTION);
    previousReadings4[i] = ADCTouch.read(TOUCHPIN3, RESOLUTION);
    previousReadings5[i] = ADCTouch.read(TOUCHPIN3, RESOLUTION);
  }
  

}

void loop() {
  
  reading = ADCTouch.read(TOUCHPIN, RESOLUTION); // read the sensor$
  reading2 = ADCTouch.read(TOUCHPIN2, RESOLUTION); // read the sensor
  reading3 = ADCTouch.read(TOUCHPIN3, RESOLUTION); // read the sensor
  reading4 = ADCTouch.read(TOUCHPIN4, RESOLUTION); // read the sensor
  reading5 = ADCTouch.read(TOUCHPIN5, RESOLUTION); // read the sensor
  
  //Serial.println(reading);
  
  // check if 1st pin triggered
  if(reading > average() * multiplier){
     digitalWrite(13, HIGH);
     state = 1;
  }else{
    digitalWrite(13, LOW);
    state = 0;
    previousReadings[currentIndex] = reading;
    currentIndex++;
    
    if(currentIndex >= SMOOTH){
      currentIndex = 0;
    }
 }
 
// check if 2nd pin triggered 
 if(reading2 > average2() * multiplier){
     state2 = 1;
  }else{
    state2 = 0;
    previousReadings2[currentIndex] = reading2;
    currentIndex2++;
    
    if(currentIndex2 >= SMOOTH){
      currentIndex2 = 0;
    }
 }  
   
    
// check if 3rd pin triggered 
 if(reading3 > average3() * multiplier){
     state3 = 1;
  }else{
    state3 = 0;
    previousReadings3[currentIndex] = reading3;
    currentIndex3++;
    
    if(currentIndex3 >= SMOOTH){
      currentIndex3 = 0;
    }
 }  

// check if 4th pin triggered 
 if(reading4 > average4() * multiplier){
     state4 = 1;
  }else{
    state4 = 0;
    previousReadings4[currentIndex] = reading4;
    currentIndex4++;
    
    if(currentIndex4 >= SMOOTH){
      currentIndex4 = 0;
    }
 }  
   
  // check if 5th pin triggered 
 if(reading5 > average5() * multiplier){
     state5 = 1;
  }else{
    state5 = 0;
    previousReadings5[currentIndex] = reading5;
    currentIndex5++;
    
    if(currentIndex5 >= SMOOTH){
      currentIndex5 = 0;
    }
 }  
    
   
   Serial.print(state);
   Serial.print(" "); // put space and not a , or . - this is the only way for numbers to correctly feed into max audio channels 
   Serial.print(state2);
   Serial.print(" ");
   Serial.print(state3);
   Serial.print(" ");
   Serial.print(state4);
   Serial.print(" ");
   Serial.println(state5); //ln = next line, for last data

}
