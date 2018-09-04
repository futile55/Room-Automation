
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int count=0;
#define led 7
#define ledldr 6
#define fan 9
#define gate 8

void setup() {
  // put your setup code here, to run once:
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(ledldr,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(gate,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Home Automation System");
  //TO get Temperature
  temp();
}

void loop() {
  // put your main code here, to run repeatedly:
 // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //IR GATE (Counting Persons)
  counter();
  ldr();
  wifi_control();
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}
void counter()
{
 int sensorValue = analogRead(A1);
  int sensorValue1;
 //  Serial.println(sensorValue);
 //Serial.println(sensorValue1);
  if(sensorValue>=600)
  {
    door();
    delay(800);
    sensorValue1 = analogRead(A0);
    if(sensorValue1>=600)
    {
      count++;
      lcd.setCursor(6,1);
       lcd.print("P");
      lcd.print(count,DEC);
    }
  }
else
{
  sensorValue1= analogRead(A0);
}

   if(sensorValue1>=600)
  {
    door();
    delay(800);
    sensorValue = analogRead(A1);
    if(sensorValue>=600)
    {
      count--;
      if(count>=0)
     { 
      lcd.setCursor(6,1);
      lcd.print("P");
      lcd.print(count,DEC);
      
      }
    }
  
  }
  // print out the value you read:
}
void temp()
{
  float tsensor= analogRead(A2);
  delay(1000);
  float tempe =(tsensor*500)/1024.0;
  lcd.setCursor(0,1);
  lcd.print("T");
  lcd.print(tempe,1);
}
void ldr()
{
  int ldrsensor= analogRead(A3);
  Serial.println("ldrsensor" );
  Serial.println(ldrsensor);
  delay(1000);
  if(ldrsensor<=60)
  analogWrite(ledldr,250);
  else if(ldrsensor>60 && ldrsensor<=130)
  analogWrite(ledldr,160);
  else
  analogWrite(ledldr,50);
}
void door()
{
  digitalWrite(gate,HIGH);
  delay(800);
  digitalWrite(gate,LOW);
}
void fanmotor()
{
  digitalWrite(fan,HIGH);
}
void ledglow()
{
  digitalWrite(led,HIGH);  
}
void wifi_control(){
  if(Serial.available())
    {
      lcd.setCursor(10,1);
     char user=Serial.read();
    if(user=='a')
    {    
  digitalWrite(led,HIGH);
  lcd.print("L ON");
    }
    if(user=='A'){
    digitalWrite(led,LOW);
    lcd.print("L OFF");
    }
    if(user=='b') {
     ldr();
    lcd.print("D ON");
    }
    if(user=='B') {digitalWrite(ledldr,LOW);
    lcd.print("D OFF");}
    if(user=='c'){ fanmotor();
    lcd.print("F ON");
    }
    if(user=='C') {digitalWrite(fan,LOW);
    lcd.print("F OFF");}
 }}


