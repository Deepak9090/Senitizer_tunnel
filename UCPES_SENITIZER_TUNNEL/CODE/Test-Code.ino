/*
Code by DEEPAK KUMAR PANDA
DIKITEC LAB!
*/
#define Pir 8
#define Alt_led 10
#define Relay 16
#define Buzzer 9
void setup() {
pinMode(Pir,INPUT);
pinMode(Alt_led,OUTPUT);
pinMode(Relay,OUTPUT);
pinMode(Buzzer,OUTPUT);

noTone(Buzzer);
digitalWrite(Relay,HIGH);
digitalWrite(Alt_led,LOW);
}
void loop() {
 if(digitalRead(Pir)==HIGH){
  Alert();
  digitalWrite(Relay,LOW);
  delay(1000*5);
  digitalWrite(Relay,HIGH);
 }
 else{
 noTone(Buzzer);
 digitalWrite(Relay,HIGH);
 digitalWrite(Alt_led,HIGH);
 }
}
void Alert(){
tone(Buzzer,10);
for(int i=0;i<=2;i++){
    digitalWrite(Alt_led,HIGH);
    delay(50);
    digitalWrite(Alt_led,LOW);
    delay(50);
}
noTone(Buzzer);
delay(100);
}
