#include <LedControl.h>
/*https://playground.arduino.cc/Main/LedControl/#Seg7Control*/

int incomingByte = 0;
int number=0;
  /*12 DIN, 11 CLK, 10 CS*/
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);

  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,5);
  /* and clear the display */
  lc.clearDisplay(0);
}

/*block 0 for right block and 1 for left block*/
void printNumber(int v, long int block) {
    int ones;
    int tens;
    int hundreds;
    long int thousands;
    boolean negative;  
    int i;

    for(i=0;i<3;i++)
    {
      lc.setChar(0,i+(block*4),' ',false);
    }

    if(block>1){
      //invalid value
      return;
    }
      
    if(v < -9999 || v > 9999) 
       return;
    /*if(v<0) {
        negative=true;
        v=v*-1;
    }*/
    ones=v%10;
    v=v/10;
    tens=v%10;
    v=v/10;
    hundreds=v%10; 
    v=v/10;
    thousands=v%10;   
    if(negative) {
       //print character '-' in the leftmost column 
       lc.setChar(0,3+(block*4),'-',false);
    }
    else {
       //print a blank in the sign column
       lc.setChar(0,3+(block*4),' ',false);
    }
    //Now print the number digit by digit
    if(0!=thousands){
      lc.setDigit(0,3+(block*4),(byte)thousands,false);
    }
    if(0!=hundreds || 0!=thousands){
      lc.setDigit(0,2+(block*4),(byte)hundreds,false);
    }
    if(0!=tens || 0!=hundreds || 0!=thousands){
      lc.setDigit(0,1+(block*4),(byte)tens,false);
    }
    lc.setDigit(0,0+(block*4),(byte)ones,false);
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0.
 */
void writeArduinoOn7Segment(byte val) {
  lc.setChar(0,0,val,false);
  //delay(delaytime);
  //lc.setChar(0,4,val+1,false);
}

void chenillardFreebox(int waitingTime)
{
  static int i=0;
  i++;
  lc.setRow(0,3,(byte)B00000110); //1+2
  lc.setRow(0,2,(byte)B00000000); //init the display
  lc.setRow(0,1,(byte)B00000000); //init the display
  lc.setRow(0,0,(byte)B00000000); //init the display
  delay(waitingTime);
  lc.setRow(0,3,(byte)B01000010); //1+6
  delay(waitingTime);
  lc.setRow(0,3,(byte)B01000000); //6
  lc.setRow(0,2,(byte)B01000000); //6
  delay(waitingTime);
  lc.setRow(0,3,(byte)B00000000); //off
  lc.setRow(0,2,(byte)B01000000); //6
  lc.setRow(0,1,(byte)B01000000); //6
  delay(waitingTime);
  lc.setRow(0,2,(byte)B00000000); //off
  lc.setRow(0,1,(byte)B01000000); //6
  lc.setRow(0,0,(byte)B01000000); //6
  delay(waitingTime);
  lc.setRow(0,1,(byte)B00000000); //off
  lc.setRow(0,0,(byte)B00110000); //6+5 , top rigth angle
  delay(waitingTime);
  lc.setRow(0,0,(byte)B00110000); //5+4
  delay(waitingTime);
  lc.setRow(0,0,(byte)B00011000); //4+3
  delay(waitingTime);
  lc.setRow(0,0,(byte)B00001000); //3
  lc.setRow(0,1,(byte)B00001000); //3
  delay(waitingTime);
  lc.setRow(0,0,(byte)B00000000); //off
  lc.setRow(0,1,(byte)B00001000); //3
  lc.setRow(0,2,(byte)B00001000); //3
  delay(waitingTime);
  lc.setRow(0,1,(byte)B00000000); //off
  lc.setRow(0,2,(byte)B00001000); //3
  lc.setRow(0,3,(byte)B00001000); //3
  delay(waitingTime);
  lc.setRow(0,2,(byte)B00000000); //off
  lc.setRow(0,3,(byte)B00001100); //3+2
  delay(waitingTime);
}

void blinkFreebox(int waitingTime)
{
  int i=0;
  for(i=0;i<3;i++){
    lc.setRow(0,3,(byte)B01001110);
    lc.setRow(0,2,(byte)B01001000);
    lc.setRow(0,1,(byte)B01001000);
    lc.setRow(0,0,(byte)B01111000);
    delay(waitingTime);
    lc.setRow(0,3,(byte)B00000000); //off
    lc.setRow(0,2,(byte)B00000000); //off
    lc.setRow(0,1,(byte)B00000000); //off
    lc.setRow(0,0,(byte)B00000000); //off
    delay(waitingTime);
  }
}

void sweepFreebox(int waitingTime)
{
    lc.setRow(0,3,(byte)B01000000); //6
    lc.setRow(0,2,(byte)B01000000); //6
    lc.setRow(0,1,(byte)B01000000); //6
    lc.setRow(0,0,(byte)B01000000); //6
    delay(waitingTime);
    lc.setRow(0,3,(byte)B00000001); //0
    lc.setRow(0,2,(byte)B00000001); //0
    lc.setRow(0,1,(byte)B00000001); //0
    lc.setRow(0,0,(byte)B00000001); //0
    delay(waitingTime);
    lc.setRow(0,3,(byte)B00001000); //3
    lc.setRow(0,2,(byte)B00001000); //3
    lc.setRow(0,1,(byte)B00001000); //3
    lc.setRow(0,0,(byte)B00001000); //3
    delay(waitingTime);
    lc.setRow(0,3,(byte)B00000001); //0
    lc.setRow(0,2,(byte)B00000001); //0
    lc.setRow(0,1,(byte)B00000001); //0
    lc.setRow(0,0,(byte)B00000001); //0
    delay(waitingTime);
    lc.setRow(0,3,(byte)B01000000); //6
    lc.setRow(0,2,(byte)B01000000); //6
    lc.setRow(0,1,(byte)B01000000); //6
    lc.setRow(0,0,(byte)B01000000); //6
    delay(waitingTime);
    lc.setRow(0,3,(byte)B00000000); //off
    lc.setRow(0,2,(byte)B00000000); //off
    lc.setRow(0,1,(byte)B00000000); //off
    lc.setRow(0,0,(byte)B00000000); //off
}


void loop() {
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();

    if('a' == incomingByte)
    {
      chenillardFreebox(100);
    }else if('b' == incomingByte)
    {
      blinkFreebox(200);
    }else if('c' == incomingByte)
    {
      sweepFreebox(200);
    }else{
      incomingByte -='0';
      // say what you got:
      Serial1.print("I received: ");
      Serial1.println(incomingByte, DEC);
      writeArduinoOn7Segment(incomingByte);
  
      number = (number+incomingByte)%10000;
      printNumber(number,1);
    }
  }
    
}
