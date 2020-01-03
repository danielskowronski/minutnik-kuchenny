#define _  0
#define A  2
#define B  1
#define C 16
#define D 32
#define E 64
#define F  4
#define G  8


int symbols[] = { 
/* 0 */ A|B|C|D|E|F,
/* 1 */ B|C,
/* 2 */ A|B|D|E|G,
/* 3 */ A|B|C|D|G,
/* 4 */ B|C|F|G,
/* 5 */ A|C|D|F|G,
/* 6 */ A|C|D|E|F|G,
/* 7 */ A|B|C,
/* 8 */ A|B|C|D|E|F|G,
/* 9 */ A|B|C|D|F|G,
/*   */ _,
/* x */ C|D|E|G
};

int latchPin = 15;
int clockPin = 12;
int dataPin  = 5;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}

void shiftOutNBits(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val, uint8_t bits){
    uint8_t i;

    for (i = 0; i < bits; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else    
            digitalWrite(dataPin, !!(val & (1 << (bits-1 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);        
    }
}

void updateScreen(byte left, byte right){
    digitalWrite(latchPin, 0);   
    shiftOutNBits(dataPin, clockPin, MSBFIRST, symbols[right],7); // RQ0..RQ6 = 7 segments of right one
    shiftOutNBits(dataPin, clockPin, MSBFIRST, 1,1);              // RQ7 = latch of right one
    shiftOutNBits(dataPin, clockPin, MSBFIRST, symbols[left],7);  // LQ0..LQ6 = 7 segments of left one
    shiftOutNBits(dataPin, clockPin, MSBFIRST, 0,1);              // LQ7 = not used but needed to fill memory
    digitalWrite(latchPin, 1);
}

void loop() {
  for (int i=0;i<100;i++){
    updateScreen(i/10,i%10);
    delay(100);
  }
}
