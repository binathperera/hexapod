
#include <IRremote.h>

/*Arduino Spider bot(6 leged HEXABOT)
 ------------------
 * Author:Binath Perera
 * This code that I have written is used on this spider for 4 movements(Forward,Backward,turn right and turn left).
 * Operates by reading inputs from a remote controller. 
 * 
 * The legs are labled as,
 * 1=====2
 * 3=====4
 * 5=====6
 * This spider's legs are categorized into 2 sets as set1(legs 1,4 and 5) and set2(legs 2,3 and 6) that operates at different times to support the spiders movements.
 * Each leg is programed to hold 3 servo motors.The servos in each leg are connected to the pins as,
 * leg#  pins
 *  1  ->0,1,2(Board 1)
 *  2  ->0,1,2(Board 2)
 *  3  ->4,5,6(Board 1)
 *  4  ->4,5,6(Board 2)
 *  5  ->8,9,10(Board 1)
 *  6  ->8,9,10(Board 2)
 * Furthermore a LCD display is used as the spider's head.
*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVOMIN 130
#define SERVOMAX 575
#define STEPLENGTH 20 //Length of step from the starting position of 90 degrees

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

Adafruit_PWMServoDriver d1=Adafruit_PWMServoDriver(0x41); //The left legs of the spider are connected to this board(legs 2,4 and 6).
Adafruit_PWMServoDriver d2=Adafruit_PWMServoDriver(0x40); //The right legs of the spider are connected to this board(legs 1,3 and 5).

boolean L1_stat;//If leg 1 is in its original position
boolean L2_stat;//If leg 2 is in its original position
boolean L5_stat;//If leg 5 is in its original position
boolean L6_stat;//If leg 6 is in its original position

int feetPlacementAngle=90;
int legPlacementAngle=90;
const int L1_angle=120; //Starting position of leg 1
const int L2_angle=60; //Starting Position of leg 2
//Legs 4 and 5 are positioned to be at 90 degrees
const int L5_angle=60;//Starting Position of leg 5
const int L6_angle=120;//Starting Position of leg 6

int signalToStart=0;

LiquidCrystal_I2C lcd(0x27,16,4);
byte e1[8]={
  B00001,
  B00011,
  B00111,
  B01111,
  B01111,
  B01111,
  B11111,
  B11111
};
byte e2[8]={
  B11111,
  B11111,
  B01111,
  B01111,
  B00111,
  B00111,
  B00011,
  B00001
};
byte e3[8]={
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte e4[8]={
  B10000,
  B11000,
  B11100,
  B11110,
  B11110,
  B11111,
  B11111,
  B11111
};
byte e5[8]={
  B11111,
  B11111,
  B11110,
  B11110,
  B11100,
  B11100,
  B11000,
  B10000
};

byte e6[8]={
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
 
  d1.begin();
  d1.setPWMFreq(60);
  d2.begin();
  d2.setPWMFreq(60);
  lcd.begin();
  lcd.backlight();  
  lcd.setCursor(0,0);
  lcd.createChar(1,e1);
  lcd.createChar(2,e2);
  lcd.createChar(3,e3);
  lcd.createChar(4,e4);
  lcd.createChar(5,e5);
  lcd.createChar(6,e6);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  stopBot();
}
void startBot(){//Spider stands up
  lcd.clear();
  do_blink();
  printLCD("HELLO !",0,3);
  d1.setPWM(0,0,angleToPulse(L1_angle));//Turn leg 1
  L1_stat=true;
  d2.setPWM(0,0,angleToPulse(L2_angle));//Turn leg 2
  L2_stat=true;
  d1.setPWM(4,0,angleToPulse(90));      //Turn leg 3
  d2.setPWM(4,0,angleToPulse(90));      //Turn leg 4
  d1.setPWM(8,0,angleToPulse(L5_angle));//Turn leg 5
  L5_stat=true;
  d2.setPWM(8,0,angleToPulse(L6_angle));//Turn leg 6
  L6_stat=true;
  delay(100);
  d1.setPWM(2,0,angleToPulse(feetPlacementAngle));   //Lift feet 1
  d2.setPWM(2,0,angleToPulse(180-feetPlacementAngle));//Lift feet 2
  d1.setPWM(6,0,angleToPulse(feetPlacementAngle));   //Lift feet 3
  d2.setPWM(6,0,angleToPulse(180-feetPlacementAngle));//Lift feet 4
  d1.setPWM(10,0,angleToPulse(feetPlacementAngle));  //Lift feet 5
  d2.setPWM(10,0,angleToPulse(180-feetPlacementAngle)); //Lift feet 6
  delay(1000);
  for(int i=160;i>=legPlacementAngle;i-=2){//Place the legs
    d2.setPWM(1,0,angleToPulse(i));
    d2.setPWM(5,0,angleToPulse(i));
    d2.setPWM(9,0,angleToPulse(i));
    d1.setPWM(1,0,angleToPulse(180-i));  
    d1.setPWM(5,0,angleToPulse(180-i));  
    d1.setPWM(9,0,angleToPulse(180-i));
  
    }
   
  delay(1000);
  }
void stopBot(){
  for(int i=0;i<=20;i+=5){  //Pull the leg up
    d1.setPWM(1,0,angleToPulse(i));
    d1.setPWM(5,0,angleToPulse(i));
    d1.setPWM(9,0,angleToPulse(i));
    d2.setPWM(1,0,angleToPulse(180-i));
    d2.setPWM(5,0,angleToPulse(180-i));
    d2.setPWM(9,0,angleToPulse(180-i));
    delay(10);
  }
  d1.setPWM(0,0,angleToPulse(90));//Turn leg 1 to 90
  L1_stat=false;
  d2.setPWM(0,0,angleToPulse(90));//Turn leg 2 to 90
  L2_stat=false;
  d1.setPWM(4,0,angleToPulse(90));//Turn leg 3 to 90
  d2.setPWM(4,0,angleToPulse(90));//Turn leg 4 to 90
  d1.setPWM(8,0,angleToPulse(90));//Turn leg 5 to 90
  L5_stat=false;  
  d2.setPWM(8,0,angleToPulse(90));//Turn leg 6 to 90
  L6_stat=false;
  delay(1000);
  d1.setPWM(2,0,angleToPulse(30));  //Turn feet 1
  d1.setPWM(6,0,angleToPulse(30));  //Turn feet 2
  d1.setPWM(10,0,angleToPulse(30)); //Turn feet 3
  d2.setPWM(2,0,angleToPulse(150)); //Turn feet 4
  d2.setPWM(6,0,angleToPulse(150)); //Turn feet 5
  d2.setPWM(10,0,angleToPulse(150));//Turn feet 6
  lcd.clear();
  printLCD("Arduino",4,0);
  printLCD("Hexabot",4,1);
  printLCD("Version 1.0",0,2);
  printLCD("OFF Mode",0,3);
  }
int angleToPulse(int angle){
    int pulse = map(angle,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
    return pulse;
    }
void fixBot(){
  lcd.clear();
  do_blink();
  printLCD("Fix Me",0,2);
  d1.setPWM(1,0,angleToPulse(90));
  d1.setPWM(5,0,angleToPulse(90));
  d1.setPWM(9,0,angleToPulse(90));
  d2.setPWM(1,0,angleToPulse(90));
  d2.setPWM(5,0,angleToPulse(90));
  d2.setPWM(9,0,angleToPulse(90));
  delay(2000);
  d1.setPWM(0,0,angleToPulse(90));
  L1_stat=false;
  d2.setPWM(0,0,angleToPulse(90));
   L2_stat=false;
   d1.setPWM(4,0,angleToPulse(90));
   d2.setPWM(4,0,angleToPulse(90));
  d1.setPWM(8,0,angleToPulse(90));
   L5_stat=false;  
  d2.setPWM(8,0,angleToPulse(90));
   L6_stat=false;
  delay(1000);
  d1.setPWM(2,0,angleToPulse(90));
  d1.setPWM(6,0,angleToPulse(90));
  d1.setPWM(10,0,angleToPulse(90));
  d2.setPWM(2,0,angleToPulse(90));
  d2.setPWM(6,0,angleToPulse(90));
  d2.setPWM(10,0,angleToPulse(90));
  }
void loop(){
  if (irrecv.decode(&results)){
        if(results.value==0xFF6897 && signalToStart==0){
          startBot();
          signalToStart=1;
          }
        if(results.value==0xFF02FD){fixBot();}
        if(results.value==0xFFB04F){stopBot();}
        irrecv.resume();
  }  
  while(signalToStart==1){
    if (irrecv.decode(&results)){
      switch(results.value){
        case 0xFF18E7:
        { moveForward();
          while(results.value==0xFFFFFF){moveForward();}
          }
        break;
        case 0xFF10EF:{ turnLeft();
          while(results.value==0xFFFFFF){turnLeft();}
          }break;
        case 0xFF4AB5:{ moveBackward();
          while(results.value==0xFFFFFF){moveBackward();}
          }break;
        case 0xFF5AA5:{ turnRight();
          while(results.value==0xFFFFFF){turnRight();}
          }break;
        }
        if(results.value==0xFFB04F){
          stopBot();
          signalToStart=0;
          }
        irrecv.resume();
    }
    /*if(digitalRead(forward_pin)==HIGH){moveForward();}
    if(digitalRead(reverse_pin)==HIGH){moveBackward();}
    if(digitalRead(left_pin)==HIGH){turnLeft();}
    if(digitalRead(right_pin)==HIGH){turnRight();}
    while(digitalRead(trigger_pin)==HIGH){
      lcd.clear();
      printLCD("HELLO !",0,3);
      do_blink();
      position_legs();
      }*/
    
    
  }
  
  }


