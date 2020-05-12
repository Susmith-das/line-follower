/* Define motor controll inputs */
const int motorRforward = 0; // signal pin 1 for the right motor, connect to IN1               
const int motorRbackward = 1;  // signal pin 2 for the right motor, connect to IN2
const int motorREnable = 5; // enable pin for the right motor (PWM enabled)

const int motorLforward = 2; // signal pin 1 for the left motor, connect to IN3           
const int motorLbackward = 3; // signal pin 2 for the left motor, connect to IN4
const int motorLEnable = 6; // enable pin for the left motor (PWM enabled)


int motorLSpeed = 255; //pwm
int motorRSpeed = 255; //pwm
int error = 140;   // 145 best 200  //  normal 255  // mad 0 

const int irPins[8] = {4,7,8,9,10,11,12,13};//defining sensor pins
int irSensors = B00000000; //represent 8 bit binary 00000000

void setup()
{
  Serial.begin(9600);
  
  pinMode(motorLforward,OUTPUT);        
  pinMode(motorLbackward,OUTPUT);
  pinMode(motorLEnable,OUTPUT);
  
  pinMode(motorRforward,OUTPUT);        
  pinMode(motorRbackward,OUTPUT);
  pinMode(motorREnable,OUTPUT);
   
  /* Set-up IR sensor pins as input */
  for (int i = 0; i<8; i++) 
     {pinMode(irPins[i], INPUT);}
}

void loop()
{
     scanD();
     check(); 
} 

void scanD()
{
  for ( byte count = 0; count<8 ;count++ )
   {
     bitWrite(irSensors, count, !digitalRead(irPins[count]));//writes led condition(!) to each bit
   } 
}    

void leftS() 

{
     Serial.println("    turn left $$ right motor forward (spin)");
     analogWrite(motorREnable, motorRSpeed);
     digitalWrite(motorRforward, HIGH);
     digitalWrite(motorRbackward, LOW);
     
     analogWrite(motorLEnable, motorLSpeed-error);
     digitalWrite(motorLforward, LOW);
     digitalWrite(motorLbackward,HIGH);
  
}
void leftSgo() 

{
     Serial.println("    turn left $$ go");
     analogWrite(motorREnable, motorRSpeed);
     digitalWrite(motorRforward, HIGH);
     digitalWrite(motorRbackward, LOW);
     
     analogWrite(motorLEnable, motorLSpeed-error);
     digitalWrite(motorLforward, HIGH);
     digitalWrite(motorLbackward,LOW);
  
}


void rightS()  //turn right
{
     Serial.println("   turn right $$  left  motor forward (spin)");
     analogWrite(motorREnable, motorRSpeed-error);
     digitalWrite(motorRforward, LOW);
     digitalWrite(motorRbackward, HIGH);
     
     analogWrite(motorLEnable, motorLSpeed);
     digitalWrite(motorLforward, HIGH);
     digitalWrite(motorLbackward, LOW);
  
}

void rightSgo()  //turn r
{
     Serial.println("   turn right $$  go");
     analogWrite(motorREnable, motorRSpeed-error);
     digitalWrite(motorRforward, HIGH);
     digitalWrite(motorRbackward, LOW);
     
     analogWrite(motorLEnable, motorLSpeed);
     digitalWrite(motorLforward, HIGH);
     digitalWrite(motorLbackward, LOW);
  
}


void go()
{
    Serial.println("      forward ");
     analogWrite(motorREnable, motorRSpeed);
     digitalWrite(motorRforward, HIGH);
     digitalWrite(motorRbackward, LOW);
     
     analogWrite(motorLEnable, motorLSpeed);
     digitalWrite(motorLforward, HIGH);
     digitalWrite(motorLbackward, LOW);
  
}

void stopme()
{
     Serial.println("     stop");
     analogWrite(motorREnable, 0);
     digitalWrite(motorRforward, LOW);
     digitalWrite(motorRbackward, LOW);
     
     analogWrite(motorLEnable, 0);
     digitalWrite(motorLforward, LOW);
     digitalWrite(motorLbackward, LOW);
  
}


     
void check( ) 
{    
  switch (irSensors)
  {
     case B00000000: // on white paper 
          stopme();
          break;
     
     case B10000000: // leftmost sensor on the line
          leftSgo();
          break;
      
     case B01000000://
          leftSgo();
          break;
     
     case B00100000: 
          leftSgo();
          break;
     

     case B00010000: 
          go();
          break; 
     
     case B00001000: 
          go();
          break;     

     case B00000100: 
          rightSgo();
          break;
     
     case B00000010: 
          rightSgo();
          break;
      
     case B00000001: 
          rightSgo();
          break;       
     
     case B11000000:
          rightS();
          break;
      
     case B01100000:
          rightS();
          break;

     case B00110000:
          rightS(); 
          break;
     
     case B00011000: 
          go();
          break;          

     case B00001100:
          leftS();
          break; 

     case B00000110:
          leftS();
          break;   
     
     case B00000011:
          leftS();
          break;          
       
     case B11100000:
          rightS();   
          break;
      
     case B01110000:
          rightS();
          break;
     
     case B00111000:
          rightS();
          break;
     
     case B00011100:
     leftS();
     break;  
     
     case B00001110:
     leftS();
     break; 
    
     case B00000111:
     leftS();
     break;   
          
     case B11110000:
     rightS(); 
     break; 
     
     case B01111000:
     rightS();       
     break;
      
     case B00111100:
     go();
     break;  
     
     case B00011110:
     leftS();
     break;  
     
     case B00001111:
     leftS();
     break;  
          
     case B11111000:
     rightS(); 
     break; 
     
     case B01111100:
     rightS(); 
     break;
     
     case B00111110:
     leftS();
     break;
     
     case B00011111:
     leftS();
     break;
           
     case B11111100:
     rightS(); 
     break; 
     
     case B01111110:
     go();
     break;
     
     case B00111111:
     leftS();
     break;
     
    
     case B11111110:
     rightS(); 
     break; 
     
     case B01111111:
     leftS();
     break;  
     
     case B11111111:
      go();        
      break;  
   
 
     default:
        Serial.print("Unhandled case: ");   
     
  }
 
}
