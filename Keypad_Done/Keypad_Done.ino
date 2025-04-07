#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char password[4];
char On_equip[] = "123";
char Off_equip[] = "321";
int i = 0;
int on = 0;
int Buzzer = 10;
int RedLed = 11;
int YellowLed = 12;


char MatrixKey[ROWS][COLS] = 
{
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};



byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad Mykeys = Keypad(makeKeymap(MatrixKey), rowPins, colPins, ROWS, COLS); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RedLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  char Enterkey = Mykeys.getKey();

  if (Enterkey)
  {
    password[i] = Enterkey; // Nhập lần lượt các kí tự vào biến chuỗi kí tự Password
    tone(Buzzer, 2500, 300);
    i++;
    on++;
    Serial.println(password);
  }

            if (on == 3)
            {
              if (!strcmp(password, On_equip))
              {
                digitalWrite(RedLed, HIGH);
                digitalWrite(YellowLed, HIGH);
                i = 0;
                Serial.println(" Dung mat khau bat den");
                delay(100);
                tone(Buzzer, 2000, 200);
                delay(100);
                tone(Buzzer, 2000, 200);
              }

              if (!strcmp(password, Off_equip))
              {
                digitalWrite(RedLed, LOW);
                digitalWrite(YellowLed, LOW);
                Serial.println(" Da tat den ......");
                i = 0;
                delay(100);
                tone(Buzzer, 2000, 200);
                delay(100);
                tone(Buzzer, 2000, 200);
              }

              if (strcmp(password, On_equip))
              {
                if (strcmp(password, Off_equip))
                {
                  i = 0;
                  Serial.println(" Sai mat khau nhap lai ...........");
                  digitalWrite(YellowLed, HIGH);
                  delay(300);
                  tone(Buzzer, 2300, 2000);

                }

              }
              on = 0;
            }



}
