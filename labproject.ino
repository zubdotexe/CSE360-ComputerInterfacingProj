#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16,2);

int moisture;
int RECV_PIN=6;
int buzzer=7;
int in1=3;
int toggleState_1 = 0;
int soil;


void setup(){
  lcd.begin();
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  IrReceiver.enableIRIn();
  pinMode(buzzer, OUTPUT);
  pinMode(in1, OUTPUT);
  digitalWrite(in1, HIGH);
  Serial.println(F("DHTxx test!"));
 
 
}
void loop(){
   soil=analogRead(A0);
   moisture=map(soil, 0,1023,100,0);
 
//Serial.println(soil);
  if(moisture>30){
    digitalWrite(buzzer, LOW);
  }
   else{
    digitalWrite(buzzer, HIGH);
  }
   if(IrReceiver.decode()){

      Serial.println(IrReceiver.decodedIRData.decodedRawData);
     
  if(IrReceiver.decodedIRData.decodedRawData==3125149440){

                if(toggleState_1 == 0){
                  digitalWrite(in1, HIGH); // turn on switch 1
                  toggleState_1 = 1;
                  }
                else{
                  digitalWrite(in1, LOW); // turn off switch 1
                  toggleState_1 = 0;
                  }
                  delay(100);
   
  }


    IrReceiver.resume();

  }
 

 

  
   lcd.setCursor(0,0);
   lcd.print("Moisture: ");
   lcd.print(moisture);
   lcd.print(" %");
   lcd.setCursor(0,1);
   lcd.print("Remote: ");
   if(toggleState_1==0){
    delay(100);
    lcd.print("ON MODE  ");
   }
   else if(toggleState_1==1){
    delay(100);
    lcd.print("OFF MODE");
   }
   

}
