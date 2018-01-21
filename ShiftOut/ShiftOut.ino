/*
Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
*/

int latchPin = 11; // 74hc595 pin 12
int clockPin = 12; // 74hc595 pin 11
int dataPin = 10;  // 74hc595 pin 15

byte leds = 0;
bool l = false;

byte dec_digits[] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000011,0b11111000,0b10000000,0b10011000 };

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(13, OUTPUT);
  shiftOut(dataPin, clockPin, LSBFIRST, 0b00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, 0b00000000);
}

void loop() {

  /*for (int tensColumn = 0; tensColumn < 10; tensColumn++) {
    for (int onesColumn = 0; onesColumn < 10; onesColumn++) {
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(latchPin, LOW);
      // shift out the bits:
      shiftOut(dataPin, clockPin, LSBFIRST, dec_digits[onesColumn]);
      shiftOut(dataPin, clockPin, LSBFIRST, dec_digits[tensColumn]); 
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      // pause before next value:
      delay(100);
    }
  }*/
  byte b = 0;
  for ( int x = 0; x < 8; x++ )
  {
    bitSet(b, x);
    shiftOut(dataPin, clockPin, MSBFIRST, b);
    delay(150);
    b = 0;
  }
  l = !l;
  digitalWrite(13, l);
}




