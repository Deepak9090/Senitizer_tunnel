/*
Code by DEEPAK KUMAR PANDA
Date-6/10/2020
Copy right©
Dikitec lab!
Project-Senitizing tunel.
MCU-Arduino(Pro micro).
      
-|Peripherals|-      -|Specification(connection)|-
   DF_Player------------None
   Relay----------------Logic i/p(Active LOW)
   Buzzer---------------Variable freq i/p(Use PWM pin)
   Led------------------Logic i/p(Active HIGH)
   ultrasonic-----------communication(Echo,Triger)
*/
//------------------------------------------------|Variables|-------------------------------------------------------------
#define RedLed 6
#define GreenLed 9
#define BlueLed 5
#define Relay 3
#define Buzzer 10
#define Up_Switch 7
#define Down_Switch 4
#define Select_Switch 8
#define ir 2
#include <LiquidCrystal.h>
#include <EEPROM.h>
int Mode=1,j,i;
int Li          = 16;
int Lii         = 0; 
int Ri          = -1;
int Rii         = -1;
int Timer=EEPROM.read(0);
int Mist=EEPROM.read(1);
const char inputArray[]="A PROJECT BY UCPES BERHAMPUR";
const int rs = A3, en = A2, d4 = A1, d5 = 15, d6 = 14, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//--------------------------------------------------|setup|-------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(BlueLed,OUTPUT);
  pinMode(Relay,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  pinMode(Up_Switch,INPUT_PULLUP);
  pinMode(Down_Switch,INPUT_PULLUP);
  pinMode(Select_Switch,INPUT_PULLUP);
  pinMode(A0,INPUT);
  pinMode(ir,INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("SANITIZING BOOTH");
  lcd.setCursor(0,1);
  for (int i = 0; i <= 16; i++) 
  {
    lcd.write(inputArray[i]);
  }
  delay(1500); 
  for (int j = 17; j <= 28; j++) 
  {
     lcd.write(inputArray[j]);
     lcd.scrollDisplayLeft();
     lcd.setCursor(j-16,0);
     lcd.print("SANITIZING BOOTH");
     lcd.setCursor(j+1,1);
     delay(700);
  }
  delay(500);
}
//--------------------------------------------------|Loop|---------------------------------------------------------------
void loop() 
{
  updatedisplay(0);
  Readswitch(0);
  delay(100);
}
//------------------------------------------------|Functions|------------------------------------------------------------
void updatedisplay(int y){
 lcd.clear();
if(y==0){
  switch(Mode)
  {
  case 1 :
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(">AUTOMATIC MODE");
    lcd.setCursor(0,1);
    lcd.print(" MANUAL RUN MODE");
    break;
  case 2 :
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" AUTOMATIC MODE");
    lcd.setCursor(0,1);
    lcd.print(">MANUAL RUN MODE");
    break;
 case 3 :
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(">SET SPRAYTIME");
    lcd.setCursor(0,1);
    lcd.print(" SET MIST FLOW");
    break;
 case 4 :
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" SET SPRAYTIME");
    lcd.setCursor(0,1);
    lcd.print(">SET MIST FLOW");
    break;
  }
}
if (y==1){
  switch(Mode){
    case 1 :
      lcd.setCursor(0,0);
      lcd.print(">SPRAYTIME:");
      lcd.print(Timer);
      lcd.print(" Sec");
      lcd.setCursor(0,1);
      lcd.print(" BACK");
      break;
    case 2 :
      lcd.setCursor(0,0);
      lcd.print(" SPRAYTIME:");
      lcd.print(Timer);
      lcd.print(" Sec");
      lcd.setCursor(0,1);
      lcd.print(">BACK");
      break;
    }
  }
if (y==2){
  switch(Mode){
    case 1 : 
      lcd.setCursor(0,0);
      lcd.print(">MIST FLOW:");
      lcd.print(Mist);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print(" BACK");
      break;
    case 2 :
      lcd.setCursor(0,0);
      lcd.print(" MIST FLOW:");
      lcd.print(Mist);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print(">BACK");
      break;
   }
  }
}

