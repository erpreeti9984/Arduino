//4 by 4 keypad ka use karke fan ko password ke through control karna

#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
int relayPin = 2;
int mincount = 0;
bool systemLocked = false;

String input = "";                
String fanPassword = "22514";    
String MasterPassword = "00000";  
String Setpassword = "";         

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(9600);
  Serial.print("Enter FanPassword");
}
void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '#') {
      
      if (systemLocked) { 
        if (input == MasterPassword) {
          Serial.println("Master Password Correct.");
           Serial.print("Master Password is: ");
            Serial.println(input);

          systemLocked = false;
          mincount = 0;
        } else {
          Serial.println("Wrong Master Password.");
        }
      } else {
        if (input == fanPassword) {
         Serial.print("Fan Password is: ");
         Serial.println(input);

          Serial.println("Fan password correct. Fan ON.");
          digitalWrite(relayPin, LOW); 
          mincount = 0;
        } else {
          mincount++;
          Serial.print("Wrong Password. Count: ");
          Serial.println(mincount);
      
          digitalWrite(relayPin, HIGH); 
          if (mincount >= 3) {   //3 times try
            systemLocked = true;
            Serial.println("System Locked. Enter Master Password.");
          }
        }
      }
      input = ""; 
    } else {
     
      input.concat(key);
      Serial.print("password is : ");
      Serial.println(input);

    }
  }
}

