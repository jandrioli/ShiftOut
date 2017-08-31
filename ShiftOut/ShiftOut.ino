/*
This tests my board with 2 8-segment displays and
2 74hc595n in daisy chain

     -    A - 7
F   | |   B - 1
     -    G - 0
E   | |   C - 6
     -.   D - 2
          E - 4
          F - 5
          DP- 3
*/
                   // 74hc595 pin 16 (VCC)
                   // 74hc595 pin 15 (Q0 - output 0)
int dataPin = 8;   // 74hc595 pin 14 (DS)
                   // 74hc595 pin 13 (OE! output enable active low)
int latchPin = 12; // 74hc595 pin 12 (SH_CP latch)
int clockPin = 11; // 74hc595 pin 11 (ST_CP clock)
int mrestPin = 2;  // 74hc595 pin 13 (MR! master reset active low)

byte leds = 0;
bool l = false;

// THESE ALL WORK OF SHITOUT WITH MSBFIRST AND THE 74HC595
// IS CONNECTED TO 7SEG DISPLAY'S LIKE THIS:
// Q0 - seg a
// ...
// Q7 - seg dp
//         segments:   .gfedcba
byte dec_digits[] = {0b00000110,
                     0b01011011,
                     0b01001111,
                     0b01100110,
                     0b01101101,
                     0b01111100,
                     0b00000111,
                     0b01111111,
                     0b01101111,
                     0b00111111 };

void setup() 
{
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(mrestPin, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(mrestPin, LOW);
  digitalWrite(latchPin, LOW);
  delay(5);
  digitalWrite(mrestPin, HIGH);
  digitalWrite(latchPin, HIGH);
  Serial.println("Started");
}

void loop() {
  Serial.println("Looping...");
  byte b = 0;
    
  for ( int x = 0; x < 8; x++ )
  {
    bitSet(b, x);
    Serial.print("Writing byte:");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(b, BIN);
    
    delay(150);
    
    digitalWrite(latchPin, LOW);
    delay(1);
    shiftOut(dataPin, clockPin, LSBFIRST, b);
    delay(1);
    digitalWrite(latchPin, HIGH);

    
    delay(1000);
    b = 0;
  }
  
    
  delay(2000);
  for ( int x = 0; x < 10; x++ )
  {
    Serial.print("Writing number:");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(dec_digits[x], BIN);
    
    digitalWrite(latchPin, LOW);
    delay(5);
    shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[x]);
    delay(5);
    digitalWrite(latchPin, HIGH);
    
    delay(1000);
  }
  delay(500);
  l = !l;
  digitalWrite(13, l);

}




