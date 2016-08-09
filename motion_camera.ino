#include <Servo.h> 
#include <Wire.h>
#include "Keypad.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
{
  {
    '1','2','3','A'                            }
  ,
  {
    '4','5','6','B'                            }
  ,
  {
    '7','8','9','C'                            }
  ,
  {
    '*','0','#','D'                            }
};
byte rowPins[ROWS] = {
  5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  13, 12, 11, 10}; //connect to the column pinouts of the keypad
int count=0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Servo myservo_pan;
Servo myservo_tilt;
int start_xpos=0;
int end_xpos=0;
int start_ypos=0;

int l=0;
int xpos =100;
int ypos = 135;
int interval = 1;
int duration = 0;
int skip = 0;

void setup() 
{ 
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  myservo_pan.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo_tilt.attach(8);
  lcd.begin(16,2);
  lcd.backlight();
  pinMode(7,OUTPUT);
  test();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Timelapse camera");
  lcd.setCursor(0,1);
  lcd.write("By Spencer O");
  int key = keypad.getKey();
  while(key == NO_KEY) {
    key = keypad.getKey(); //UPDATE VALUE
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("A setup  B Man");
  lcd.setCursor(0,1);
  lcd.write("C default");
  char key_choice = keypad.getKey();
  while(key_choice ==NO_KEY){
    key_choice = keypad.getKey();
  }
  if(key_choice)  // Check for a valid key.
  {
    switch (key_choice)
    {
    case 'A':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("set start: xpos");
      lcd.setCursor(5,1);
      start_xpos += GetNumber();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("set end: xpos");
      lcd.setCursor(5,1);
      end_xpos += GetNumber();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("set fixed: ypos");
      lcd.setCursor(5,1);
      start_ypos += GetNumber();
      ypos=start_ypos;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("Time interval:");
      lcd.setCursor(5,1);
      duration += GetNumber();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("Sweep interval:");
      lcd.setCursor(5,1);
      skip += GetNumber();
      lcd.clear();
      break;

    case 'C':
      start_xpos += 90;
      end_xpos += 180;
      start_ypos +=120;
      duration += 20;
      skip +=5;
      lcd.clear();
      break;

    case 'B':
      int choice = 10;
      while(true){
        lcd.clear();
        choice = GetNumber2();
        if (choice == 4)
        {
          xpos -=2;
          myservo_pan.write(xpos);
        }
        if (choice == 6)
        {
          xpos +=2;
          myservo_pan.write(xpos);
        }
        if (choice == 2)
        {
          ypos +=2;
          myservo_tilt.write(ypos);
        }
        if (choice == 8)
        {
          ypos -=2;
          myservo_tilt.write(ypos);
        }
        if (choice ==5)
        {
          lcd.setCursor(4,1);
          lcd.print("Wait");
          for (int w= 3; w > 0; w=w-1){
            lcd.setCursor(9,1);
            lcd.print("");
            lcd.setCursor(9,1);
            lcd.print(w);
            delay(1000);
          } 
          digitalWrite(7,HIGH);
          lcd.setCursor(12,1);
          lcd.print("Take");
          delay(100);
          digitalWrite(7,LOW);
          delay(1000);
          lcd.setCursor(0,1);
          lcd.print("                ");
        }
      }
    }
  }
}

void loop() 
{ 
  for(xpos = start_xpos; xpos <= end_xpos; xpos += skip) 
  {                                  
    myservo_pan.write(xpos);
    myservo_tilt.write(start_ypos);
    lcd.setCursor(0,0);
    lcd.print("Pan     Tilt     ");
    lcd.setCursor(4,0);
    lcd.print(xpos);
    lcd.setCursor(13,0);
    lcd.print(ypos);
    lcd.setCursor(4,1);
    lcd.print("Wait");
    for (int w= 3; w > 0; w=w-1){
      lcd.setCursor(9,1);
      lcd.print("");
      lcd.setCursor(9,1);
      lcd.print(w);
      delay(1000);
    }    
    digitalWrite(7,HIGH);
    lcd.setCursor(12,1);
    lcd.print("Take");
    delay(100);
    digitalWrite(7,LOW);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("                ");
    for (int x= 0; x < duration; x=x+interval){
      lcd.setCursor(0,1);
      lcd.print("     ");
      lcd.setCursor(0,1);
      lcd.print(duration-x);
      delay(interval*1000);
      lcd.setCursor(0,1);
      lcd.print("OK  ");
    }      
  } 
  for(xpos = end_xpos; xpos >= start_xpos; xpos -= skip) 
  {                                  
    myservo_pan.write(xpos);
    myservo_tilt.write(ypos);
    lcd.setCursor(0,0);
    lcd.print("Pan     Tilt     ");
    lcd.setCursor(4,0);
    lcd.print(xpos);
    lcd.setCursor(13,0);
    lcd.print(ypos);
    lcd.setCursor(4,1);
    lcd.print("Wait");
    for (int w= 3; w > 0; w=w-1){
      lcd.setCursor(9,1);
      lcd.print("");
      lcd.setCursor(9,1);
      lcd.print(w);
      delay(1000);
    }    
    digitalWrite(7,HIGH);
    lcd.setCursor(12,1);
    lcd.print("Take");
    delay(100);
    digitalWrite(7,LOW);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("                ");
    for (int x= 0; x < duration; x=x+interval){
      lcd.setCursor(0,1);
      lcd.print("     ");
      lcd.setCursor(0,1);
      lcd.print(duration-x);
      delay(interval*1000);
      lcd.setCursor(0,1);
      lcd.print("OK  ");
    }      
  } 
} 

int GetNumber()
{
  int num = 0;
  char key = keypad.getKey();
  while(key != '#')
  {
    switch (key)
    {
    case NO_KEY:
      break;

    case '0': 
    case '1': 
    case '2': 
    case '3': 
    case '4':
    case '5': 
    case '6': 
    case '7': 
    case '8': 
    case '9':
      lcd.print(key);
      num = num * 10 + (key - '0');
      break;

    case '*':
      num = 0;
      lcd.setCursor(0,1);
      lcd.print("                  ");
      break;
    }

    key = keypad.getKey();
  }

  return num;
}

int GetNumber2()
{
  int num2 = 0;
  char key_2 = keypad.getKey();
  while(key_2 != NO_KEY)
  {
    switch (key_2)
    {
    case NO_KEY:
      break;

    case '0': 
    case '1': 
    case '2': 
    case '3': 
    case '4':
    case '5': 
    case '6': 
    case '7': 
    case '8': 
    case '9':
      num2 = num2 * 10 + (key_2 - '0');
      break;

    case '*':
      num2 = 0;
      //      lcd.setCursor(0,1);
      //      lcd.print("                  ");
      break;
    }

    key_2 = keypad.getKey();
  }

  return num2;
}

int test()
{
  lcd.clear();
  lcd.write("Self Test");
  myservo_pan.write(90);
  lcd.write(".");
  delay(1000);
  myservo_pan.write(180);
  lcd.write(".");
  delay(1000);
  myservo_pan.write(135);
  lcd.write(".");
  delay(1000);
  myservo_tilt.write(90);
  lcd.write(".");
  delay(1000);
  myservo_tilt.write(120);
  lcd.write(".");
  delay(1000);
  myservo_tilt.write(100);
  lcd.write(".");
  delay(1000);
}














