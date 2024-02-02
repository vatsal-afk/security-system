#include <Keypad.h> 
#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo_lock;

int contrast = 20;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
int V0_pin = 5;

const int LedPinG = 3;
const int LedPinR = 2;

const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS][COLS] = 
{ 
  {'1', '2', '3', 'A'}, // here '*' stands for ','
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {',', '0', '=', 'D'}  // '#' is used as '='
};
byte rowPins[ROWS] = {13, 12, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 

boolean init_state = false;
boolean state = false;
boolean ultra;
boolean final_state = true;
String ID, pass;
boolean access;
char separator; // stores the ','

char identity [4] = "ABCD";
String default_pass = "123456";

void setup()
{
  analogWrite(V0_pin, contrast);
  pinMode(LedPinR, OUTPUT);
  pinMode(LedPinG, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("Namaste!"); 
  lcd.setCursor(0, 1);
  lcd.print("The Secure Space");
  delay(4000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("ID & Pass - ");
  servo_lock.attach(4);
}

// NO_KEY states that no key has been pressed.

void loop()
{
  char key = keypad.getKey();
  if (key != NO_KEY && (key == '1'|| key == '2'|| key == '3'|| key == '4'|| key == '5'|| key == '6'|| key == '7'|| key == '8'|| key == '9'|| key == '0'|| key == 'A'|| key == 'B'|| key == 'C'|| key == 'D'))
  {
    if (init_state != true)
    {
      ID = ID + key; 
      float ID_length = ID.length();
      lcd.setCursor(0, 1); 
      lcd.print(ID); 
    }
    else
    {
      pass = pass + key;
      float pass_length = pass.length();
      lcd.setCursor(2, 1);
      lcd.print(pass);
      final_state = true;
    }
  }

  else if (state == false && key != NO_KEY && (key == ','))
  {
    init_state = true;
    separator = key; 
    lcd.setCursor(1, 1); 
    lcd.print(separator);
  }

// To check the PIN entered

  else if (final_state == true && key != NO_KEY && key == '=')
  {
    /*
    for(int i; i < 4; i++)
    {
      if (ID == identity[i])
      {
        access = true;
      }
      else if(ID != identity[i])
      {
        access = false;
      }
    }
    */ 

    if (pass == default_pass)
    {
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Access Granted!");
      digitalWrite(LedPinG, HIGH);
      servo_lock.write(180); 
      digitalWrite(LedPinR, LOW);

    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Access Denied!");
      digitalWrite(LedPinG, LOW);
      servo_lock.write(0); 
      digitalWrite(LedPinR, HIGH);
      delay(3000);
      digitalWrite(LedPinR, LOW);
    }
}
}