void updatetasks(){
   int l=Mode;
  switch(Mode){
    case 1 :
      while(l==1){
     x: lcd.setCursor(0,0);
        lcd.print("  -:AUTOMODE:-");
        lcd.setCursor(0,1);
        lcd.print("Please go inside");
        //Availablel=Distance();
          if(digitalRead(ir)==HIGH)
          {
            process();
          }
          else
          {
            digitalWrite(GreenLed,HIGH);
            digitalWrite(BlueLed,LOW);
            digitalWrite(RedLed,LOW);
          }
          if(digitalRead(Select_Switch)==LOW)
          {
          while(digitalRead(Select_Switch)==LOW);
          delay(100);
          Mode=1;
          while(l==1){
            Readswitch(1);
            if(Mode==1)
            {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("You want to exit ?");
              lcd.setCursor(0,1);
              lcd.print(">yes     No");
            }
            else if(Mode==2)
            {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("You want to exit ?");
              lcd.setCursor(0,1);
              lcd.print(" yes    >No");
            }
            if(digitalRead(Select_Switch)==LOW)
            {
              while(digitalRead(Select_Switch)==LOW);
              delay(100);
              digitalWrite(Buzzer,HIGH);
              delay(100);
              digitalWrite(Buzzer,LOW);
              if(Mode==1){
                l=10;
              }
              else{
                goto x;
              }
            }
            delay(50);
          }
          }
      }
   break;
   case 2 :
      while(l==2)
      {
     y: lcd.setCursor(0,0);
        lcd.print("-:MANUAL MODE:-");
        lcd.setCursor(0,1);
        lcd.print("Press the switch");
          if(digitalRead(Up_Switch)==LOW)//For manual operation the a extra push switch will be used
          {
            digitalWrite(Buzzer,HIGH);
            delay(100);
            digitalWrite(Buzzer,LOW);
            process();
          }
          else
          {
            digitalWrite(GreenLed,HIGH);
            digitalWrite(BlueLed,LOW);
            digitalWrite(RedLed,LOW);
          }
          if(digitalRead(Select_Switch)==LOW)
          {
          while(digitalRead(Select_Switch)==LOW);
          delay(100);
          Mode=1;
          while(l==2){
            Readswitch(1);
            if(Mode==1)
            {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("You want to exit ?");
              lcd.setCursor(0,1);
              lcd.print(">yes     No");
            }
            else if(Mode==2)
            {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("You want to exit ?");
              lcd.setCursor(0,1);
              lcd.print(" yes    >No");
            }
            if(digitalRead(Select_Switch)==LOW)
            {
              while(digitalRead(Select_Switch)==LOW);
              delay(100);
              digitalWrite(Buzzer,HIGH);
              delay(100);
              digitalWrite(Buzzer,LOW);
              if(Mode==1){
                l=10;
                Mode=2;
              }
              else{
                goto y;
              }
            }
            delay(50);
          }
          }
        }
   case 3 :
   if(Mode > 2){
    Mode=1;
   }
   updatedisplay(1);
      while(l==3)
      {
         a : updatedisplay(1);
         Readswitch(1);
        if(digitalRead(Select_Switch)==LOW)
        {
          while(digitalRead(Select_Switch)==LOW);
          digitalWrite(Buzzer,HIGH);
          delay(100);
          digitalWrite(Buzzer,LOW);
          i=j=0;
          while(Mode==1)
          {
            Timer= map(analogRead(A0),0,1023,0,20);
            EEPROM.write(0,Timer);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("SPRAYTIME:");
            lcd.print(Timer);
            lcd.print(" Sec");
                if(digitalRead(Select_Switch)==LOW)
                {
                  while(digitalRead(Select_Switch)==LOW);
                  digitalWrite(Buzzer,HIGH);
                  delay(100);
                  digitalWrite(Buzzer,LOW);
                  goto a;
                }
                delay(50);           
           }
           if(Mode==2)
           {
            l=15;
            Mode=3;                  
           }
         }
         delay(50);
   }
   break;
  case 4 :
  
     if(Mode > 2){
    Mode=1;
   }
   updatedisplay(2);
      while(l==4)
      {
        deepak : updatedisplay(2);
        Readswitch(1);
        if(digitalRead(Select_Switch)==LOW)
        {
          while(digitalRead(Select_Switch)==LOW);
          digitalWrite(Buzzer,HIGH);
          delay(100);
          digitalWrite(Buzzer,LOW);
          i=j=0;
          while(Mode==1)
          {
            Mist= map(analogRead(A0),0,1023,0,100);
            EEPROM.write(1,Mist);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("MIST FLOW:");
            lcd.print(Mist);
            lcd.print("%");
                if(digitalRead(Select_Switch)==LOW)
                {
                  while(digitalRead(Select_Switch)==LOW);
                  digitalWrite(Buzzer,HIGH);
                  delay(100);
                  digitalWrite(Buzzer,LOW);
                  goto deepak;
                }
                delay(50);           
           }
           if(Mode==2)
           {
            l=15;
            Mode=4;                  
           }
         }
         delay(50);
   }
    break; 
}
}
void process()
{
  digitalWrite(GreenLed,LOW);
  tone(Buzzer,10);
  for(i=0;i<=10;i++)
  {
    digitalWrite(RedLed,HIGH);
    delay(100);
    digitalWrite(RedLed,LOW);
    delay(100); 
  }
  noTone(Buzzer);
  digitalWrite(RedLed,LOW);
  digitalWrite(BlueLed,HIGH);
  delay(100);
  analogWrite(Relay,map(Mist,0,100,0,255));
  delay(1000*Timer);
  digitalWrite(Relay,LOW);
  delay(50);
}
void Readswitch(int x){
  if(x==0){
    if(digitalRead(Up_Switch)==LOW)
  {
    while(digitalRead(Up_Switch)==LOW);
    digitalWrite(Buzzer,HIGH);
    delay(100);
    digitalWrite(Buzzer,LOW);
    Mode--;
  }
  if(digitalRead(Down_Switch)==LOW)
  {
     while(digitalRead(Down_Switch)==LOW);
    digitalWrite(Buzzer,HIGH);
    delay(100);
    digitalWrite(Buzzer,LOW);
     Mode++;
  }
  if(digitalRead(Select_Switch)==LOW)
  {
    while(digitalRead(Select_Switch)==LOW);
    digitalWrite(Buzzer,HIGH);
    delay(100);
    digitalWrite(Buzzer,LOW);
    updatetasks();
  }
 if(Mode<1)Mode=1;
 else if(Mode>4)Mode=4;
  }
  if(x==1){
    if(digitalRead(Up_Switch)==LOW)
    {
      while(digitalRead(Up_Switch)==LOW);
      digitalWrite(Buzzer,HIGH);
      delay(100);
      digitalWrite(Buzzer,LOW);
      Mode--;
     }
     if(digitalRead(Down_Switch)==LOW)
     {
      while(digitalRead(Down_Switch)==LOW);
      digitalWrite(Buzzer,HIGH);
      delay(100);
      digitalWrite(Buzzer,LOW);
      Mode++;
      }
      if(Mode<1)Mode=1;
      else if(Mode>2)Mode=2;
  }
  
}
